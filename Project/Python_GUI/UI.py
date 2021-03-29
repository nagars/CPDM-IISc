from tkinter import *  # Import tkiner library used to generate GUI
from tkinter import scrolledtext  # Import library for scroll text box
import tkinter  # Import function to list serial ports. Re-defined as port_list
import serial.tools.list_ports as port_list
import serial
import time

# Generate window
window = Tk()
# Define window size
window.geometry('550x300')
# Set title for window
window.title("Shawn's Serial Terminal")

# Variable Definitions
#transmit_msg = 0  # Data to transmit given by user
echo_flag = tkinter.BooleanVar()  # Checks if echo checkbox is set/cleared

serial_buffer_size = 12 # Transmit/Receive buffer size

########## CRC FUNCTIONS ################

def crc16(data : bytearray, length):
    if data is None or length <= 0:
        return 0
        
    polynomial = 0x1021
    crc = 0xFFFF

    for i in range(0, length):

        crc ^= data[i] << 8

        for j in range(0,8):

            if (crc & 0x8000) > 0:
                crc =(crc << 1) ^ polynomial
            else:
                crc = crc << 1

    return crc & 0xFFFF


########## SERIAL PORT FUNCTIONS #########

def serial_transmit(instruction):

    #Create empty array of specified bytes
    transmit_buffer = bytearray([0] *  serial_buffer_size)

    #Fill instruction to byte 0
    transmit_buffer[0] = instruction

    #Transmit buffer has 2 segments. Byte 0 to Byte (serial_buffer_size - 2) is the message segment
    #where data is stored. Last 2 bytes are reserved for the crc to be attended to.

    #Calculate CRC for message segment.
    crc = crc16(transmit_buffer, serial_buffer_size - 2)
    print(crc)
    #Append crc to transmit buffer
    transmit_buffer[serial_buffer_size - 2] = (crc >> 8) & 0xff
    transmit_buffer[serial_buffer_size - 1] = crc & 0xff

    #Transmit
    serial_port.write(transmit_buffer)

    #If Echo is on, Print to serial
    if echo_flag.get() == 1:
        n = serial_buffer_size - 1
        while n >= 0:
            terminal_box.insert('1.0', " ")
            terminal_box.insert('1.0', transmit_buffer[n])  
            n = n - 1

        terminal_box.insert('1.0', "Sent: ")


    return

########################################

####### UI EVENT TRIGGERED FUNCTIONS #######
# Define a function to list all com ports
def list_com_button_pressed():
    # List all the available serial ports
    com_ports_available = list(port_list.comports())
    for n in com_ports_available:
        terminal_box.insert('1.0', '\n')
        terminal_box.insert('1.0', n)
        terminal_box.insert('1.0', '\n')

    return

# Define a function to set the com port text to a variable
def set_com_button_pressed():

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
            serial_port = serial.Serial(port = com_port_given, baudrate = 9600, 
                                        bytesize = 8, timeout = 2, stopbits=serial.STOPBITS_ONE)

            #Check if COM port failed to open. Print error message
            if serial_port.isOpen() == 0:
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

            return
    
    # Port name is not listed on available serial ports
    terminal_box.insert('1.0', "\nInvalid COM Port\n")

    return

# Define a function to set the message to send to a variable
def send_button_pressed():

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

###########################################


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
send_message_textbox = Entry(window, width=3, state = 'disabled')
# Set its position
send_message_textbox.grid(column=1, row=5)

# Create a label for send message to be placed near text box
tx_msg_label = Label(window, text="TX MSG")
# Set its position next to it
tx_msg_label.grid(column=0, row=5)

# Create a button to send data on selected port
send_button = Button(window, text="send", command=send_button_pressed, state = 'disabled')
# Sets its position
send_button.grid(column=2, row=5)

# Create a scroll text box for the terminal
terminal_box = scrolledtext.ScrolledText(window, width=40, height=10)
# Set its position
terminal_box.grid(column=1, row=3)

# Create a label for terminal
terminal_label = Label(window, text="Terminal")
# Set its position on it
terminal_label.grid(column=1, row=1)
################################################

window.mainloop()
