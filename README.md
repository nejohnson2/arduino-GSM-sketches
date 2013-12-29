###Arduino GSM Sketches

These are a collection of sketches to be used with the Arduino GSM Shield.  They focus primarily on using the shield through serial communication instead of using the GSM library.  

####Notes on modifiying the Arduino SoftwareSerial Library

In working with the Arduino GSM shield, I kept finding text messages were only being halfway delivered.  Meaning I would only see have the message.  This happened with a couple of the AT Commands that I was using which return larger amounts of information.  The problem I kept encountering is that the serial buffers in both the SoftwareSerial Library and the GSM library were too small causing the messages and information to be incomplete.  I simply edited those variables in the library in order to get things to work properly.

If using the SoftwareSerial Library, modify the SoftwareSerial.h file to increase the buffer from 64 to 256.

This can be done by:

- Go to the Arduino application (Applications > Arduino) and right click. Select show package contents
- Find the file Resources > Java > libraries > SoftwareSerial > SoftwareSerial.h
- Change the line: __#define _SS_MAX_RX_BUFF 64__   to __#define _SS_MAX_RX_BUFF 256__
- Save file

For the GSM Library:

- Go to the Arduino application (Applications > Arduino and right click.  Select 'Show Package Contents'
- Find the file Resources > Java > libraries > GSM > GSM3CircularBuffer.h 
- Change the line: __#define __BUFFERSIZE__ __128__   to __#define __BUFFERSIZE__ __128__  
- (I also changed the __BUFFERMASK__ value to 0xFF though I'm not sure that is necessary)
- Save file

####Notes for using AT Commands
All of these commands work on the Quectel M10 GSM module which is used on the Arduino GSM Shield.  If using other GSM modules, consult the data sheet or manual for that specific module.  Each company adds and uses different commands which may cause confusion.  That being said, there is a list of standard AT Commands which work across all modules.  They too can be found online.  Below are all most common commands.

- __AT__  Check to see if the module is active.  Should return 'OK'
- __AT+CREG?__ Is the module registered to the network?
- __AT+COPS?__ What network is the module registered?
- __AT+CMGF=1__ This puts the module into text mode so messages can be sent/received
- __AT+CMGS="number",129,__ Send a text message.  When using CoolTerm, enter this command, the use 'Command+T' to bring up another window.  This will let you type ASCII and Hex.  Type your message, and the add '1A' as Hex.
- __AT+CMGL="ALL"__ View all text messages
- __AT+CMGR=<index>__ Read SMS message at index number
- __AT+QBAND?__ What band am I on?
- __AT+CIMI__ Get the IMSI number from the module
- __AT+CSQ__ Check the signal strength
