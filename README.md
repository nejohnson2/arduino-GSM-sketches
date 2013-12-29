###Arduino GSM Sketches

These are a collection of sketches to be used with the Arduino GSM Shield.  They focus primarily on using the shield through serial communication instead of using the GSM library.  

####Notes for the tracking sketch

Something important to note is that I modified the GSM library in order to get this sketch to work.  The GSM3CircularBuffer.h file has a default buffer size of 128.  In order to get AT+QENG? information from the GSM module, I had to increase the size of the buffer to 256.  The __BUFFERMASK__ was also changed to 0xFF.

If using the SoftwareSerial Library, modify the SoftwareSerial.h file and to increase the buffer from 64 to 256.

This can be done by:

- Go to the Arduino application (Applications > Arduino) and right click. Select show package contents
- Find the file Resources > Java > libraries > SoftwareSerial > SoftwareSerial.h
- Change the line: __#define _SS_MAX_RX_BUFF 64__   to __#define _SS_MAX_RX_BUFF 256__
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
