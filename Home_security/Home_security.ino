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
#include <gprs.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
virtuabotixRTC myRTC(5, 4, 6);
#define TIMEOUT    5000


GPRS gprs;

char currentLine[25] = ""; //Variable to hold last line of serial output from SIM800
int currentLineIndex = 0;
bool nextLineIsMessage = false;

int  pos = 0; // This is for kosview intro

LiquidCrystal_I2C lcd(0x3F  , 20, 4); // set the LCD address to 0x3F for a 16 chars and 2 line display

/// below contains initialization of some characters.
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
#define RST_PIN 17
#define L_U 16
#define triggered 17
#define red 14

#define green 15
#define yellow 22
#define buzzer 9
//#define Alarm_parity 17
#define Door_dev_parity 16
#define Alarm_relay 3
#define Light_relay 2


int backlighttime = 0;
int Security_status = 0;
int state = 0;
bool too_many_tries = false;
int seconds = 0;
int State=0;

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



bool send_sms_for_alarm = true;
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


  // kosviewintro();
  // checkinglcdloading();

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(L_U, OUTPUT);
  pinMode(triggered, INPUT);
  //  pinMode(Alarm_parity, INPUT);
  pinMode(Door_dev_parity, INPUT);
  pinMode(Alarm_relay, OUTPUT);
  pinMode(Light_relay, OUTPUT);


  Serial.begin(9600);



  while (!Serial);
 digitalWrite(buzzer, LOW);
  Serial.println("Starting SIM800 SMS Command Processor");
  gprs.preInit();
  delay(1000);

  if (0 != gprs.init()) {
    delay(1000);
    Serial.print("init error\r\n");
  }

  //Set SMS mode to ASCII
  if (0 != gprs.sendCmdAndWaitForResp("AT+CMGF=1\r\n", "OK", TIMEOUT)) {
    ERROR("ERROR:CNMI");
    return;
  }

  //Start listening to New SMS Message Indications
  if (0 != gprs.sendCmdAndWaitForResp("AT+CNMI=1,2,0,0,0\r\n", "OK", TIMEOUT)) {
    ERROR("ERROR:CNMI");
    return;
  }

  Serial.println("Init success");





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
  delay(500);
  lock();
  //delay (2000);
  Lcd_default();
  delay (1000);
}

void loop() {
  myRTC.updateTime();

  smsreceiver();

  if (myRTC.seconds > seconds)
  {
    lcd.clear();
    Lcd_default();
    backlighttime++;
    if (backlighttime > 60)
    {
      lcd.noBacklight();
    }
  }
  if (seconds == 59 && myRTC.seconds == 0)
  {
    lcd.clear();
    Lcd_default();
  }

  if ((myRTC.hours == 00) && (myRTC.minutes == 02) && (myRTC.seconds > 47) && (myRTC.seconds > seconds))
  {
    digitalWrite(buzzer, HIGH);
    delay (100);
    digitalWrite(buzzer, LOW);
    delay (100);


    if ((myRTC.seconds == 59))
    {
      lock();
    }

  }
  seconds = myRTC.seconds;
  digitalWrite (L_U, Security_status);
  if ((myRTC.hours > 18) || (myRTC.hours > -1 && myRTC.hours < 7 ) )
  {
    digitalWrite (Light_relay, HIGH);
  }
  else
  {
    digitalWrite (Light_relay, LOW);
  }


  check_parity();
  check_if_triggered();


  readRFID();

}

void check_parity()
{
  int parity = /*digitalRead(Alarm_parity) +*/ digitalRead(Door_dev_parity);
  if (digitalRead(Door_dev_parity) == LOW)
  {
    raise_alarm();
  }

}

void check_if_triggered()
{
  int trig = digitalRead(triggered);
  if ((trig == HIGH) )//&& (Security_status == 1))
  {
    raise_alarm();
  }
}

void raise_alarm()
{
  if (send_sms_for_alarm = true)
  {
    //send sms
    send_sms_for_alarm = false;
  }
  int temp = Security_status;
  digitalWrite (Alarm_relay, HIGH);
  digitalWrite (Light_relay, HIGH);
  delay (500);
  digitalWrite (Alarm_relay, LOW);
  digitalWrite (Light_relay, LOW);
  delay (500);
  digitalWrite (Alarm_relay, HIGH);
  digitalWrite (Light_relay, HIGH);
  delay (500);
  digitalWrite (Alarm_relay, LOW);
  digitalWrite (Light_relay, LOW);
  delay (500);
  digitalWrite (Alarm_relay, HIGH);
  digitalWrite (Light_relay, HIGH);
  delay (500);
  digitalWrite (Alarm_relay, LOW);
  digitalWrite (Light_relay, LOW);
  delay (300);

  readRFID();

  delay (200);
  if (temp == Security_status)
  {

    readRFID();

    if (temp == Security_status)
    {
      raise_alarm();
    }
  }


}

