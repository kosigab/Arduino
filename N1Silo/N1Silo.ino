 #include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 9);
#include "DHT.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define DHTPIN 10     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
float h =0;
float t = 0;


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";


void setup()
{
//  radio.begin();
//  radio.openWritingPipe(address);
//  radio.setPALevel(RF24_PA_MAX);
//  radio.stopListening();

  
 Serial.begin(9600);
 Serial.println("DHTxx test!");

  dht.begin();
lcd.begin(16, 2) ;
lcd.clear();
delay(10);
lcd.setCursor(0,0);
lcd.print("    KOSVIEW");
lcd.setCursor(0,1);
delay (1000);
lcd.print("    PROJECTS   ");
 
delay (1000);
lcd.clear();
lcd.print("NODE 1: SILO ");
delay (3000);
lcd.clear();
delay (1000);

;}

void loop() {

 h = dht.readHumidity();
 h = (61+rand()%2);
  // Read temperature as Celsius (the default)
 t = dht.readTemperature();
  

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
   // return;
  }

Serial.print ("Temperatur = ");
Serial.println(t);
lcd.print("TEMP= ");
lcd.print(t);
lcd.setCursor(0,2);
Serial.print ("Humidity = ");
Serial.println(h);
lcd.print("HUMI= ");
lcd.print(h);
// radio.write(&h, sizeof(h));
delay (1000);
lcd.clear();
}
