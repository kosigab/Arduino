
#include <LiquidCrystal.h>


#include <gprs.h>
#include <SoftwareSerial.h>
#define TIMEOUT    5000
#define relay 13
#define green 10
#define yellow 12
#define red 11

# define buzzer 15

GPRS gprs;

LiquidCrystal lcd(2,3,4,5,6,9);



int state = 0 ;
int state2 = 0;

double soil_moist = 0;


char currentLine[250] = "";
int currentLineIndex = 0;

//Boolean to be set to true if message notificaion was found and next
//line of serial output is the actual SMS message content
bool nextLineIsMessage = false;




int  pos = 0;




void setup()
{
  lcd.begin(16, 2);                      // initialize the lcd
  pinMode(green, OUTPUT);
   // pinMode(14, OUTPUT);
    pinMode(red, OUTPUT);
      pinMode(yellow, OUTPUT);
        pinMode(relay, OUTPUT);
            pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  digitalWrite (relay, HIGH);
  lcd.clear();
   lcd.setCursor(0, 0);
  lcd.print("Please wait...");
  while (!Serial);
  Serial.println("GPRS - Send SMS Test ...");

  gprs.preInit();
  delay(5000);
  while (0 != gprs.init()) {
    delay(5000);
    Serial.print("init error\r\n");
  }



   Serial.println("Init success, start to send SMS message...");

  lcd.clear();
  kosview_intro();
  //kosview_intro();
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

}
void loop()
{

  lcd.clear();
  soil_moist = analogRead(14);
  soil_moist = 1023 - soil_moist;
  soil_moist = 100 * soil_moist / 1023;
  Serial.println(soil_moist);
  lcd.setCursor(0, 0);
  lcd.print("Soil moisture =");
    lcd.setCursor(0, 1);
  lcd.print(soil_moist);
   lcd.print("%");
  delay (500);

///////////////////////////////////////////////////////////////////////////

  
  if (soil_moist < 15)
  {
    if (state == 0)
    {
      sendsms_low_moisture();
      delay (100);
      state = 1;
    }


    
    digitalWrite (relay, LOW);
    digitalWrite (buzzer, HIGH);
    digitalWrite (green, LOW);
     digitalWrite (yellow, LOW);
    
    digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (80);
     digitalWrite (red, HIGH);
    delay(30);
    digitalWrite(red, LOW);
    delay (60);
    digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (80);
     digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (60);
     digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (80);
     digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (60);
    digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (80);
     digitalWrite (red, HIGH);
    delay(100);
    digitalWrite(red, LOW);
    delay (60);
    
  }

  if (soil_moist > 70)
  {
    state =0;
    digitalWrite (relay, HIGH);
    digitalWrite (buzzer, HIGH);
    digitalWrite (green, LOW);
     digitalWrite (yellow, LOW);
    
    digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (80);
     digitalWrite (red, HIGH);
    delay(30);
    digitalWrite(red, LOW);
    delay (60);
    digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (80);
     digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (60);
     digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (80);
     digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (60);
    digitalWrite (red, HIGH);
    delay(10);
    digitalWrite(red, LOW);
    delay (80);
     digitalWrite (red, HIGH);
    delay(100);
    digitalWrite(red, LOW);
    delay (60);
    
  }

  
if ((soil_moist < 70)&&(soil_moist>15))
{
  state = 0;
         digitalWrite (relay, HIGH);
  digitalWrite (buzzer, LOW);
  digitalWrite (green, HIGH);
    delay(30);
    digitalWrite(green, LOW);
    delay (50);
     digitalWrite (green, HIGH);
    delay(20);
    digitalWrite(green, LOW);
    delay (800);
}
  
   
  
}

void kosview_intro()
{
  lcd.clear();
  lcd.setCursor(0, 0);
 
  lcd.print("| KOSVIEW      |");
  lcd.setCursor(0, 1);
  lcd.print("| PROJECTS     |");
 
  delay (1000);

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
  delay (2000);
  pos = 0;
  lcd.clear();
}


void sendsms_high_moisture()
{
  delay (1000);
  gprs.sendSMS("+2348104916575", "Soil moisture is too high"); //define phone number and text
  delay (2000);
}
void sendsms_low_moisture()
{
  delay (1000);
  gprs.sendSMS("+2348104916575", "Soil moisture is too low"); //define phone number and text
  delay (2000);
}
