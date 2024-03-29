/*
Sketch: GPRS Connect TCP

Function: This sketch is used to test seeeduino GPRS's send SMS func.to make it work, 
you should insert SIM card to Seeeduino GPRS and replace the phoneNumber,enjoy it!
************************************************************************************
note: the following pins has been used and should not be used for other purposes.
  // Arduino Pin 7 -----> Sim800l RX
//Arduino Pin 8 ------> sim800l TX
  pin 9   // power key pin
  pin 12  // power status pin
************************************************************************************
created on 2013/12/5, version: 0.1
by lawliet.zou(lawliet.zou@gmail.com)
*/
#include <gprs.h>
#include <SoftwareSerial.h>

GPRS gprs;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("GPRS - Send SMS Test ...");
  gprs.preInit();
  delay(1000);
  while(0 != gprs.init()) {
      delay(1000);
      Serial.print("init error\r\n");
  }  
  Serial.println("Init success, start to send SMS message...");
  gprs.sendSMS("+2347011150239","Let's test this"); //define phone number and text
}

void loop() {
  //nothing to do
}
