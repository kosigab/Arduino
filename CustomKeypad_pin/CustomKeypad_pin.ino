/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>
#include <LiquidCrystal.h>
#define red 4
#define green 3
char* ourCode = "1234";
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
int currentPosition=0;


const byte rows = 4; //number of the keypad's rows and columns
const byte cols = 4;
//define the cymbols on the buttons of the keypads
char keyMap [rows] [cols] = { //define the cymbols on the buttons of the keypad

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
////PIN 8 is BAD!!!
byte rowPins [rows] = {13, 12, 11, 10}; //pins of the keypad
byte colPins [cols] = {9, 6, 5, 2};

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols);
void setup(){
  lcd.begin(16, 2) ;
  displayCodeEntryScreen();
  pinMode (red, OUTPUT);
   pinMode (green, OUTPUT);
  


  
//  lcd.setCursor(0,1);
  Serial.begin(9600);
}
  
void loop()
{ 
  int l;
  char Key = myKeypad.getKey();
 
 
  if (int(Key)!=0){
   // lcd.setCursor(0,1);
   // lcd.print("    ");
    lcd.setCursor(0,1);
    Serial.println(Key);
  //  lcd.print(Key);

    for (l=0; l<=currentPosition; ++l)
    {
      lcd.print("*");
      if (Key != ourCode [currentPosition])
      {
        ++currentPosition;
        if(currentPosition == 4)
        {
          unlockDoor();
          currentPosition=0;
        }
       if (Key == ourCode [currentPosition])
          {
          invalidCode();
          currentPosition = 0;
          }
        }
    }
      
 }
  }
  
//}
void  displayCodeEntryScreen()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter secret pin");
  lcd.setCursor(0,1);
}
void unlockDoor()
{
   digitalWrite(green, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("*****ACCESS*****");
  lcd.setCursor(0,1);
  lcd.print("****GRANTED!****");
  delay(5000);
   digitalWrite(green, LOW);
   displayCodeEntryScreen();
  
}
void invalidCode()
{
  lcd.clear();
  digitalWrite(red, HIGH);
  lcd.setCursor(0,0);
  lcd.print("*****ACCESS*****");
  lcd.setCursor(0,1);
  lcd.print("*****DENIED!****");
  delay(5000);
   digitalWrite(red, LOW);
   displayCodeEntryScreen();
  
}
