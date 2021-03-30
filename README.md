# Project Summary
This is project is the result of a task assigned to me during an interview process. I found it to be very interesting and is a good learning experience for anyone wanting to familiarise themselves with the STM32 and beginners Python Programming.
It involves the development of a python GUI to open a serial port and transmit instructions to an STM32 via UART. The STM performs certain operations and returns the result of said operations to the PC.

Please note, This is my first python script I have ever written. Keep that in mind if you choose to look at my solution to the prompt.

## Table of Contents
1. Getting Started
    1. Hardware Used
    2. Software Used
    3. Dependencies
2. Design Breakdown
    1. STM32
    2. Python GUI
3. Known Issues
4. References
5. Media

## Getting Started
A description of all that you need before actually running this project.

#### Hardware Used

    MCU: STM32F042K6 , Dev-Board: NUCLEO-F042K6 , USB-TTL Converter: Any generic one  
    
#### Software Used

    For STM - IDE: Atollic Truestudio v9.3 , HAL-Generation: CubeMX v6.0.1 , Language: C++
    
    For PC - IDE: Visual Studio Code v1.54.3 (Windows) , Language: Python v3.9
    
#### Dependencies 

    Python libraries required: tkinter , pyserial , threading and time
    
## Design Breakdown

Flowcharts and an overview of the project can be found in the Documents folder.

## Known Issues

- The buffer on the STM is designed for 10 instructions after which previous pending instructions will start getting overwritten. A check along with ready/busy status codes needs to be implemented
- When sending the first instruction through the GUI, the python code sometimes misses the first acknowledge response from the STM. I have confirmed the STM always sends it. Unsure why this bug is occurring.

## References

#### CRC16 

- [Understanding and implementing CRC (Cyclic Redundancy Check) (Updated 2019) calculation](http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html#ch4)
- [CRC16 Routine by Richard van der Hoff (2004)](https://cs.fit.edu/code/svn/cse2410f13team7/wireshark/wsutil/crc16.c)
- [Cyclic Redundancy Check by Gorry Fairhurst (2012)](https://erg.abdn.ac.uk/users/gorry/course/dl-pages/crc.html)
- [Implementing The CCITT Cyclical Redundancy Check by Bob Felice (2007)](https://www.drdobbs.com/implementing-the-ccitt-cyclical-redundan/199904926)

#### Python

- [Graphical User Interfaces with Tk](https://docs.python.org/3/library/tk.html)
- [Programming VIP (2020)](https://programming.vip/docs/python-serial-communication-applet-gui-interface.html)
- [Python GUI examples (Tkinter Tutorial) by Mokhtar Ebrahim (2018)](https://likegeeks.com/python-gui-examples-tkinter-tutorial/)
- [pyserial](https://pyserial.readthedocs.io/en/latest/pyserial.html)
- [threading](https://docs.python.org/3.9/library/threading.html)
- [Python Timer Functions: Three Ways to Monitor Your Code by Geir Arne Hjelle](https://realpython.com/python-timer/)

#### Application Notes

- [Microchip AN730 CRC](https://www.microchip.com/wwwAppNotes/AppNotes.aspx?appnote=en011756)
- [ST AN4908 Auto Baud Rate Detection](https://www.st.com/resource/en/application_note/dm00327191-stm32-usart-automatic-baud-rate-detection-stmicroelectronics.pdf)
- [Tutorial: Checksum and CRC Data Integrity Techniques for Aviation by Philip Koopman (2012)](https://users.ece.cmu.edu/~koopman/pubs/KoopmanCRCWebinar9May2012.pdf)

#### Misc 

- [How To Implement A Simple Circular Buffer In C](https://medium.com/@charlesdobson/how-to-implement-a-simple-circular-buffer-in-c-34b7e945d30e)
- [Check divisibility by 7](https://www.geeksforgeeks.org/divisibility-by-7/#:~:text=Divisibility%20by%207%20can%20be,this%20until%20a%20small%20number)
- [Effect of Initial Seed Values on CRCs and Checksums](https://checksumcrc.blogspot.com/2019/08/effect-of-initial-seed-values-on-crcs.html)

## Media

- Python GUI - https://www.youtube.com/watch?v=e1G2v6ciRYg&list=PLDWfgviIgeVMS9EBJ9NjDTaawb84WkjV9&index=1
- Hardware/Software Interaction - https://www.youtube.com/watch?v=ZplhOZm4G-c&list=PLDWfgviIgeVMS9EBJ9NjDTaawb84WkjV9&index=2
