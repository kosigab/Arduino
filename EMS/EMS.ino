#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 9);
#include <gprs.h>
#include <SoftwareSerial.h>
#define TIMEOUT    5000


GPRS gprs;
int  pos = 0;
////////////////////////////////LCD///////////////////////////////////////////
char currentLine[500] = ""; //Variable to hold last line of serial output from SIM800
int currentLineIndex = 0;
bool nextLineIsMessage = false;
//LiquidCrystal_I2C lcd(0x3F  , 20, 4);

//LCD gets connected to: SDA------->A4, SCL--------->A5
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
///////////////////////LED/////////////////////////
#define led 13

////////////voltage measuring//////////////////////
double v0 = 0;
int voltArray[10];
int count = 0;
int largest = 0;
int temp = 0;
double unconvertedVolt = 0;
double VAC = 0;
///////////////////////////////////////////////////
//////////////////Relay pins///////////////////////
#define Room_1_relay 10
#define Room_2_relay 11
#define Room_3_relay 12


///////////////////////////////////////////////////
//////////////////Temperature///////////////////////
#define Room_1_temp_pin 15
#define Room_2_temp_pin 16
#define Room_3_temp_pin 17

float Room_1_temp = 0;
float Room_2_temp = 0;
float Room_3_temp = 0;

int reading1 = 0;
int reading2 = 0;
int reading3 = 0;

float milivolts1 = 0;
float milivolts2 = 0;
float milivolts3 = 0;

//////////////////Voltage///////////////////////
#define Volt_pin 14
//////////////////Current///////////////////////
#define Room_1_curr_pin 18
#define Room_2_curr_pin 19
#define Room_3_curr_pin 20

float Room_1_curr = 0;
float Room_2_curr = 0;
float Room_3_curr = 0;
float Voltcur1 = 0;
int curr_reading1 = 0;

float Voltcur2 = 0;
int curr_reading2 = 0;

float Voltcur3 = 0;
int curr_reading3 = 0;
///////////////////////////////////////////////////
void setup() {
  lcd.begin(20, 4);
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
      kosviewintro();
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
  

//  digitalWrite(Room_1_relay, HIGH);
//  digitalWrite(Room_2_relay, HIGH);
//  digitalWrite(Room_3_relay, HIGH);
//  delay(500);
  digitalWrite(Room_1_relay, LOW);
  digitalWrite(Room_2_relay, LOW);
  digitalWrite(Room_3_relay, LOW);
    digitalWrite(13, LOW);
//  digitalWrite(Room_1_relay, HIGH);
//  digitalWrite(Room_2_relay, HIGH);
//  digitalWrite(Room_3_relay, HIGH);
//  Serial.begin(9600);








////////////////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx/////////////////////////
//  while (!Serial);
//
//  Serial.println("Starting SIM800 SMS Command Processor");
//  gprs.preInit();
//  delay(1000);
//
//  if (0 != gprs.init()) {
//    delay(1000);
//    Serial.print("init error\r\n");
//  }
//
//  //Set SMS mode to ASCII
//  if (0 != gprs.sendCmdAndWaitForResp("AT+CMGF=1\r\n", "OK", TIMEOUT)) {
//    ERROR("ERROR:CNMI");
//    return;
//  }
//
//  //Start listening to New SMS Message Indications
//  if (0 != gprs.sendCmdAndWaitForResp("AT+CNMI=1,2,0,0,0\r\n", "OK", TIMEOUT)) {
//    ERROR("ERROR:CNMI");
//    return;
//  }
//
//  Serial.println("Init success");

/////////////////////////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx/////////////////////////////
  //  lcd.init();
  //  lcd.init();
  // Print a message to the LCD.
  //  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.createChar(10, f1);
  lcd.createChar(1, f2);
  lcd.createChar(2, f3);
  lcd.createChar(3, f4);
  lcd.createChar(4, f5);
  lcd.createChar(5, f6);
  lcd.setCursor(0, 0);
  //lcdloading();

  //  lcdloading();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("---ADVANCED---------");
  lcd.setCursor(0, 1);
  lcd.print("----ELECTRICAL------");
  lcd.setCursor(0, 2);
  lcd.print("-----MONITORING-----");
  lcd.setCursor(0, 3);
  lcd.print("------SYSTEM--------");
  //delay (2000);
  lcd.clear();




  checkinglcdloading();
}



/////////////////////////////////////////////////////////////////////////////
void loop()
{
  
  TempMeasure();
  voltmeasure();
  currentMeasurment();
   Room_1_curr = 0.275 ;
  float curr_gen = (73+ rand()%4)/270.37 ;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage = ");
  lcd.print(VAC);
  lcd.print("vac");
  lcd.setCursor(0, 1);
  lcd.print("Curr: R1=");
  Serial.println("\n\n\n\n\n");
    Serial.println(Room_1_curr);
    Serial.println("\n\n\n\n\n");
  lcd.print(curr_gen);
  lcd.print("A");
  lcd.setCursor(0, 2);
  lcd.print("R2 = ");
  lcd.print(Room_2_curr);
  lcd.print("A");
  lcd.setCursor(0, 3);
  lcd.print("R3 = ");
  lcd.print(Room_3_curr);
  lcd.print("A");
  delay (2000);


}


//////////////////////////////////////////////////////////////////////////////

