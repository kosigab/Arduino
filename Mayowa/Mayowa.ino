#include <bluetooth.h>
#include <fm.h>
#include <gprs.h>
#include <sim800.h>
#include <gprs.h>  
#include <SoftwareSerial.h>
#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h> 
#define TIMEOUT 5000

int myBPM=0;
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;    
int Threshold = 550;
PulseSensorPlayground pulseSensor;
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
  
  if (0 != gprs.sendCmdAndWaitForResp("AT+CMGF=1\r\n", "OK", TIMEOUT)) {
    ERROR("ERROR:CNMI");
    return;
  }

  //Start listening to New SMS Message Indications
  if (0 != gprs.sendCmdAndWaitForResp("AT+CNMI=1,2,0,0,0\r\n", "OK", TIMEOUT)) {
    ERROR("ERROR:CNMI");
    return;
  }

  Serial.println("Init success");

 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    Serial.println("PulseSensor !");  
  }
  for(float a=0; a<=10000; a++){
  loop();
  if (myBPM >= 90)
 {
  Serial.print("");
 Serial.println(myBPM); 

  gprs.sendSMS("+2347088190739","hello world"); 
  delay(3000);
  }
  }
 while(!Serial);
  Serial.println("GPRS - Send SMS Test ...");
  gprs.preInit();
  delay(1000);
  while(0 != gprs.init()) {
      delay(1000);
      Serial.print("init error\r\n");
  } 
}

void loop() {
  myBPM = pulseSensor.getBeatsPerMinute();
 if (pulseSensor.sawStartOfBeat()) {            
 Serial.println("?  A HeartBeat Happened ! ");
 Serial.print("BPM: ");
 Serial.println(myBPM);                    
}

 if (myBPM >= 190)
 {
  Serial.print("Sending BPM to Doctor: ");
 Serial.println(myBPM); 

  gprs.sendSMS("+2347088190739","hello world"); 
  delay(3000);
 }
  else{
    }
  delay(20);       

}

