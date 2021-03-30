"""
Feature List:
1, Generates GUI serial terminal
2, Prevents user from typing and sending messages
    unless COM port has been opened successfully
3, User can input COM port
4, Checks if given COM port is valid and opens serial
5, Throws error if unable to upon serial to COM port
6, Allows user to list all available COM ports
7, Disabled COM port button and textbox once serial opened
8, If COM port is opened/failed to open, displays message in terminal
9, Enables send button and textbox once COM port is opened
10, Checks if data in textbox to send is valid
11, Creates transmit buffer with data given by user
12, Generates CRC16 for transmit buffer
13, Transmit buffer on serial port
14, Once transmit, waits for acknowledge message from target for 200ms
15, If no ack / if nack comes, print error message on terminal
16, If Echo checkbox is checked, prints transmitted message on 
    terminal once ack returned
17, Generates thread to poll serial constantly
18, Checks data integrity using CRC16. Prints message to terminal if failed.
19, If valid, prints received data to terminal
20, Terminal box auto scrolls upwards
"""

import tkinter                       # Import tkinter library used to generate GUI
from tkinter import *                # Import tkinter modules used to generate GUI
from tkinter import scrolledtext     # Import tkinter library for scroll text box

import serial.tools.list_ports as port_list # Import function to list serial ports.
import serial                       # Import pyserial library
from serial import SerialException  # Import pyserial exception handling

import threading                    # Import threading library to run parallel threads
import time                         # For accessing system time

# Generate GUI window
window = Tk()
# Define window size
window.geometry('600x500')
# Set title for window
window.title("Shawn's Serial Terminal")

# Variable Definitions
echo_flag = tkinter.BooleanVar()    # Checks if echo checkbox is set/cleared
serial_buffer_size = 12             # Transmit/Receive buffer size
ack = 150                           # Acknowledge value returned by stm
nack = 155                          # Not-Acknowledge value returned by stm
ack_received = 0                    # Stores if ack was received on transmission or not

########## CRC FUNCTIONS ################
def crc16(data: bytearray, length):
    """
    Description: Performs a crc16 algorithm on given array of
    data for provided number of bytes. Used both for
    generation of crc16 for transmit message and checking of
    data integrity on receive message
    """

    #Check inputs are valid
    if len(data) == 0 or length <= 0:
        return

    #Set Polynomial and seed
    polynomial = 0x1021
    crc = 0xFFFF

    #Calculate crc
    for i in range(0, length):
        crc ^= data[i] << 8
        for j in range(0, 8):
            if (crc & 0x8000) > 0:
                crc = (crc << 1) ^ polynomial
            else:
                crc = crc << 1

    return crc & 0xFFFF


########## SERIAL PORT FUNCTIONS #########
def serial_read():
    """
    Description: Forever polls the serial terminal for incoming data.
    A successful read has a length of 12 bytes and passes crc16 check.
    Sets/Clears a global acknowledge receive flag if data received is
    an ack/nack message.
    Prints receive message to terminal if valid.
    """

    global ack_received

    while 1:
        #Read 12 bytes of data on serial line (Blocking)
        #Time out set at 2 sec at initialisation of COM port
        receive_buffer = serial_port.read(12)

        #Data received. Check data integrity. Returns 0 if valid
        data_valid = crc16(receive_buffer, serial_buffer_size)

        #Check if data is valid. 0 if valid
        if data_valid == 0:
            #Check if ack received and set flag
            if receive_buffer[0] == ack:
                ack_received = 1
            elif receive_buffer[0] == nack:
                ack_received = 0
            else:
                #Print to terminal
                n = serial_buffer_size - 1
                terminal_box.insert('1.0', "\n")
                while n >= 0:
                    terminal_box.insert('1.0', " ")
                    terminal_box.insert('1.0', receive_buffer[n])
                    n = n - 1

                terminal_box.insert('1.0', "Received: ")

    return


