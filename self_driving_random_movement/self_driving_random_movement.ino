/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/
#define mA1 2
#define mA2 3
#define mB1 4
#define mB2 5
#define servopin 6
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  pinMode (mA1, OUTPUT);
  pinMode (mA2, OUTPUT);
  pinMode (mB1, OUTPUT);
  pinMode (mB2, OUTPUT);
  myservo.attach(servopin);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  myservo.write(70);
  delay(305);

  myservo.write(135);
  delay(105);

  myservo.write(160);
  delay(700);

  myservo.write(13);
  delay(105);


  digitalWrite (mA2, HIGH);
  digitalWrite (mA1, LOW);

  digitalWrite (mB2, HIGH);
  digitalWrite (mB1, LOW);

  delay(1400);
  digitalWrite (mA2, LOW);
  digitalWrite (mA1, LOW);

  digitalWrite (mB1, LOW);
  digitalWrite (mB2, LOW);
  delay (700);

  myservo.write(70);
  delay(305);

  myservo.write(90);
  delay(505);

  myservo.write(135);
  delay(105);

  myservo.write(160);
  delay(1000);

  myservo.write(13);
  delay(105);

  digitalWrite (mA1, HIGH);
  digitalWrite (mA2, LOW);

  digitalWrite (mB1, HIGH);
  digitalWrite (mB2, LOW);

  delay(500);
  digitalWrite (mA1, LOW);
  digitalWrite (mA2, LOW);

  digitalWrite (mB1, LOW);
  digitalWrite (mB2, LOW);
  delay (300);

  digitalWrite (mA1, HIGH);
  digitalWrite (mA2, LOW);

  digitalWrite (mB2, HIGH);
  digitalWrite (mB1, LOW);

  delay(200);
  digitalWrite (mA1, LOW);
  digitalWrite (mA2, LOW);

  digitalWrite (mB1, LOW);
  digitalWrite (mB2, LOW);
  delay (1200);


  digitalWrite (mA2, HIGH);
  digitalWrite (mA1, LOW);

  digitalWrite (mB1, HIGH);
  digitalWrite (mB2, LOW);

  delay(500);
  digitalWrite (mA1, LOW);
  digitalWrite (mA2, LOW);

  digitalWrite (mB1, LOW);
  digitalWrite (mB2, LOW);
  delay (1200);
}
