/* Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <MFRC522.h>
#include <SPI.h>


#define SS_PIN 10
#define RST_PIN 9
#define red 2
#define green 6
#define yellow 5
#define buzzer 4
int state =0;
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

int code[] = {128,13,98,126}; //This is the stored UID
int codeRead = 0;
String uidString;
void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
 
  lock();
}

void loop() {
  waiting();
  if(  rfid.PICC_IsNewCardPresent())
  {
      readRFID();
  }
  delay(500);

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

    uidString = String(rfid.uid.uidByte[0])+" "+String(rfid.uid.uidByte[1])+" "+String(rfid.uid.uidByte[2])+ " "+String(rfid.uid.uidByte[3]);
  

    int i = 0;
    boolean match = true;
    while(i<rfid.uid.size)
    {
      if(!(rfid.uid.uidByte[i] == code[i]))
      {
           match = false;
      }
      i++;
    }

    if(match)
    {
      Serial.println("\nI know this card!");

  switch (state)
  {
    case 0:
    unlock();
    state =1;
    break;
     case 1:
    lock();
    state =0;
    break;
    
  }
     // delay(3000);
    
    }else
    {
      //Serial.print(uidString);
      rejectcard();
    }
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
void unlock()
{
    digitalWrite(buzzer, HIGH);
    delay(100);
     digitalWrite(buzzer, LOW);
     delay(100);
  digitalWrite(green, HIGH);
   digitalWrite(red, LOW);
delay (3000);
}
void lock()
{
   digitalWrite(buzzer, HIGH);
    delay(100);
     digitalWrite(buzzer, LOW);
     delay(100);
  digitalWrite(red, HIGH);
   digitalWrite(green, LOW);
delay(5000);
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
}

