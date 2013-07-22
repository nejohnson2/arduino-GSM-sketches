/* 
 Send SMS with Location of nearby cell phone towers
 
 This sketch sends an AT+QENG command directly to the GSM module which determins
 the GSM modules connected tower and six nearby towers.   The information is then
 put into an array and sent via text message to some specified number every 30sec.
 
 By Nicholas Johnson
 
 */

#include <GSM.h>

GSM gsmAccess(false); //true for debugging 
GSM_SMS sms;

char myNumber[20] = "17654307001";
char buffer[500];
int timeout_1 = 5000; // 5 seconds
int timeout_2 = 5000;
int timeout_3 = 30000;

int bufferSizeWritten;

void setup()
{
  Serial.begin(9600);

  boolean notConnected = true;

  Serial.println("Connecting to the GSM network");

  while(notConnected){
    if(gsmAccess.begin() == GSM_READY) // Note: I do not require PIN #
      notConnected = false;
    else {
      Serial.println("Not connected, trying again");
      delay(1000);
    }
  }

  Serial.println("Connected");
  
  theGSM3ShieldV1ModemCore.println("ATE0");

  theGSM3ShieldV1ModemCore.println("AT+CMGF=1");
  theGSM3ShieldV1ModemCore.println("AT+CREG=2");
  theGSM3ShieldV1ModemCore.println("AT+QENG=1,1");

  int start = millis();
  while((millis() - start) < timeout_1){
    theGSM3ShieldV1ModemCore.theBuffer().flush();  
  }

  getLocation();

}

void loop()
{
  delay(20000);
  getLocation();
}

void getLocation(){

  int start = millis();
  while((millis() - start) < timeout_1){
    theGSM3ShieldV1ModemCore.theBuffer().flush();  
  }
  
  theGSM3ShieldV1ModemCore.println("AT+QENG?");  
  
  char temp_char;
  char resp_temp[20];
  int resp_counter = 0;
  int endline_counter = 0;
  int linenumberyouwant = 3;
  
  start = millis();
  while((millis() - start) < timeout_2) {
    if(theGSM3ShieldV1ModemCore.theBuffer().availableBytes() != 255) {
      temp_char = theGSM3ShieldV1ModemCore.theBuffer().read();

      Serial.print(resp_counter);
      Serial.print(": ");
      Serial.println(resp_temp[resp_counter]); 

      if (temp_char == 0x2B) {  
        Serial.print("end line character");
        endline_counter++; 
      }
      if (endline_counter == linenumberyouwant) {
          buffer[resp_counter] = temp_char;
          resp_counter++;
      }
    }
  } 
  
  sendSMS();
  
}

void sendSMS(){
  
  Serial.print("Message to mobile number: ");
  Serial.println(myNumber);

  // sms text
  Serial.println("SENDING");
  Serial.println();
  Serial.println("Message:");
  Serial.println(buffer);

  // send the message
  sms.beginSMS(myNumber);
  sms.print(buffer);
  sms.endSMS(); 
  Serial.println("\nCOMPLETE!\n");  
}