void readRFID()
{

  if (  rfid.PICC_IsNewCardPresent())
  {
    lcd.backlight();
    backlighttime = 0;
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
      if ( (!(rfid.uid.uidByte[i] == code[i]))  && (!(rfid.uid.uidByte[i] == codeB[i])) && (!(rfid.uid.uidByte[i] == codeC[i])  )  ) //&& (!(rfid.uid.uidByte[i] == codeA[i]))
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
}

void printDec(byte * buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
void unlock()
{
  send_sms_for_alarm = true;
  Security_status = 0;
  s_tate = "UNLOCKED";
  too_many_tries = false;
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(30);
  digitalWrite(green, HIGH);

  digitalWrite(buzzer, HIGH);
  delay(600);
  digitalWrite(buzzer, LOW);
  // delay(100);
  digitalWrite(green, HIGH);

  digitalWrite(red, LOW);
  counter = 0;
  lcd.clear();
  lcd.print("  *****SECURITY****");
  lcd.setCursor(0, 1);
  delay (300);
  lcd.print("****UNLOCKED***");
  delay (1500);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  // lcd.print("    Welcome");

  Lcd_default();
}
void lock()
{
  send_sms_for_alarm = true;
  Security_status = 1;
  s_tate = "Security ACTIVE";
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  if (too_many_tries = false)
  {
    counter = 0;
  }


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

  Lcd_default();
}











/////////////////////////////////////////////////////////////////////////////////////









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
  // digitalWrite(red, LOW);
  delay(100);
  counter++;
  lcd.clear();
  Lcd_default();
  if (counter == 3)
  {
    too_many_tries = true;
    lock();


  }
  if (counter == 5)
  {
    too_many_tries = true;
    // lock();
    lcd.clear();
    lcd.print("Too many tries");
    delay (1000);
    lcd.setCursor(3, 2);
    lcd.print("Sending Alert...");
    //send sms
    delay(4000);
    lcd.clear();
    lcd.print("SENT!");
    delay (1000);
    lcd.clear();

  }

  if (counter == 7)
  {

    raise_alarm();
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
void Lcd_default()
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(myRTC.dayofmonth);
  lcd.print("/");
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.year);
  lcd.print(" ");



  lcd.print("(");
  lcd.print(counter);
  lcd.print(")");
  lcd.print(" ");

  lcd.setCursor(0, 1);

  if (myRTC.hours < 10)
  {
    lcd.print("0");
    lcd.print(myRTC.hours);
  }
  else
  {
    lcd.print(myRTC.hours);
  }

  // lcd.print(myRTC.hours);
  lcd.print(":");

  if (myRTC.minutes < 10)
  {
    lcd.print("0");
    lcd.print(myRTC.minutes);
  }
  else
  {
    lcd.print(myRTC.minutes);
  }

  lcd.print(":");

  if (myRTC.seconds < 10)
  {
    lcd.print("0");
    lcd.print(myRTC.seconds);
  }
  else
  {
    lcd.print(myRTC.seconds);
  }



  lcd.setCursor(0, 2);
  lcd.print("Swipe eTag...");
  lcd.setCursor(0, 3);
  lcd.print(s_tate);
}

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

      } else if (lastLine.length() > 0) {

        if (nextLineIsMessage) {
          Serial.println(lastLine);

          //Read message content and set status according to SMS content
          if (lastLine.indexOf("UNLOCK") >= 0) {
            // digitalWrite(green, HIGH);
            unlock();
            State = 1;
            //lcd.print("Waiting for SMS");
          }
          if (lastLine.indexOf("LOCK") >= 0) {
            lock();

            State = 2;
            // lcd.print("Waiting for SMS");
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
    // }
    if (State == 1)
    {
      delay(10000);
      sendsmsunlocked();
      State = 0;
      //  lcd.print("Waiting for SMS");
      return;
    }
    if (State == 2)
    {
      delay(10000);
      sendsmslocked();
      State = 0;
      //     lcd.print("Waiting for SMS");
      return;
    }
  }
}

void sendsmsunlocked()
{

  Serial.println("Sending sms...");
  gprs.sendSMS("+2348106137871", "Your vehicle was just unlocked succesfully!"); //define phone number and text



}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sendsmslocked()
{
  Serial.println("Sending sms...");
  gprs.sendSMS("+2348106137871", "Your vehicle was just locked"); //define phone number and text

  Serial.println("SMS sent!");
}