def serial_transmit(instruction):
    """
    Description: Transmit instruction to target device on
    serial terminal. Fills first byte of transmit buffer 
    with instruction, generates crc16 and appends it to alst
    2 bytes of transmit buffer before sending.
    Waits for a specified amount of time for an acknowledge message
    to be returned from target. Prints transmitted buffer to terminal
    if ack returned, else prints error message.
    """

    #Create empty array of specified bytes
    transmit_buffer = bytearray([0] * serial_buffer_size)

    #Fill instruction to byte 0
    transmit_buffer[0] = instruction

    #Transmit buffer has 2 segments. Byte 0 to Byte (serial_buffer_size - 2) is the message segment
    #where data is stored. Last 2 bytes are reserved for the crc to be attended to.

    #Calculate CRC for message segment.
    crc = crc16(transmit_buffer, serial_buffer_size - 2)
    #Append crc to transmit buffer
    transmit_buffer[serial_buffer_size - 2] = (crc >> 8) & 0xff
    transmit_buffer[serial_buffer_size - 1] = crc & 0xff

    #Transmit
    serial_port.write(transmit_buffer)

    #reset ack_received variable
    ack_received = 0
    #Wait for acknowledge/not-acknowledge
    status = wait_for_ack()

    #If ack, print data to serial if necessary, else re-transmit instruction
    if status == True:
        #If Echo is on, Print data sent to serial
        if echo_flag.get() == 1:
            n = serial_buffer_size - 1
            terminal_box.insert('1.0', "\n")
            while n >= 0:
                terminal_box.insert('1.0', " ")
                terminal_box.insert('1.0', transmit_buffer[n])
                n = n - 1

            terminal_box.insert('1.0', "Sent:     ")
    else:
        #Print error message
        terminal_box.insert(
            '1.0', "\nTransmit instruction failed: Not acknowledge returned. Target busy?\n")
    return


def wait_for_ack():
    """
    Description: Waits for acknowledge_received flag to be set
    for 200s. Uses system time to track when time has expired. Returns 
    True if flag is set by serial_receive() while waiting
    """

    #Set current system time in variable
    start_time = time.time()

    #Wait for an ack to be received for 200ms
    while round(time.time() - start_time) <= 0.2:
        if ack_received == 1:
            return True

    return False


####### INITIALISE MULTI_THREAD #####
#Set multi-threading serial read
#Generate thread
read_thread = threading.Thread(target=serial_read)
#Will allow for this thread to be closed on end of main program
read_thread.daemon = True

####### UI EVENT TRIGGERED FUNCTIONS #######
def list_com_button_pressed():
    """Description: Prints a list of available serial COM ports
    on to terminal.
    """

    # List all the available serial ports
    com_ports_available = list(port_list.comports())
    for n in com_ports_available:
        terminal_box.insert('1.0', '\n')
        terminal_box.insert('1.0', n)
        terminal_box.insert('1.0', '\n')

    return


def set_com_button_pressed():
    """
    Description: This function checks if the
    com port given by the user in the textbox is a valid
    name. It confirms if the port is available and opens it.
    Prints error and success messages. Disabled buttons
    and textbox related to com port settings once serial is
    opened. Starts a new thread to poll the serial line for incoming
    data.
    """

    # Get COM port string from textbox
    com_port_given = com_port_textbox.get()

    # Check if string size is valid, else return error
    string_length = len(com_port_given)

    if string_length == 0:
        terminal_box.insert('1.0', "\nNo COM Port Set\n")
        return
    elif string_length < 4:
        terminal_box.insert('1.0', "\nInvalid COM Port\n")
        return
    elif string_length > 5:
        terminal_box.insert('1.0', "\nInvalid COM Port\n")
        return

    # Lists all available serial ports
    com_ports_available = list(port_list.comports())

    # Confirm the inputted port is valid by searching list of valid port names
    for n in com_ports_available:
        if com_port_given in n.description:
            #Open selected com port with default parameters. Returned port handle is set as global variable
            global serial_port
            try:
                serial_port = serial.Serial(port=com_port_given, baudrate=9600,
                                            bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE, parity=serial.PARITY_NONE)
            #Check if COM port failed to open. Print error message
            except SerialException:
                terminal_box.insert('1.0', " is busy. Unable to open\n")
                terminal_box.insert('1.0', com_port_given)
                terminal_box.insert('1.0', "\n")
                return

            #Print COM port opened successfully.
            terminal_box.insert('1.0', " opened successfully\n")
            terminal_box.insert('1.0', com_port_given)
            terminal_box.insert('1.0', "\n")

            #Disable com port button and text box
            set_com_button['state'] = 'disabled'
            com_port_textbox['state'] = 'disabled'

            #Enable send button and send message textbox
            send_button['state'] = 'active'
            send_message_textbox['state'] = 'normal'

            #Enable serial_read thread to poll serial line for receive message
            #Starts thread
            read_thread.start()

            return

    # Port name is not listed on available serial ports
    terminal_box.insert('1.0', "\nInvalid COM Port\n")

    return


