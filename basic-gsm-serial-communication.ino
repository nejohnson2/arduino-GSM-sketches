/*
  
  This sketch is the most basic way to communicate with the Arduino 
  GSM Shield.  Upload the sketch and use Cool Term to send AT Commands
  directly to the GSM Module.  
  
  View Quectel M10 AT Command Set:
  http://arduino.cc/en/uploads/Main/Quectel_M10_AT_commands.pdf
  
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

char inChar = 0;

void setup()  
{
  Serial.begin(9600);
  Serial.println("Device ready");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}

void loop() // run over and over
{
  if (mySerial.available()){
    inChar = mySerial.read();
    Serial.write(inChar);
    delay(20);
    }
    
  if (Serial.available()>0){
    mySerial.write(Serial.read());
  }
}
