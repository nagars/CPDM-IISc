from tkinter import *       #Import tkiner library used to generate GUI

#Generate window
window = Tk()               
#Define window size
window.geometry('400x300')
#Set title for window
window.title("Shawn's Serial Terminal")

#Define a function to change the com port label with user entered com port (TEST ONLY)
def set_com_button_pressed() :
    com_port = com_port_textbox.get()
    com_port_label.configure(text = com_port)

########## INIT UI OBJECTS ########################
#Create a label for com port to be placed near text box
com_port_label = Label(window, text = "COM PORT")
#Set its position in top left corner
com_port_label.grid(column = 0, row = 0)

#Create a text box to get the COM port from user
com_port_textbox = Entry(window, width = 10)
#Sets its position
com_port_textbox.grid(column = 0, row = 1)

#Create a button to send data on selected port
set_com_button = Button(window, text = "Set COM", command = set_com_button_pressed)
#Sets its position
set_com_button.grid(column = 1, row = 1)

#Create a button to send data on selected port
send_button = Button(window, text = "send")
#Sets its position
send_button.grid(column = 1, row = 2)
################################################

window.mainloop()





