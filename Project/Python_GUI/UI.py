from tkinter import *       #Import tkiner library used to generate GUI
from tkinter import scrolledtext    #Import library for scroll text box

#Generate window
window = Tk()               
#Define window size
window.geometry('360x250')
#Set title for window
window.title("Shawn's Serial Terminal")

#Variable Definitions
com_port = 0
transmit_msg = 0
echo_flag = 0
echo_checkbox = 0

#Define a function to set the com port text to a variable
def set_com_button_pressed() :
    com_port = com_port_textbox.get()

#Define a functiono to set the message to send to a variable
def send_button_pressed():
    transmit_msg = send_message_textbox.get()

########## INIT UI OBJECTS ########################
#Create a label for com port to be placed near text box
com_port_label = Label(window, text = "COM PORT")
#Set its position in top left corner
com_port_label.grid(column = 0, row = 0)

#Create a text box to get the COM port from user
com_port_textbox = Entry(window, width = 10)
#Sets its position
com_port_textbox.grid(column = 0, row = 1)
#set focus on it
com_port_textbox.focus()

#Create a button to send data on selected port
set_com_button = Button(window, text = "Set COM", command = set_com_button_pressed)
#Sets its position
set_com_button.grid(column = 3, row = 0)

#Create a checkbox to register if the user wants the sent data to be echoed in terminal
echo_checkbox = Checkbutton(window, text = "Enable Echo")
#Set position
echo_checkbox.grid(column = 3, row = 1)

#Create a text box to get the transmit message from user
send_message_textbox = Entry(window, width = 26)
#Set its position
send_message_textbox.grid(column = 1, row = 5)

#Create a label for send message to be placed near text box
tx_msg_label = Label(window, text = "TX MSG")
#Set its position next to it
tx_msg_label.grid(column = 0, row = 5)

#Create a button to send data on selected port
send_button = Button(window, text = "send")
#Sets its position
send_button.grid(column = 2, row = 5)

#Create a scroll text box for the terminal
terminal_box = scrolledtext.ScrolledText(window,width=17,height=10)
#Set its position
terminal_box.grid(column = 1, row = 3)

#Create a label for terminal
terminal_label = Label(window, text = "Terminal")
#Set its position on it
terminal_label.grid(column = 1, row = 1)
################################################

window.mainloop()
#Poll echo check box to check if echo of sent message in terminal is required or not
echo_flag = echo_checkbox.state