def send_button_pressed():
    """Description: Accepts the data to transmit
    from textbox. Checks if value is valid. calls serial_transmit
    to prepare transmit buffer and send on serial.
    """

    # Read message to transmit from textbox
    transmit_msg = send_message_textbox.get()
    # Check if string size is valid, else print error and return
    string_length = len(transmit_msg)
    if string_length == 0:
        terminal_box.insert('1.0', "\nNo TX Message Given\n")
        return
    elif string_length > 3:
        terminal_box.insert('1.0', "\nTX Message Exceeds Max Size\n")
        return

    # Convert the transmit value from string to integer
    transmit_val = int(transmit_msg)

    # Check if value exceeds 100
    if(transmit_val > 100):
        terminal_box.insert('1.0', "\nTX Message Exceeds Max Value of 100\n")
        return
    elif(transmit_val < 0):
        terminal_box.insert('1.0', "\nTX Message Cannot be Negative\n")
        return

    # Call serial transmit function
    serial_transmit(transmit_val)

    return


########## INITIALISE UI OBJECTS ########################
# Create a label for com port to be placed near text box
com_port_label = Label(window, text="COM PORT")
# Set its position in top left corner
com_port_label.grid(column=0, row=0)

# Create a text box to get the COM port from user
com_port_textbox = Entry(window, width=10)
# Sets its position
com_port_textbox.grid(column=0, row=1)
# set focus on it
com_port_textbox.focus()

# Create a button to send data on selected port
set_com_button = Button(window, text="Open COM Port",
                        command=set_com_button_pressed)
# Sets its position
set_com_button.grid(column=3, row=2)

# Create a button to list com ports
list_com_button = Button(window, text="List COM Ports  ",
                         command=list_com_button_pressed)
# Sets its position
list_com_button.grid(column=3, row=1)

# Create a checkbox to register if the user wants the sent data to be echoed in terminal
echo_checkbox = Checkbutton(window, text="Enable Echo", variable=echo_flag)
# Set position
echo_checkbox.grid(column=3, row=3)

# Create a text box to get the transmit message from user
send_message_textbox = Entry(window, width=3, state='disabled')
# Set its position
send_message_textbox.grid(column=1, row=5)

# Create a label for send message to be placed near text box
tx_msg_label = Label(window, text="TX MSG")
# Set its position next to it
tx_msg_label.grid(column=0, row=5)

# Create a button to send data on selected port
send_button = Button(window, text="send",
                     command=send_button_pressed, state='disabled')
# Sets its position
send_button.grid(column=2, row=5)

# Create a scroll text box for the terminal
terminal_box = scrolledtext.ScrolledText(window, width=47, height=20)
# Set its position
terminal_box.grid(column=1, row=3)

# Create a label for terminal
terminal_label = Label(window, text="Terminal")
# Set its position on it
terminal_label.grid(column=1, row=1)
################################################

#Main loop
window.mainloop()
