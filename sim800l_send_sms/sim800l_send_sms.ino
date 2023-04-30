#include <SoftwareSerial.h>

/*
 SMS receiver

 This sketch, for the Arduino GSM shield, waits for a SMS message
 and displays it through the Serial port.

 Circuit:
 * GSM shield attached to and Arduino
 * SIM card that can receive SMS messages

 created 25 Feb 2012
 by Javier Zorzano / TD

 This example is in the public domain.

 http://www.arduino.cc/en/Tutorial/GSMExamplesReceiveSMS

*/

// include the GSM libra

#define SIM800_TX_PIN 7
#define SIM800_RX_PIN 8

// initialize the library instances
SoftwareSerial serialSIM800(SIM800_TX_PIN, SIM800_RX_PIN);
//GSM gsmAccess;
//GSM_SMS sms;

// Array to hold the number a SMS is retreived from
//char senderNumber[20];

void setup()
{
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    serialSIM800.begin(9600);
    delay(1000);
      
      }
      serialSIM800.begin(9600);
    delay(1000);

  Serial.println("Setup complete!");
   Serial.println("Sending sms...");
   serialSIM800.write("AT+CMGF=1\r\n");
   delay(1000);

   serialSIM800.write("AT+CMGS=\"+2347011150239\"\r\n");
   delay(1000);
   serialSIM800.write("project error");
   delay(1000);

   serialSIM800.write((char)26);
   delay(1000);
   Serial.println("SMS sent!");

}
void loop(){
}
