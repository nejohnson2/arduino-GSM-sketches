/*
  
  This sketch uses the Arduino GSM Shield to allow the user to send AT Commands to the GSM module 
  directly without needing the Arduino GSM Library.  Upload this sketch, open a serial application
  like CoolTerm, and begin sending commands.
  
  Developed by Benedetta Simeonidis
  
*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
char inChar = 0;
char message[] = "hello world";

void setup()  
{
  Serial.begin(9600);
  Serial.println("Hello Debug Terminal!");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

  //Turn off echo from GSM
  mySerial.print("ATE0");
  mySerial.print("\r");
  delay(300);
  
  //Set the module to text mode
  mySerial.print("AT+CMGF=1");
  mySerial.print("\r");
  delay(500);
  
  //Send the following SMS to the following phone number
  mySerial.print("AT+CMGS=\"");
  // CHANGE THE NUMBER BELOW! 
  // 129 for domestic #s, 145 if with +area code in front of #
  mySerial.print("1234567\",129");                                         //this is where you would replace the phone number
  mySerial.print("\r");
  delay(300);
  // TYPE THE BODY OF THE TEXT HERE! 160 CHAR MAX!
 // mySerial.print("T4D);
  mySerial.print(message);
  // Special character to tell the module to send the message
  mySerial.write(0x1A);
  delay(500);
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
