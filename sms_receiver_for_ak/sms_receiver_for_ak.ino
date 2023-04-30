#include <gprs.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h> 
#include <Servo.h> 
Servo myservo; 

 
#define TIMEOUT    5000
#define LED_PIN    22
#define buzzer 14
#define red 15
#define green 16
#define resetter 9
 
bool ledStatus;
GPRS gprs;
int State = 0;
int counter  = 0;
String state = "";
LiquidCrystal lcd(13, 10, 5, 3, 2, 11); // pins of the LCD. (RS, E, D4, D5, D6, D7)(A0, A1, A2, A3, A4, A5)


 
void setup() {

myservo.attach(4); 
  myservo.write(45); 
  lcd.begin(16, 2);
   pinMode (red, OUTPUT);
    pinMode (buzzer, OUTPUT);
   pinMode (green, OUTPUT);
    pinMode (resetter, OUTPUT);


 Serial.println("Setup complete!");
//    lcd.print("GSM VEHICLE");
//    lcd.setCursor(0, 1);
//     lcd.print("UNLOCKING SYSTEM");
//    delay (2000);
//    lcd.clear();
//    lcd.print("A Product of:");
//    lcd.setCursor(0, 1);
//    delay (1000);
//     lcd.print("KOSVIEW PROJECTS");
//      digitalWrite(red, HIGH);
//      state = "VL";
//      delay (2000);
       lcd.clear();
    lcd.print("Please wait");
    lcd.setCursor(0, 1);
    delay (2000);
     lcd.print("LOADING...");
     delay (4000);
   


  
  Serial.begin(9600);
 while(!Serial);
 
  Serial.println("Starting SIM800 SMS Command Processor");
  gprs.preInit();
  delay(1000);
 
  if (0 != gprs.init()) {
      delay(1000);
      Serial.print("init error\r\n");
  } 
 
  //Set SMS mode to ASCII
  if(0 != gprs.sendCmdAndWaitForResp("AT+CMGF=1\r\n", "OK", TIMEOUT)) {
    ERROR("ERROR:CNMI");
    return;
  }
   
  //Start listening to New SMS Message Indications
  if(0 != gprs.sendCmdAndWaitForResp("AT+CNMI=1,2,0,0,0\r\n", "OK", TIMEOUT)) {
    ERROR("ERROR:CNMI");
    return;
  }
 
   lcd.clear();
    lcd.print("Waiting for SMS");
  Serial.println("Init success");
}
 
//Variable to hold last line of serial output from SIM800
char currentLine[500] = "";
int currentLineIndex = 0;
 
//Boolean to be set to true if message notificaion was found and next
//line of serial output is the actual SMS message content
bool nextLineIsMessage = false;


 
// 
void loop() {
  //Write current status to LED pin
  digitalWrite(LED_PIN, ledStatus);
  // lcd.clear();
  //  lcd.print("Waiting for SMS");
  //If there is serial output from SIM800
 // if(gprs.serialSIM800.available()){
    char lastCharRead = gprs.serialSIM800.read();
    //Read each character from serial output until \r or \n is reached (which denotes end of line)
    if(lastCharRead == '\r' || lastCharRead == '\n'){
        String lastLine = String(currentLine);
         
        //If last line read +CMT, New SMS Message Indications was received.
        //Hence, next line is the message content.
        if(lastLine.startsWith("+CMT:")){
           
          Serial.println(lastLine);
          nextLineIsMessage = true;
           
        } else if (lastLine.length() > 0) {
           
          if(nextLineIsMessage) {
            Serial.println(lastLine);
             
            //Read message content and set status according to SMS content
            if(lastLine.indexOf("UNLOCK NOW") >= 0){
             // digitalWrite(green, HIGH);
              Unlock();
              State =1;
               //lcd.print("Waiting for SMS");
            } else if(lastLine.indexOf("LOCK NOW") >= 0) {
              Lock();
              State =2;
              // lcd.print("Waiting for SMS");
            }
             
            nextLineIsMessage = false;
          }
           
        }
         
        //Clear char array for next line of read
        for( int i = 0; i < sizeof(currentLine);  ++i ) {
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
      State =0;
     lcd.print("Waiting for SMS");
     return;
    }
    if (State == 2)
  {
    delay(10000);
      sendsmslocked();
      State =0;
     lcd.print("Waiting for SMS");
     return;
    }
}

 void Lock()
    {
     // counter = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
       digitalWrite(green, LOW);
       state = "VL";
      digitalWrite(red, HIGH);
       myservo.write(50); 
      lcd.print("Vehicle locked!");
       digitalWrite(buzzer, HIGH);
       delay (1000);
       digitalWrite(buzzer, LOW);
     //  delay(10000);
    //  sendsmslocked();
//      Posi_tion = 0;
      delay(3000);
    //  digitalWrite(red, LOW);
      lcd.clear();
      }

void Unlock()
      {
        counter =0;
         state = "VU";
        lcd.clear();
       lcd.setCursor(0, 0);
        digitalWrite(red, LOW);
       digitalWrite(green, HIGH);
        myservo.write(180);   
       lcd.print("Vehicle unlocked!");
         delay (300);
       digitalWrite(buzzer, HIGH);
       delay (300);
       digitalWrite(buzzer, LOW);
       delay (100);
       digitalWrite(buzzer, HIGH);
       delay (300);
       digitalWrite(buzzer, LOW);
       delay (100);
        digitalWrite(buzzer, HIGH);
       delay (300);
       digitalWrite(buzzer, LOW);
       
//      sendsmsunlocked();
//       Posi_tion = 0;
       delay(3000);
     //  digitalWrite(green, LOW);
       lcd.clear();
        }




void sendsmsunlocked()
  {
    
     Serial.println("Sending sms...");
      gprs.sendSMS("+2348106137871","Your vehicle was just unlocked succesfully!"); //define phone number and text
//   serialSIM800.write("AT+CMGF=1\r\n");
//   delay(1000);
//
//   serialSIM800.write("AT+CMGS=\"+2348106137871\"\r\n");//+2348173125515
//   delay(1000);
//   serialSIM800.write("Your vehicle was just unlocked succesfully!");
//   delay(1000);
//
//   serialSIM800.write((char)26);
//   lcd.setCursor(0,1);
   lcd.print("Sms sent!");
   
   delay(1000);
   lcd.clear();
   Serial.println("SMS sent!");
  
   
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void sendsmslocked()
  {
     Serial.println("Sending sms...");
     gprs.sendSMS("+2348106137871","Your vehicle was just locked"); //define phone number and text
// 
//   serialSIM800.write("AT+CMGF=1\r\n");
//   delay(1000);
//
//   serialSIM800.write("AT+CMGS=\"+2348106137871\"\r\n");//+2348173125515
//   delay(1000);
//   serialSIM800.write("Your vehicle was just locked!");
//   delay(1000);
//
//   serialSIM800.write((char)26);
   lcd.setCursor(0,1);
    lcd.print("Sms sent!");
   
   delay(1000);
   lcd.clear();
   Serial.println("SMS sent!");
    }

