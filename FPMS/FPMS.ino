

#define blue 13
#define green 12
#define red 11
#define buzzer 10
#define ph_monitor 14
#define turbidity_monitor1 15
#define turbidity_monitor2 16
//#include <Wire.h>
#include <LiquidCrystal.h>
#include <gprs.h>
#include <SoftwareSerial.h>
#include <stdio.h>
#define TIMEOUT    5000

GPRS gprs;
LiquidCrystal lcd(2, 3, 4, 5, 6, 9);
int state = 0;
double ph_gradient = 0;
double turbidity_gradient = 0;
double ph_impurity = 0;
double turbidity_impurity = 0;
double impurity = 0;
double ph = 0;
double ph_analog_value = 0;
int turbidity = 0;


//Variable to hold last line of serial output from SIM800
  char currentLine[250] = "";
  int currentLineIndex = 0;

  //Boolean to be set to true if message notificaion was found and next
  //line of serial output is the actual SMS message content
  bool nextLineIsMessage = false;



int  pos = 0;

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


void setup()
{
  lcd.begin (20, 4);
  lcd.setCursor(0, 0);
  kosview_intro();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("GPRS - Send SMS Test ...");
  gprs.preInit();
  delay(1000);
  while (0 != gprs.init()) {
    delay(1000);
    Serial.print("init error\r\n");
  }

  pinMode (ph_monitor, INPUT);
  pinMode (turbidity_monitor1, INPUT);
  pinMode (turbidity_monitor2, INPUT);
  pinMode (blue, OUTPUT);
  pinMode (green, OUTPUT);
  pinMode (red, OUTPUT);
  pinMode (buzzer, OUTPUT);

  lcd.createChar(10, f1);
  lcd.createChar(1, f2);
  lcd.createChar(2, f3);
  lcd.createChar(3, f4);
  lcd.createChar(4, f5);
  lcd.createChar(5, f6);

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


  

  // kosview_intro();
  checkinglcdloading();

}
void loop()
{
  measure_PH();
  measure_turbidity();
  Impurity_level();

  if (impurity > 30)
  {

    high_impurity();
    if (state == 0)
    {
      sendsms_high_impurity();
      state = 1;
    }

  }
  else
  {
    low_impurity();
    state = 0;

  }
sms_receiver();
  delay(1000);
  lcd.clear();
}
void measure_PH()
{
  ph_analog_value = analogRead(ph_monitor);
  ph = (7.0 / 390) * ph_analog_value;
  Serial.print("ph analog reading = ");
  Serial.println(ph_analog_value);
  Serial.print("ph = ");
  Serial.println(ph);
  lcd.setCursor(0, 0);
  lcd.print("PH = ");
  lcd.print(ph);
  delay (10);

}

void measure_turbidity()
{
  turbidity = analogRead(turbidity_monitor1);
  turbidity = turbidity - 800;
  Serial.print("turbidity1 = ");
  Serial.println(turbidity);
  lcd.setCursor(0, 1);
  lcd.print("Turbidity = ");
  lcd.print(turbidity);
  delay(100);
}



void Impurity_level()
{
  ph_gradient = (ph - 7)*1.0;
  if(ph_gradient<0)
  {
    ph_gradient = ph_gradient*-1;
  }
 // ph_gradient = abs(ph_gradient);
  ph_impurity = 1.0*(100 * ph_gradient) / 7;

  
  turbidity_impurity = (100 * (turbidity)) / 1023;

  if (ph_impurity > turbidity_impurity)
  {
    impurity = ph_impurity;
  }
 
  if (ph_impurity < turbidity_impurity)
  {
    impurity = turbidity_impurity;
  }
  impurity = abs(impurity);
  lcd.setCursor(0, 2);
  lcd.print("Impurity ");
  lcd.setCursor(3, 3);
  lcd.print("-index = ");
  lcd.print(impurity);
  lcd.print("%");
}

void low_impurity()
{
    digitalWrite (buzzer, LOW);
  digitalWrite (blue, HIGH);
  delay(30);

  digitalWrite (blue, LOW);

  delay (30);
  digitalWrite (green, HIGH);
  delay (30);
  digitalWrite (green, LOW);
}


void high_impurity()
{
  
  digitalWrite (red, HIGH);
    digitalWrite (buzzer, HIGH);
  delay(60);

  digitalWrite (red, LOW);

  delay (60);
  digitalWrite (red, HIGH);
  delay (60);
  digitalWrite (red, LOW);
  delay (60);
  digitalWrite (red, HIGH);
  delay(30);

  digitalWrite (red, LOW);

  delay (30);
  digitalWrite (red, HIGH);
  delay (30);
  digitalWrite (red, LOW);
}
void kosview_intro()
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

  do {
    lcd.scrollDisplayLeft();
    pos++;
    delay(5);
  }
  while (pos < 40);

  pos = 0;

  do {
    lcd.scrollDisplayRight();
    pos++;
    delay(5);
  }
  while (pos < 40);
  delay (1000);
  pos = 0;
  lcd.clear();
}

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
//void sendsms_high_turbidity()
//{
//  delay (1000);
//  gprs.sendSMS("+2347031073965","High turbidity detected"); //define phone number and text
//  delay (1000);
//}
void sendsms_high_ph()
{
  delay (1000);
  gprs.sendSMS("+2347031073965", "Water is too Alkaline."); //define phone number and text
  delay (1000);
}
void sendsms_high_impurity()
{
  delay (1000);
  gprs.sendSMS("+2347031073965", "Dirty water! Water change is recommended."); //define phone number and text
  delay (1000);
}
void sendsms_low_ph()
{
  delay (1000);
  gprs.sendSMS("+2347031073965", "Water is too Acidic."); //define phone number and text
  delay (1000);
}
void sendstatus()
{
  delay (1000);
   gprs.sendSMS("+2347031073965", "Retreiving status..." );
    delay (1000);
  char *intStr_impurity = itoa(impurity, intStr_impurity, impurity);
  char *intStr_ph = itoa(ph, intStr_ph, ph);

  String impurity_sms_pa = " The water impurity index = ";
  String ph_sms_pa = " The ph is = ";
  String ph_str = String (intStr_ph);
  String ph_sms_str = ph_sms_pa + ph_str;
  String impurity_str = String(intStr_impurity);
  String impurity_sms_str = impurity_sms_pa + impurity_str + ph_sms_str ;
  char *impurity_sms = new char[impurity_sms_str.length() + 1];
  strcpy(impurity_sms, impurity_sms_str.c_str());
  delete [] impurity_sms;
  gprs.sendSMS("+2347031073965", impurity_sms ); //define phone number and text


  // char turb = char(intStr);
  //  gprs.sendSMS("+2347031073965",intStr); //define phone number and text
}


void sms_receiver()
{
  //If there is serial output from SIM800
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
          if (lastLine.indexOf("STATUS") >= 0) {
            delay(1000);
            sendstatus();
            delay(1000);
          }

          nextLineIsMessage = false;
        }

      }

      //Clear char array for next line of read
      for ( int i = 0; i < sizeof(currentLine);  ++i ) {
        currentLine[i] = (char)0;
      }
      currentLineIndex = 0;
    } 
    else {
      currentLine[currentLineIndex++] = lastCharRead;
    }
  }
}
