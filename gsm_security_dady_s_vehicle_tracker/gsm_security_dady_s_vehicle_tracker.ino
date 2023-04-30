//#include <GSM.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////**/********************************************\**/////////////////////////////////////////////////////////////////////
////////////////////////**/          GSM VEHICLE SECURITY SYSTEM       \**/////////////////////////////////////////////////////////////////////
////////////////////////**/     DESIGNED, PROGRAMMED AND EXECUTED BY   \**/////////////////////////////////////////////////////////////////////
////////////////////////**/            KOSVIEW PRODUCTIONS             \**/////////////////////////////////////////////////////////////////////
////////////////////////**/********************************************\**/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
pin 8   // tx pin
  pin 7   // rx pin
  pin 9   // power key pin
  pin 12  // power status pin
  */


#include <gprs.h>
#include <SoftwareSerial.h>
#define TIMEOUT    5000

#include <MFRC522.h>
#include <SPI.h>

#define buzzer 4
#define SS_PIN 10
#define RST_PIN 3
#define red 2
#define green 6
#define yellow 5
int state = 0;


GPRS gprs;
//gprs.preInit();

char currentLine[20] = ""; //Variable to hold last line of serial output from SIM800
int currentLineIndex = 0;
bool nextLineIsMessage = false;
int State;
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

int code[] = {128, 13, 98, 126}; //This is the stored UID
int codeRead = 0;
String uidString;
byte startup_state = 1;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode (buzzer, OUTPUT);
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  Lock();
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Starting SIM800 SMS Command Processor");
  gprs.preInit();
  delay(1000);

  if (0 != gprs.init())
  {
    delay(1000);
    Serial.print("init error\r\n");
  }

  //Set SMS mode to ASCII
  if (0 != gprs.sendCmdAndWaitForResp("AT+CMGF=1\r\n", "OK", TIMEOUT))
  {
    ERROR("ERROR:CNMI");
    return;
  }

  //Start listening to New SMS Message Indications
  if (0 != gprs.sendCmdAndWaitForResp("AT+CNMI=1,2,0,0,0\r\n", "OK", TIMEOUT))
  {
    ERROR("ERROR:CNMI");
    return;
  }

  Serial.println("Init success");

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  smsreceiver();
  rfidcheck();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sendsmsunlocked()
{

  Serial.println("Sending sms...");
  gprs.sendSMS("+2348184422648", "Unlocked"); //define phone number and text

  Serial.println("SMS sent!");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sendsmslocked()
{
  Serial.println("Sending sms...");
  gprs.sendSMS("+2348184422648", "Locked"); //define phone number and text

  Serial.println("SMS sent!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Lock()
{
  switch (startup_state)
  {
    case  1:
    digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  delay(5000);
  startup_state = 0;
  break;
  case 0:
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  delay(5000);
  sendsmslocked();
  break;
  default:
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  delay(5000);
  sendsmslocked();
  }
  

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Unlock()
{
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
  delay (3000);
  sendsmsunlocked();

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Unl_ock()
{
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
  delay (3000);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void L_ock()
{
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void send_location()
{
  String loc_ = "";
  Serial.println("Sending sms...");
  gprs.sendSMS("+2348184422648", "Location:"); //define phone number and text

  Serial.println("SMS sent!");
}
/////////////////////////////////////////////////////////////////////////////////////////

void smsreceiver()
{
  if (gprs.serialSIM800.available()) {
    char lastCharRead = gprs.serialSIM800.read();
    //Read each character from serial output until \r or \n is reached (which denotes end of line)
    if (lastCharRead == '\r' || lastCharRead == '\n') {
      String lastLine = String(currentLine);

      //If last line read +CMT, New SMS Message Indications was received.
      //Hence, next line is the message content.
      if (lastLine.startsWith("+CMT:")) {

        Serial.println(lastLine);
        nextLineIsMessage = true;

      } else if (lastLine.length() > 0)
      {

        if (nextLineIsMessage)
        {
          Serial.println(lastLine);

          //Read message content and set status according to SMS content
          if (lastLine.indexOf("UNLOCK 5346") >= 0)
          {
            Unl_ock();
           
           
          }
          if (lastLine.indexOf("LOCK 5643") >= 0)
          {
            L_ock();
            
          }
          if (lastLine.indexOf("LOCATION 5346") >= 0)
          {
            send_location();
           
          }
          nextLineIsMessage = false;
        }
      }

      //Clear char array for next line of read
      for ( int i = 0; i < sizeof(currentLine);  ++i ) {
        currentLine[i] = (char)0;
      }
      currentLineIndex = 0;
    } else {
      currentLine[currentLineIndex++] = lastCharRead;
    }
  }
 
}


void rfidcheck()
{
  waiting();
  if (  rfid.PICC_IsNewCardPresent())
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
    Serial.println(F("INVALID!"));
    return;
  }

  Serial.println("Scanned UID:");
  printDec(rfid.uid.uidByte, rfid.uid.size);

  uidString = String(rfid.uid.uidByte[0]) + " " + String(rfid.uid.uidByte[1]) + " " + String(rfid.uid.uidByte[2]) + " " + String(rfid.uid.uidByte[3]);


  int i = 0;
  boolean match = true;
  while (i < rfid.uid.size)
  {
    if (!(rfid.uid.uidByte[i] == code[i]))
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
        Unlock();
        state = 1;
        break;
      case 1:
        Lock();
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

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
//void unlock()
//{
//  digitalWrite(buzzer, HIGH);
//    delay(100);
//     digitalWrite(buzzer, LOW);
//     delay(100);
//  digitalWrite(green, HIGH);
//   digitalWrite(red, LOW);
//delay (3000);
//}
//void lock()
//{
//  digitalWrite(buzzer, HIGH);
//    delay(100);
//     digitalWrite(buzzer, LOW);
//     delay(100);
//  digitalWrite(red, HIGH);
//   digitalWrite(green, LOW);
//delay(5000);
//}
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