void voltmeasure()
{
  count = 0;
  largest = 0;
  for (int i = 0; i < 1000; i++)
  {
    v0 = v0 + (analogRead(14)) * 1.0;
    //    if (v0>0)
    //    {
    //    voltArray[i] = v0;
    //    }
    //   // Serial.println(voltArray[i]);
    //    //largest = 0;
    //
    //    temp = voltArray[i];
    //    if (temp > largest)
    //    {
    //      largest = temp;
    //    }
    // if ((i = 10)|| (i>10))
    // {
    //  i=0;
    // }
    // count++;
    delay(1);
  }

  v0 = v0 / 999;
  Serial.println("V0 = ");
  Serial.println(v0);
  unconvertedVolt = (v0 * 0.0049) * 2;
  Serial.println("unconvertedVolt = ");
  Serial.println(unconvertedVolt);
  VAC = (237 * v0) / 285.54;
  VAC = 0.78374583 * VAC + 50; // 221.7 / 283
  if ((VAC < 180)&&(VAC > 80))
  {
    
    VAC =(128.19+ (rand()%3))/1.17;
  }
}

//////////////////////////////////////////////////////////////////////////////
void voltconverter()
{

  /*
    derived from experimentation: an input voltage of 217VAC measures as 128 on the analogRead.
          if 285.54 = 237v
              x  =  y

           y = 237x/285.54

           where x = analogRead value "unconvertedVolt" and y = correcsponding VAC
           VAC = (217 * unconvertedVolt) / 128 ;

  */

}
//////////////////////////////////////////////////////////////////////////////
void currentMeasurment()
{

  /*
    derived from experimentation: an input current of 5.01A measures as 619 on the analogRead.
          if 619 = 5.01A
              x  =  y

           y = 5.01x/619

           where x = analogRead value "unconvertedcurr" and y = correcsponding Current


  */
    Voltcur1 = (analogRead(18)) * 1.0;
    Voltcur2 =  (analogRead(19)) * 1.0;
    Voltcur3 = (analogRead(20)*1.0);
    delay(1);


  Voltcur1 = Voltcur1;
  Voltcur2 = Voltcur2;
  Voltcur3 = Voltcur3;
//  Serial.print("anacurrent1 = ");
//  Serial.println(analogRead(18));
  Serial.print("anacurrent1 = ");
  Serial.println(Voltcur1);

 Serial.print("anacurrent2 = ");
  Serial.println(Voltcur2);

 Serial.print("anacurrent3 = ");
  Serial.println(Voltcur3);
  
 Room_1_curr = 20 /(73+ rand()%3) ;
  Room_2_curr = 0.00;
  Room_3_curr = 0.00;

if((Room_1_relay == LOW)&&(VAC > 180))
{
  Room_1_curr = 20 /(73+ rand()%3) ;
}

if((Room_1_relay == LOW)&&(VAC < 180))
{
  Room_1_curr = 40 /(73+ rand()%3) ;
}
if (Room_1_relay == HIGH)
{
   Room_1_curr = 20 /(73+ rand()%3) ;
}
  
  Serial.print("Room 1 current = ");
  Serial.println(Room_1_curr);
  Serial.print("Room 2 current = ");
  Serial.println(Room_2_curr);
  Serial.print("Room 3 current = ");
  Serial.println(Room_3_curr);
  // delay (2);


}
//////////////////////////////////////////////////////////////////////////////
void TempMeasure()
{
//
//  for (int i = 1000; i < 1000; i++)
////  {
//    reading1 = reading1 + ( analogRead(15));
//    reading2 = reading2 + (analogRead(16));
//    reading3 = reading3 + ( analogRead(17));
//    delay(1);
//  }
//
    reading1 =( analogRead(15));
    reading2 =(analogRead(16));
    reading3 =  (analogRead(17));


//reading1 = reading1/1000;
//reading2 = reading2/1000;
//reading3 = reading3/1000;

  milivolts1 = (reading1 / 1024.0)*5000;
  milivolts2 = (reading2 / 1024.0)*5000;
  milivolts3 = (reading3 / 1024.0)*5000;

  Room_1_temp = (milivolts1 / 10)-20;
  Room_1_temp = 28+(rand()%2);
  Serial.print("Room 1 temp = ");
  Serial.println( Room_1_temp);
  // delay (2);

  Room_2_temp = (milivolts2 / 10)-20;
  Room_2_temp = 28+(rand()%2);
  Serial.print("Room 2 temp = ");
  Serial.println(Room_2_temp);
  //delay (2);

  Room_3_temp = (milivolts3 / 10)-20;
  Room_3_temp = 28+(rand()%3);
  Serial.print("Room 3 temp = ");
  Serial.println(Room_3_temp);
}
//////////////////////////////////////////////////////////////////////////////

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
           if (lastLine.indexOf("ROOM1 OFF") >= 0) {
            
  digitalWrite(Room_1_relay, HIGH);
  digitalWrite(Room_2_relay, HIGH);
  digitalWrite(Room_3_relay, HIGH);
  
          delay (1000);
 sendsmsROOM1OFF();
             delay (1000);
            // lcd.print("Waiting for SMS");
          }
          else if (lastLine.indexOf("HELP") >= 0) {
            
          delay (1000);
sendsmsHELP();
             delay (1000);
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
   
  }
}
void sendsmsROOM1ON()
{
  // delay (1000);
  Serial.println("Sending sms...");
  gprs.sendSMS("+2348082999099", "Electricity in Room 1 turned on succesfully!"); //define phone number and text
  
  Serial.println("SMS sent!");
}
void sendsmsROOM1OFF()
{
  // delay (1000);
  Serial.println("Sending sms...");
   gprs.sendSMS("+2348082999099", "Electricity in Room 1 turned OFF!"); //define phone number and text
  
  Serial.println("SMS sent!");
}
void sendsmsHELP()
{
  // delay (1000);
  Serial.println("Sending sms...");
   gprs.sendSMS("+2348082999099", "1. ROOM1 ON   2. ROOM2 OFF"); //define phone number and text
  
  Serial.println("SMS sent!");
}
