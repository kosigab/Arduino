/* Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


int  pos = 0;

LiquidCrystal_I2C lcd(0x3F  , 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
byte f1[8] = {
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b01010,
  0b10001,
  0b10001,
  0b11111
};
byte f2[8] = {
  0b11111,
  0b11011,
  0b01110,
  0b00100,
  0b01010,
  0b10001,
  0b10101,
  0b11111
};
byte f3[8] = {
  0b11111,
  0b10001,
  0b01110,
  0b00100,
  0b01010,
  0b10001,
  0b11111,
  0b11111
};
byte f4[8] = {
  0b11111,
  0b10001,
  0b01110,
  0b00100,
  0b01010,
  0b10101,
  0b11111,
  0b11111
};
byte f5[8] = {
  0b11111,
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b11111,
  0b11111,
  0b11111
};
byte f6[8] = {
  0b11111,
  0b10001,
  0b01010,
  0b00000,
  0b01110,
  0b11111,
  0b11111,
  0b11111
};


#define SS_PIN 10
#define RST_PIN 9
#define red 2
#define green 6
#define yellow 1
#define buzzer 4
int state = 0;

MFRC522 rfid(SS_PIN, 0); // Instance of the class

MFRC522::MIFARE_Key key;

int code[] = {128, 13, 98, 126}; //This is the stored UID
int codeA[] = {81, 137, 224, 46};//{81, 137, 223, 46};
int codeB[] = {81, 69, 42, 46};
int codeC[] = {70, 82, 142, 141};
int codeD[] = {118, 203, 140, 141};
int codeRead = 0;
String uidString;
String star = "";


int counter  = 0;
String s_tate = "";


void setup() {
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.createChar(0, f1);
  lcd.createChar(1, f2);
  lcd.createChar(2, f3);
  lcd.createChar(3, f4);
  lcd.createChar(4, f5);
  lcd.createChar(5, f6);
  lcd.setCursor(0, 0);


//   kosviewintro();
//  checkinglcdloading();

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EJIMONU ");
  delay(100);
  lcd.setCursor(4, 1);
  lcd.print("RESIDENCE");
  delay(100);
  lcd.setCursor(5, 2);
  lcd.print("HOME SECURITY");
  delay(100);
  lcd.setCursor(13, 3);
  lcd.print("SYSTEM");
  delay(100);
  //lock();
  //delay (2000);
  lcd.clear();
  lcd.print("Enter Pin");
  lcd.print(" ");
  lcd.print("(");

  lcd.print(counter);
  lcd.print(")");
  lcd.print(" ");
  lcd.print(s_tate);
  //  pinMode (servo, OUTPUT);
  delay (1000);
}

void loop() {


    if (  rfid.PICC_IsNewCardPresent())
    {
      readRFID();
    }

}


void readRFID()
{

  rfid.PICC_ReadCardSerial();
  Serial.print(F("\nPICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  Serial.println("Scanned PICC's UID:");
  printDec(rfid.uid.uidByte, rfid.uid.size);

  uidString = String(rfid.uid.uidByte[0]) + " " + String(rfid.uid.uidByte[1]) + " " + String(rfid.uid.uidByte[2]) + " " + String(rfid.uid.uidByte[3]);


  int i = 0;
  boolean match = true;
  while (i < rfid.uid.size)
  {
    if (           (!(rfid.uid.uidByte[i] == code[i]))  && (!(rfid.uid.uidByte[i] == codeB[i])) && (!(rfid.uid.uidByte[i] == codeC[i])  )  ) //&& (!(rfid.uid.uidByte[i] == codeA[i]))
    {
      match = false;
    }
    i++;
  }

  if (match)
  {
    Serial.println("\nI know this card!");

    switch (state)
    {
      case 0:
        unlock();
        state = 1;
        break;
      case 1:
        lock();
        state = 0;
        break;

    }
    // delay(3000);

  } else
  {
    //Serial.print(uidString);
    rejectcard();
  }
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

void printDec(byte * buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
void unlock()
{
  digitalWrite(buzzer, HIGH);
  delay(30);
  digitalWrite(buzzer, LOW);
  delay(30);
  digitalWrite(green, HIGH);

digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
 // delay(100);
  digitalWrite(green, HIGH);
  
  digitalWrite(red, LOW);
  counter = 0;
  lcd.clear();
  lcd.print("  *****SECURITY****");
  lcd.setCursor(0, 1);
  delay (500);
  lcd.print("****DE-ACTIVATED!***");
  delay (1500);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  // lcd.print("    Welcome");

  lcd.print("Enter Pin");
  lcd.print(" ");
  lcd.print("(");
  lcd.print(counter);
  lcd.print(")");
  lcd.print(" ");
  lcd.print(s_tate);
}
void lock()
{
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  counter = 0;
  lcd.clear();
  lcd.print(" *****SECURITY****");
  lcd.setCursor(0, 1);
  delay (500);
  lcd.print("*****ACTIVATED!****");
  delay (1500);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  // lcd.print("    Welcome");

  lcd.print("Enter Pin");
  lcd.print(" ");
  lcd.print("(");
  lcd.print(counter);
  lcd.print(")");
  lcd.print(" ");
  lcd.print(s_tate);
}
void waiting()
{
  digitalWrite(yellow, HIGH);
  delay(50);
  digitalWrite(yellow, LOW);
}
void rejectcard()
{
  digitalWrite(buzzer, HIGH);
  digitalWrite(red, HIGH);
  delay(100);
  Serial.println("\nUnknown Card");

  digitalWrite(buzzer, LOW);
  digitalWrite(red, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  digitalWrite(red, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  digitalWrite(red, LOW);
  delay(100);
  counter++;
   lcd.clear();
  lcd.print("Enter Pin");
  lcd.print(" ");
  lcd.print("(");

  lcd.print(counter);
  lcd.print(")");
  lcd.print(" ");
  lcd.print(s_tate);
  if(counter > 3)
  {
    lock();
    
//    for (int i=0; i <1000; i++)
//    {
//      digitalWrite (buzzer, 1);
//      digitalWrite (red, 1);
//      delay (1000);
//      digitalWrite (buzzer, 0);
//      digitalWrite (red, 0);
//       delay (1000);
//    }
  }
}
void lcdloading()
{
  for (int i = 0; i < 3; i++)
  {
    lcd.setCursor(10, 1);
    lcd.write(10);
    delay (300);
    lcd.clear();
    lcd.setCursor(10, 1);
    lcd.write(1);
    delay (300);
    lcd.clear();
    lcd.setCursor(10, 1);
    lcd.write(2);
    delay (300);
    lcd.clear();
    lcd.setCursor(10, 1);
    lcd.write(3);
    delay (300);
    lcd.clear();
    lcd.setCursor(10, 1);
    lcd.write(4);
    delay (300);
    lcd.clear();
    lcd.setCursor(10, 1);
    lcd.write(5);
    delay (300);
    lcd.clear();
    delay (2);

  }
}
/////////////////////////////////////////////////////
void checkinglcdloading()
{
  for (int i = 0; i < 3; i++)
  {
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(10);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(1);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(2);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(3);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(4);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(5);
    delay (300);
    lcd.clear();
    delay (2);

  }
}
void kosviewintro()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("----------_________.");
  lcd.setCursor(0, 1);
  lcd.print("|     KOSVIEW      |");
  lcd.setCursor(0, 2);
  lcd.print("|     PROJECTS     |");
  lcd.setCursor(0, 3);
  lcd.print("----------_________|");
  delay (2000);

  do
  {
    lcd.scrollDisplayLeft();
    pos++;
    delay(5);
  }
  while (pos < 40);

  pos = 0;

  do
  {
    lcd.scrollDisplayRight();
    pos++;
    delay(5);
  }
  while (pos < 40);
  delay (1000);
  pos = 0;
  lcd.clear();



}

