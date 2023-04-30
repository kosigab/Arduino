#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
 int a=0;
 int b=0;
 int c=0;

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
  // put your setup code here, to run once:
lcd.begin(16, 2) ;
lcd.clear();
pinMode (13, OUTPUT);
//lcd.createChar(1, custom);

delay(3000)
;}

void loop() {
  
   lcd.print("Loading Hack Algorithm...");
  delay (3000);
  lcd.setCursor(0,1);
  
   lcd.print(".");
   digitalWrite(13, HIGH);
  delay (500);
   lcd.print(".");
  digitalWrite(13, LOW);
  delay (500);
   lcd.print(".");
  digitalWrite(13, HIGH);
  delay (500);
   lcd.print(".");
    digitalWrite(13, LOW);
  delay (500);
   digitalWrite(13, HIGH);
   lcd.print(".");
  delay (500);
    digitalWrite(13, LOW);
   lcd.print(".");
  delay (500);
  digitalWrite(13, HIGH);
   lcd.print(".");
  delay (500);
  digitalWrite(13, LOW);
   lcd.print(".");
  delay (500);
  digitalWrite(13, HIGH);
   lcd.print(".");
  delay (500);
  digitalWrite(13, LOW);
   lcd.print(".");
  delay (500);
 digitalWrite(13, HIGH);
   lcd.print(".");
  delay (500);
  digitalWrite(13, LOW);
   lcd.print(".");
  delay (500);
 digitalWrite(13, HIGH);
   lcd.print(".");
  delay (500);
   digitalWrite(13, LOW);
  lcd.print(".");
  delay (500);
 digitalWrite(13, HIGH);
   lcd.print(".");
  delay (500);
   digitalWrite(13, LOW);
   lcd.print(".");
  delay (3000);
 
lcd.clear();
lcd.print("Good morning.:-)");
delay (5000);
lcd.clear();
delay (2000);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone");
delay (3000);
lcd.clear();
digitalWrite(13, HIGH);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone.");
delay (500);
lcd.clear();
digitalWrite(13, LOW);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone..");
delay (500);
lcd.clear();
digitalWrite(13, HIGH);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone...");
delay (500);
lcd.clear();
digitalWrite(13, LOW);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone");
delay (500);
lcd.clear();
digitalWrite(13, HIGH);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone.");
delay (500);
lcd.clear();
digitalWrite(13, LOW);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone..");
delay (500);
lcd.clear();
digitalWrite(13, HIGH);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone...");
delay (500);
lcd.clear();
digitalWrite(13, LOW);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone");
delay (500);
lcd.clear();
digitalWrite(13, HIGH);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone.");
delay (500);
lcd.clear();
digitalWrite(13, LOW);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone..");
delay (500);
lcd.clear();
digitalWrite(13, HIGH);
lcd.print("Preparing to");
lcd.setCursor(0,1);
lcd.print("hack phone...");
delay (500);
digitalWrite(13, LOW);
lcd.clear();
delay (3000);

lcd.print("Retrieving data...");
  delay (3000);
  lcd.setCursor(0,1);
  
   lcd.write(1);
   digitalWrite(13, HIGH);
  delay (1000);
   lcd.write(1);
   digitalWrite(13, LOW);
  delay (1000);
   lcd.write(1);
   digitalWrite(13, HIGH);
  delay (1000);
  lcd.write(1);
   digitalWrite(13, LOW);
  delay (100);
   lcd.write(1);
   digitalWrite(13, HIGH);
  delay (100);
   lcd.write(1);
   digitalWrite(13, LOW);
  delay (100);
   lcd.write(1);
   digitalWrite(13, HIGH);
  delay (100);
    lcd.write(1);
   digitalWrite(13, LOW);
  delay (100);
    lcd.write(1);
   digitalWrite(13, HIGH);
  delay (100);
    lcd.write(1);
   digitalWrite(13, LOW);
  delay (100);
   lcd.write(1);
   digitalWrite(13, HIGH);
  delay (100);
   lcd.write(1);
   digitalWrite(13, LOW);
  delay (3000);
    lcd.write(1);
   digitalWrite(13, HIGH);
  delay (500);
   lcd.write(1);
  digitalWrite(13, LOW);
  delay (1000);
   lcd.write(1);
   digitalWrite(13, HIGH);
  delay (100);
    lcd.write(1);
   digitalWrite(13, LOW);
  delay (300);
 //
 do
 {
    do
     {
        digitalWrite(13, HIGH);
         delay(30);
        digitalWrite(13, LOW);
         delay(50);
         a++;
      }
  while(a<50);
     do
     {
       digitalWrite(13, HIGH);
         delay(80);
        digitalWrite(13, LOW);
         delay(70);
         b++;
     }
     while (b<30);
     c++;
 }
 while (c<10);
 
lcd.clear();
delay(5000);
lcd.print("Phone make:");
delay(1000);
lcd.setCursor(0,1);
lcd.print ("SAMSUNG GALAXYs5");
delay(4000);
lcd.clear();
delay(2500);
lcd.print("Google ac found!");
delay(3000);
lcd.clear();
delay(2000);
lcd.print("Google username:");
delay(3000);
lcd.clear();
lcd.print("ejimonuchidieb-");
lcd.setCursor(0,1);
lcd.print("-ere@gmail.com");
delay(5000);
lcd.clear();
lcd.print("Phone password:");
delay(2000);
lcd.setCursor(0,1);
lcd.print("'goal**eh*'");
delay(5000);
lcd.clear();
lcd.print("ERROR 0x000ff3f12f");
lcd.setCursor(0,1);
lcd.print("Invalid password");
delay(5000);
/*
lcd.print(".");
delay (500);

lcd.print(".");
delay (500);
lcd.print(".");
delay (200);
lcd.print(".");
delay (200);
lcd.print(".");
delay (200);
lcd.print(".");
delay (200);
lcd.print(".");
delay (500);

lcd.print(".");
delay (500);
lcd.print(".");
delay (200);
lcd.print(".");
delay (200);
*/
delay (5000);
lcd.clear();

}
