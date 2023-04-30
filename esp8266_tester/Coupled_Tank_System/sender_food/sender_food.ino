#define solenoid 6
#define node_hts 7
#define ts 8
#define red 10
#define green 11
#include "HX711.h"
#include <Servo.h>
Servo myservo;

const int LOADCELL_DOUT_PIN1 = 3;
const int LOADCELL_SCK_PIN1 = 2;
const int LOADCELL_DOUT_PIN2 = 5;
const int LOADCELL_SCK_PIN2 = 4;

int food_q = 100;
double food_mass = 0;
double water_mass = 0;
int water_q = 1000;
String food = "food";
String water = "water";
int nhts = 0;
int pos = 0;

HX711 scale1;
HX711 scale2;

void setup() {
  myservo.attach(9);
  myservo.write(0);
  scale1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
  scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);

  pinMode(node_hts, INPUT);
  pinMode(solenoid, OUTPUT);
  pinMode(ts, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode (green, OUTPUT);
  digitalWrite(ts, HIGH);
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
  Serial.begin(9600);
}

void loop() {
  if (scale1.is_ready()) {
    double reading = scale1.read() - 154400 ;
    //    Serial.print("food quantity: ");

    food_mass = ((171 * reading) / 160000);
    food_q = (100 * food_mass) / 572;
    if (food_q < 25)
    {
      myservo.write(120);
    }
    //  Serial.print(food_q);
    // Serial.println("%");

    if (food_q > 90)
    {
      myservo.write(0);
    }

  }
  delay(100);
  if (scale2.is_ready()) {
    double reading = scale2.read() + 101160 ;

    //   Serial.print("water quantity: ");

    water_mass = (171 * reading) / 162000;
    water_q = (100 * water_mass) / 674;
    // Serial.print(water_q);
    //  Serial.println("%");
    if (water_q < 15)
    {
      digitalWrite(solenoid, LOW);
    }
    if (water_q > 90)
    {
      digitalWrite(solenoid, HIGH);
    }

  }
  // delay (1000);

  nhts = digitalRead(node_hts);
  // Serial.print(nhts);
  delay(10);

  if (nhts < 1)
  {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);

    digitalWrite(ts, HIGH);
    Serial.println(food_q);
    delay(2000);
    // food_q++;
    Serial.println(food);
    delay(2000);

    Serial.println(water_q);
    delay(2000);
    // water_q++;

    Serial.println(water);
    delay(2000);
    digitalWrite(ts, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    nhts = digitalRead(node_hts);
    delay(2000);
    nhts = digitalRead(node_hts);

  }
}
