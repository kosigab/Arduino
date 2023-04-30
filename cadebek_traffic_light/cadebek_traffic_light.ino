
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define red 2
#define yellow 15
#define green 4
int stop_time = 10000;
int ready_time = 1000;
int go_time = 10000;

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  
  lcd.init();                
  lcd.init();

  lcd.backlight();


}


void loop()
{
digitalWrite(red, 1);
delay(stop_time);
digitalWrite (yellow, 1);
delay(ready_time);
digitalWrite(red, 0);
digitalWrite(yellow, 0);
digitalWrite(green, 1);
delay(go_time);
digitalWrite(green, 0);
digitalWrite (yellow, 1);
delay(ready_time);
digitalWrite(yellow, 0);
  
}
