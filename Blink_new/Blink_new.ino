#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
int dist=0;
int  pos = 0;

LiquidCrystal_I2C lcd(0x3F  ,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(14,INPUT);
 Serial.begin(9600);

  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("----------_________.");
  lcd.setCursor(0,1);
  lcd.print("|     KOSVIEW      |");
   lcd.setCursor(0,2);
  lcd.print("|     PROJECTS     |");
   lcd.setCursor(0,3);
  lcd.print("----------_________|");
  delay (2000);

}


void loop()
{
 do{ 
    lcd.scrollDisplayLeft();
    pos++;
    delay(10);
 }
 while (pos <40);
 delay (2000);
 pos=0;
 {
 do{ 
    lcd.scrollDisplayRight();
    pos++;
    delay(10);
 }
 while (pos <40);
 delay (2000);
 pos=0;
  

 }
 
}
