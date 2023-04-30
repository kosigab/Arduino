/*
  Arduino Wireless Communication Tutorial
      Example 1 - Transmitter Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
float cel = 0;
float val;
float mv = 0;
int tempPin = 14;
#define red 2
//LiquidCrystal lcd (2,3,4,5,6,9);
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
int a = 10;
void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  Serial.begin(9600);
  //lcd.begin(16, 2);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  pinMode (14, INPUT);
  pinMode (2, OUTPUT);
  lcd.clear();
  lcd.print("Kosview");
  lcd.setCursor(0, 1);
  lcd.print("    Projects");
  delay(1000);
    lcd.clear();
}
void loop() {
  //const char text[] = "Hello World";
  lcd.clear();
  val = analogRead(14);
   mv = ( val / 1024.0) * 5000;
 cel = (mv / 10)-15;
  radio.write(&cel, sizeof(cel));
  Serial.println(cel);
  digitalWrite (10, HIGH);
  delay (30);
  digitalWrite(10, LOW);
  //a++;
  delay(70);
  lcd.print("temp = ");
  lcd.setCursor(0, 1);
  lcd.print(cel);
  delay(600);
}
