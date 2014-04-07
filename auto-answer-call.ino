/*
  Featured AT Command:
  
  ATSO=1
  Set the phone to automatically answer a phone number.

  By Mike Allison
  Towers of Power
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
boolean stringComplete = false;
String inputString = "";
String fromGSM="";
void setup()  
{
  Serial.begin(9600);
  Serial.println("Serial Connected");
  mySerial.begin(9600);
  
  //reserve some buffer space
  inputString.reserve(200);
  fromGSM.reserve(200);
  
  //Turn off echo from GSM
  mySerial.print("ATE0");
  mySerial.print("\r");
  delay(300);
  
  //set to auto answer after 1 ring, [1-255]
  mySerial.print("ATS0=1");
  mySerial.print("\r");
  delay(300);
 
}

void sendSMS(String& phone_number, char message[] ){
    //Set the module to text mode
    mySerial.print("AT+CMGF=1");
    mySerial.print("\r");
    delay(500);
    
    //Send the following SMS to the following phone number
    mySerial.print("AT+CMGS=\"");
    // CHANGE THE NUMBER BELOW! 
    // 129 for domestic #s, 145 if with +area code in front of #
    mySerial.print(phone_number+"\",129");                                         //this is where you would replace the phone number
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
  //listen from GSM Module
  if (mySerial.available()){
   char inChar = mySerial.read();
    
    if (inChar == '\n') {
      
       //check the state 
       if(fromGSM == "OK\r"){
          Serial.println("---------IT WORKS-------");
        }
        else if(fromGSM == "RING\r"){
          Serial.println("---------ITS RINGING-------");
        }
        else if(fromGSM == "ERROR\r"){
          Serial.println("---------IT DOESNT WORK-------");
        }
        else if(fromGSM == "NO CARRIER\r"){
          Serial.println("---------CALL ENDED-------");
          String myNumber = "XXXXXXXXXX"; // <------ Dont forget to change this!!!
          char myMessage[] = "Thanks for Calling, Mike!";
          sendSMS(myNumber, myMessage);
        }
        
        
      //write the actual response
      Serial.println(fromGSM);
      //clear the buffer
      fromGSM = "";
        
    }else {
         fromGSM+=inChar;
    }
    delay(20);
    }
    
    //only write a full message to the GSM module
    if (stringComplete) {
      mySerial.print(inputString); 
      inputString = "";
      stringComplete = false;
    }
  
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}
