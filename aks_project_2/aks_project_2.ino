/* Arduino Security System with the Keypad and LCD 
 * Creator Mert Kılıç - Mert Arduino Tutorial and Project
 * Please subscribe for support
 * Thanks
 */

#include <LiquidCrystal.h> //include LCD library (standard library)
#include <Keypad.h> //include keypad library - first you must install library (library link in the video description)
#include <SoftwareSerial.h>

#define servo 12
#define red 4
#define green 3
#define SIM800_TX_PIN 1
#define SIM800_RX_PIN 2
SoftwareSerial serialSIM800(SIM800_TX_PIN, SIM800_RX_PIN);

char* password ="0000"; //create a password
int pozisyon = 0; //keypad position
int flag = 0;

const byte rows = 4; //number of the keypad's rows and columns
const byte cols = 4;

char keyMap [rows] [cols] = { //define the cymbols on the buttons of the keypad

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
////PIN 8 is free!!!
byte rowPins [rows] = {13, 12, 11, 10}; //pins of the keypad
byte colPins [cols] = {9, 7, 6, 5};

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols);

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); // pins of the LCD. (RS, E, D4, D5, D6, D7)

void setup(){
  

  lcd.begin(16, 2);
   pinMode (red, OUTPUT);
   pinMode (green, OUTPUT);
   Serial.begin(9600);
  while (!Serial) {
    serialSIM800.begin(9600);
    delay(1000);
      
      }
      serialSIM800.begin(9600);
    delay(1000);
    Serial.println("Setup complete!");
    lcd.print("GSM initialized!");
    delay (2000);
      lcd.print("Enter secret pin");
  pinMode (servo, OUTPUT);
//  setLocked (true); //state of the password
  
}

void loop(){

  char whichKey = myKeypad.getKey(); //define which key is pressed with getKey
    int l;
  if (int(whichKey)!=0){
    lcd.clear();
 lcd.setCursor(0, 0);
 // lcd.print("    Welcome");
  
  lcd.print(" Enter Password");
  lcd.setCursor(0, 1);
   for (l=0; l<=pozisyon; ++l)
    {
      lcd.print("*");
    }

  if(whichKey == '*' || whichKey == '#' || whichKey == 'A' ||       //define invalid keys
  whichKey == 'B' || whichKey == 'C' || whichKey == 'D'){

    pozisyon=0;
//    setLocked (true);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Invalid Key!");
    delay(1000);
    lcd.clear();
  }
  if(whichKey == password [pozisyon]){

    pozisyon ++;
  }
  if(pozisyon == 4)
  {
    if (flag == 0)
    {
      // setLocked (false);
       lcd.clear();
       lcd.setCursor(0, 0);
       digitalWrite(green, HIGH);
       lcd.print("Vehicle unlocked!");
       sendsmsunlocked();
       pozisyon = 0;
       delay(3000);
       digitalWrite(green, LOW);
       lcd.clear();
       flag=1;
    }
    if(flag == 1)
    {
    //  setLocked (false);
      lcd.clear();
      lcd.setCursor(0, 0);
      digitalWrite(red, HIGH);
      lcd.print("Vehicle locked!");
      sendsmslocked();
      pozisyon = 0;
      delay(3000);
      digitalWrite(red, LOW);
      lcd.clear();
    }
   }
    lcd.print(" Enter Password");
    lcd.setCursor(0, 0);
   
  }
  else if(whichKey != password [pozisyon]){
//     setLocked (true);
     lcd.clear();
      digitalWrite(red, HIGH);
     lcd.print("***Access denied!***");
      pozisyon = 0;
      delay (3000);
      digitalWrite(red, LOW);
      lcd.clear();
       lcd.print(" Enter Password");
  }  
  }
//  delay(100);

// }
  


  void sendsmsunlocked()
  {
     Serial.println("Sending sms...");
   serialSIM800.write("AT+CMGF=1\r\n");
   delay(1000);

   serialSIM800.write("AT+CMGS=\"+2348082999099\"\r\n");
   delay(1000);
   serialSIM800.write("Your vehicle was just unlocked succesfully!");
   delay(1000);

   serialSIM800.write((char)26);
   delay(1000);
   Serial.println("SMS sent!");
    }
    
    void sendsmslocked()
  {
     Serial.println("Sending sms...");
   serialSIM800.write("AT+CMGF=1\r\n");
   delay(1000);

   serialSIM800.write("AT+CMGS=\"+2348082999099\"\r\n");
   delay(1000);
   serialSIM800.write("Your vehicle was just locked!");
   delay(1000);

   serialSIM800.write((char)26);
   delay(1000);
   Serial.println("SMS sent!");
    }


