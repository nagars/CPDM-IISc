from tkinter import *                   #Import tkiner library used to generate GUI
from tkinter import scrolledtext        #Import library for scroll text box
import tkinter
import serial.tools.list_ports as port_list     #Import function to list serial ports. Re-defined as port_list

#Generate window
window = Tk()
#Define window size
window.geometry('550x300')
#Set title for window
window.title("Shawn's Serial Terminal")

#Variable Definitions
com_port = 0  # Holds com port value given
transmit_msg = 0  # Data to transmit given by user
echo_flag = tkinter.BooleanVar()  # Checks if echo checkbox is set/cleared

#######UI EVENT TRIGGERED FUNCTIONS#######
#Define a function to list all com ports
def list_com_button_pressed():
    ports = list(port_list.comports())
    for n in ports:
        terminal_box.insert('1.0','\n')
        terminal_box.insert('1.0', n)
        terminal_box.insert('1.0','\n')
    
    return

#Define a function to set the com port text to a variable
def set_com_button_pressed():
    #Get COM port string from textbox
    com_port = com_port_textbox.get()
    #Check if string size is valid, else return error
    string_length = len(com_port)

    if string_length == 0:
        terminal_box.insert('1.0', "\nNo COM Port Set\n")
    elif string_length < 4:
        terminal_box.insert('1.0', "\nInvalid COM Port\n")
    elif string_length > 5:
        terminal_box.insert('1.0', "\nInvalid COM Port\n")
    else:
        #Open selected com port

        #Print com port valid
        
        return

#Define a function to set the message to send to a variable
def send_button_pressed():
    #Ensure COM port is set and open

    #Read message to transmit from textbox
    transmit_msg = send_message_textbox.get()
    #Check if string size is valid, else print error and return
    string_length = len(transmit_msg)
    if string_length == 0:
        terminal_box.insert('1.0', "\nNo TX Message Given\n")
        return

    #Convert the transmit value from string to integer
    transmit_val = int(transmit_msg)

    print (transmit_val)
    #Check if value exceeds 100
    if(transmit_val > 100):
        terminal_box.insert('1.0', "TX Message Exceeds Max Value of 100\n")
        return
    elif(transmit_val < 0):
        terminal_box.insert('1.0', "TX Message Cannot be Negative\n")
        return

    #Call serial transmit function

    #print data sent if successful

    return

###########################################


########## INIT UI OBJECTS ########################

#Create a label for com port to be placed near text box
com_port_label = Label(window, text="COM PORT")
#Set its position in top left corner
com_port_label.grid(column=0, row=0)

#Create a text box to get the COM port from user
com_port_textbox = Entry(window, width=10)
#Sets its position
com_port_textbox.grid(column=0, row=1)
#set focus on it
com_port_textbox.focus()

#Create a button to send data on selected port
set_com_button = Button(window, text="Set COM", command=set_com_button_pressed)
#Sets its position
set_com_button.grid(column=3, row=2)

#Create a button to list com ports
list_com_button = Button(window, text="List COM Ports", command=list_com_button_pressed)
#Sets its position
list_com_button.grid(column=3, row=1)

#Create a checkbox to register if the user wants the sent data to be echoed in terminal
echo_checkbox = Checkbutton(window, text="Enable Echo", variable=echo_flag)
#Set position
echo_checkbox.grid(column=3, row=3)

#Create a text box to get the transmit message from user
send_message_textbox = Entry(window, width=3)
#Set its position
send_message_textbox.grid(column=1, row=5)

#Create a label for send message to be placed near text box
tx_msg_label = Label(window, text="TX MSG")
#Set its position next to it
tx_msg_label.grid(column=0, row=5)

#Create a button to send data on selected port
send_button = Button(window, text="send", command = send_button_pressed)
#Sets its position
send_button.grid(column=2, row=5)

#Create a scroll text box for the terminal
terminal_box = scrolledtext.ScrolledText(window, width=40, height=10)
#Set its position
terminal_box.grid(column=1, row=3)

#Create a label for terminal
terminal_label = Label(window, text="Terminal")
#Set its position on it
terminal_label.grid(column=1, row=1)
################################################

window.mainloop()
