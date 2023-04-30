#include <SoftwareSerial.h>
 
//SIM900 TX is connected to Arduino D6
#define SIM900_TX_PIN 7
 
//SIM900 RX is connected to Arduino D7
#define SIM900_RX_PIN 8
 
//Create software serial object to communicate with SIM900
SoftwareSerial serialSIM900(SIM900_TX_PIN,SIM900_RX_PIN);
 
void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  while(!Serial);
   
  //Being serial communication witj Arduino and SIM900
  serialSIM900.begin(9600);
  delay(1000);
   
  Serial.println("Setup Complete!");
}
 
void loop() {
  //Read SIM900 output (if available) and print it in Arduino IDE Serial Monitor
  if(serialSIM900.available()){
    Serial.write(serialSIM900.read());
  }
  //Read Arduino IDE Serial Monitor inputs (if available) and send them to SIM900
  if(Serial.available()){    
    serialSIM900.write(Serial.read());
  }
}
