#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int reading;
int LM35Feed=A0;
float tCentigrade;
float milivolts;

byte custom[8]=
{
  B11111,
  B10101,
  B10101,
  B11111,
  B10101,
  B10101,
  B11111,
  B00000
};


void setup()
{
 Serial.begin(9600);
lcd.begin(16, 2) ;
lcd.clear();
pinMode (13, OUTPUT);
lcd.createChar(1, custom);

delay(3000)
;}

void loop() {
  reading=analogRead(LM35Feed);
  milivolts=(reading/1023.0)*4000;
  tCentigrade=milivolts/10;
  lcd.print("Loading...");
  delay (70);
  lcd.setCursor(0,1);
  
   lcd.print(".");
   digitalWrite(13, HIGH);
  delay (70);
   lcd.print(".");
  digitalWrite(13, LOW);
  delay (70);
   lcd.print(".");
   digitalWrite(13, HIGH);
  delay (70);
   lcd.print(".");
  digitalWrite(13, LOW);
  delay (70);
   lcd.print(".");
   digitalWrite(13, HIGH);
   
  delay (70);
   lcd.print(".");
  digitalWrite(13, LOW);
  delay (70);
   lcd.print(".");
   digitalWrite(13, HIGH);
   
  delay (70);
   lcd.print(".");
  digitalWrite(13, LOW);
  delay (70);
   lcd.print(".");
   digitalWrite(13, HIGH);
   delay(3000);
  lcd.clear();
  delay(3000);
  
   Serial.print("Temperature:");
   Serial.print(tCentigrade);
   lcd.print("Room temperature:");
   lcd.setCursor(0,1);
   lcd.print(tCentigrade);
   
   

delay (3000);
lcd.clear();

}
