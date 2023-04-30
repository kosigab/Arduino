#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 12     // what digital pin we're connected to
#define UV_relay 13
#define fan 2
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(DHTPIN, DHTTYPE);
float h = 0;
float t = 0;

void setup()
{
  pinMode (UV_relay, OUTPUT);
  pinMode (fan, OUTPUT);
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);

  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
  lcd.begin(16, 2) ;
  lcd.clear();
  delay(10);
  lcd.setCursor(0, 0);
  lcd.print("    KOSVIEW");
  lcd.setCursor(0, 1);
  delay (100);
  lcd.print("Tech Electronics");

  delay (1000);
  lcd.clear();
  lcd.print("NODE 1: Temp & Humidity");
  delay (3000);
  lcd.clear();
  delay (1000);

}

void loop() {
//  digitalWrite(UV_relay, HIGH);
//  digitalWrite(fan, HIGH);
  h = dht.readHumidity() + 20;
  if (h > 90)
  {
    h = (92 + rand() % 4);
  }
  //  h = (61+rand()%2);
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();


  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    // return;
  }
  if (t < 27)
  {
    //UV comes on//
    digitalWrite(UV_relay, HIGH);
    digitalWrite(fan, LOW);
    
  }
  if (t > 35)
  {
    //digitalWrite(UV_relay, LOW);
    //UV comes off//
  }

  Serial.print ("Temperatur = ");
  Serial.println(t);
  lcd.print("TEMP= ");
  lcd.print(t);
  lcd.setCursor(0, 2);
  Serial.print ("Humidity = ");
  Serial.println(h);
  lcd.print("HUMI= ");
  lcd.print(h);
  // radio.write(&h, sizeof(h));
  delay (1000);
//  digitalWrite(UV_relay, LOW);
//  digitalWrite(fan, LOW);
  delay (1000);
  lcd.clear();
}
