// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 9);
#include "DHT.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define DHTPIN 10     // what digital pin we're connected to
float h =0;
float t = 0;

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
    dht.begin();
   radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  
  Serial.begin(9600);
  Serial.println("DHTxx test!");



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
}

void loop() {
  // Wait a few seconds between measurements.
  delay(200);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 h = dht.readHumidity();
  // Read temperature as Celsius (the default)
 t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
   // return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
lcd.print("TEMP= ");
lcd.print(t);

lcd.setCursor(0,2);
lcd.print("HUMI= ");
lcd.print(h);
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  delay (1000);
  lcd.clear();
}
