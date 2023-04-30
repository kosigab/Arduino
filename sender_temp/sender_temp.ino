#define node_fts 7
#define ts 8
#include "DHT.h"
#include <Wire.h>
#define DHTPIN 12     // what digital pin we're connected to
#define UV_relay 13
#define fan 2
#define red 10
#define green 11
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)


int temp = 0;
int humi = 0;
String temperature = "temperature";
String humidity = "humidity";
int nfts = 0;

DHT dht(DHTPIN, DHTTYPE);
float h = 0;
float t = 0;

void setup() {
  pinMode(node_fts, INPUT);
  pinMode (ts, OUTPUT);
  pinMode (UV_relay, OUTPUT);
  pinMode (fan, OUTPUT);
  pinMode (red, OUTPUT);
  pinMode (green, OUTPUT);
  digitalWrite(ts, LOW);

  digitalWrite(red, HIGH);
  delay(10);
  digitalWrite (red, LOW);
  delay(50);
  digitalWrite(red, HIGH);
  delay(10);
  digitalWrite (red, LOW);
  delay(50);
  digitalWrite(red, HIGH);
  delay(10);
  digitalWrite (red, LOW);
  delay(50);
  digitalWrite(green, HIGH);
  delay(50);
  digitalWrite(green, LOW);
  delay(50);
  digitalWrite(green, HIGH);
  delay(50);
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);


  Serial.begin(9600);
  dht.begin();
}

void loop() {
  h = dht.readHumidity() + 20;
  if (h > 90)
  {
    h = (92 + rand() % 4);
  }
  //  h = (61+rand()%2);
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();


  // if (isnan(h) || isnan(t)) {
  //    Serial.println("Failed to read from DHT sensor!");
  //    // return;
  //  }

  if (t < 24)
  {
    //UV comes on//
    digitalWrite(UV_relay, HIGH);
    digitalWrite(fan, LOW);

  }
  if (t > 35)
  {
    digitalWrite(UV_relay, LOW);
    //UV comes off//
    digitalWrite(fan, HIGH);
  }
  temp = t;
  humi = h;

  nfts = digitalRead(node_fts);
  // Serial.print(nfts);
  delay(10);
  if (nfts < 1)
  {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(ts, HIGH);
    Serial.println(temp);
    delay(3000);

    Serial.println(temperature);
    delay(3000);

    Serial.println(humi);
    delay(3000);

    Serial.println(humidity);
    delay(3000);
    digitalWrite(ts, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    nfts = digitalRead(node_fts);
    delay(3000);
    nfts = digitalRead(node_fts);

  }



}
