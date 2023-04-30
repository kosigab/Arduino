#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define soil  14
int measure =0;
void setup()
{
 Serial.begin(9600);
 pinMode (soil, INPUT); 

//  dht.begin();
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
delay (3000);

;}

void loop() {
measure = analogRead (soil);
lcd.clear();
lcd.print ("Node 2: Soil");
delay (2000);
lcd.clear();
lcd.print("uncalculated");
lcd.setCursor(0,1);
lcd.print("Soil M = ");
lcd.print(measure);
delay(1000);
lcd.clear();



}
