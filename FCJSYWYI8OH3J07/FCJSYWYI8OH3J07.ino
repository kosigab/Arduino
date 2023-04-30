
#include <LiquidCrystal.h>
unsigned int val = 0; //breathalyzer value
unsigned char PIN = 0;
int intNumber = 1023; //max value
LiquidCrystal lcd(8,9,4,5,6,7);

void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
lcd.print("Calculating BAC...");

}

void loop() {
  // main program
  int delayTime = 100; //delay
 
val=analogRead(A0);
if(val<=735){
lcd.setCursor(1, 2);
lcd.print("BAC = 0");
delay(delayTime);
}

else if(val>735 && val < 800){
float bac=val*.0015 - 1.1125;
  lcd.setCursor(1, 2);
lcd.print("BAC = ");
lcd.print(bac,3);
delay(delayTime);
}

else if(val>800){
float bac=val*0.0053-4.1867;
  lcd.setCursor(1, 2);
lcd.print("BAC = ");
lcd.print(bac,3);
delay(delayTime);
}
}
