/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////************************************************/////////////////////////////////////////////////////////////////////
////////////////////////**          GSM VEHICLE SECURITY SYSTEM       **/////////////////////////////////////////////////////////////////////
////////////////////////**     DESIGNED, PROGRAMMED AND EXECUTED BY   **/////////////////////////////////////////////////////////////////////
////////////////////////**            KOSVIEW PRODUCTIONS             **/////////////////////////////////////////////////////////////////////
////////////////////////************************************************/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <gprs.h>
#include <LiquidCrystal.h> 
#include <Keypad.h>
#include <SoftwareSerial.h>
#define TIMEOUT    5000
//#define LED_PIN    0
#include <Servo.h> 
Servo myservo; 
//bool ledStatus;
//GPRS gprs;

#define buzzer 9
#define red 21
#define green 20
#define SIM800_TX_PIN 1
#define SIM800_RX_PIN 0
//SoftwareSerial serialSIM800(SIM800_TX_PIN, SIM800_RX_PIN);

GPRS gprs;
// gprs.preInit();
char* password ="0000"; //create a password
int Posi_tion = 0; //keypad position
int flag = 0;
int x=0;
int y;
int pos = 0;  
int counter  = 0;
String state = "";
char currentLine[500] = ""; //Variable to hold last line of serial output from SIM800
int currentLineIndex = 0;
bool nextLineIsMessage = false;


const byte rows = 4; //number of the keypad's rows and columns
const byte cols = 4;

char keyMap [rows] [cols] = { //define the cymbols on the buttons of the keypad

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
////PIN 8 is BAD!!!
byte rowPins [rows] = {14, 15, 16, 17}; //pins of the keypad
byte colPins [cols] = {18, 19, 11, 4}; 

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols);

LiquidCrystal lcd(13, 10, 5, 3, 2, 12); // pins of the LCD. (RS, E, D4, D5, D6, D7)(A0, A1, A2, A3, A4, A5)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{ 
 myservo.attach(1); 
  myservo.write(45); 
  lcd.begin(16, 2);
   pinMode (red, OUTPUT);
    pinMode (buzzer, OUTPUT);
   pinMode (green, OUTPUT);
   Serial.begin(9600);
//  while (!Serial) {
////    serialSIM800.begin(9600);
//    delay(1000);
//      
//      }
//      serialSIM800.begin(9600);
    delay(1000);




//    
//  




    Serial.println("Setup complete!");
    lcd.print("GSM VEHICLE");
    lcd.setCursor(0, 1);
     lcd.print("UNLOCKING SYSTEM");
    delay (2000);
    lcd.clear();
    lcd.print("A Product of:");
    lcd.setCursor(0, 1);
    delay (1000);
     lcd.print("KOSVIEW PROJECTS");
      digitalWrite(red, HIGH);
      state = "VL";
      delay (2000);
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
 
  if(0 != gprs.init()) {
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
 
  Serial.println("Init success");



   // delay (2000);
    lcd.clear();
    lcd.print("Enter Pin");
    lcd.print(" ");
    lcd.print("(");
    
    lcd.print(counter);
    lcd.print(")");
    lcd.print(" ");
    lcd.print(state);
//  pinMode (servo, OUTPUT);
delay (1000);
  myservo.write(50); 
  delay (1000);
//  setLocked (true); //state of the password





//Boolean to be set to true if message notificaion was found and next
//line of serial output is the actual SMS message content


  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop(){
  smsreceiver();
  char whichKey = myKeypad.getKey(); //define which key is pressed with getKey
    int l;
  if (int(whichKey)!=0){
    lcd.clear();
 lcd.setCursor(0, 0);
 // lcd.print("    Welcome");
  
  lcd.print("Enter Pin");
   lcd.print(" ");
    lcd.print("(");
    lcd.print(counter);
    lcd.print(")");
    lcd.print(" ");
    lcd.print(state);
  lcd.setCursor(0, 1);
   for (l=0; l<=Posi_tion; ++l)
    {
      lcd.print("*");
       digitalWrite(buzzer, HIGH);
       delay (30);
       digitalWrite(buzzer, LOW);
    }

  if(whichKey == '*' || whichKey == '#' || whichKey == 'A' ||       //define invalid keys
  whichKey == 'B' || whichKey == 'C' || whichKey == 'D'){

    Posi_tion=0;
//    setLocked (true);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Invalid Key!");
    delay(1000);
    lcd.clear();
  }
  if(whichKey == password [Posi_tion]){

    Posi_tion ++;
  }
  if(Posi_tion == 4)
  {
     if (flag == 0 && x == 0)
    {
     
     y=1;
       Unlock();
       state = "VU";
       flag = 1;
       x = 0;
    }
    if(flag == 1 && x == 1)
    {
      
      y=0;
      Lock();
      flag = 0;
      x = 0;

    }
   if (y == 1)x = 1;
       
     lcd.print("Enter Pin");
     lcd.print(" ");
    lcd.print("(");
    
    lcd.print(counter);
    lcd.print(")");
     lcd.print(" ");
    lcd.print(state);
    lcd.setCursor(0, 0);
   }
   
   
  
  else if(whichKey != password [Posi_tion]){
//     setLocked (true);
     lcd.clear();
      digitalWrite(red, HIGH);
     lcd.print("*****ACCESS*****");
     lcd.setCursor(0,1);
     delay (500);
     lcd.print("*****DENIED*****");
     delay (1500);
     x=0;
     flag = 0;
    
      Posi_tion = 0;
     // call();
     // delay (10000);
     counter=counter+1;
//     if (counter == 3)
//     {
//       Lock();
//      sendsmslockedDuetoinvalidcode();
//      }
      if (counter == 3)
      {
         counterlimitreached3();
      }
      if (counter > 5)
      {
         counterlimitreached5();
      }
      
      delay (3000);
     // digitalWrite(red, LOW);
      lcd.clear();
      lcd.print(" Enter Pin");
      lcd.print(" ");
    lcd.print("(");
    
    lcd.print(counter);
    lcd.print(")");
       
      
  }
  
 }//2
  delay(100);
}//1


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void sendsmsunlocked()
//  {
//    
//     Serial.println("Sending sms...");
//      gprs.sendSMS("+2348082999099","Your vehicle was just unlocked succesfully!"); //define phone number and text
////   serialSIM800.write("AT+CMGF=1\r\n");
////   delay(1000);
////
////   serialSIM800.write("AT+CMGS=\"+2348082999099\"\r\n");//+2348173125515
////   delay(1000);
////   serialSIM800.write("Your vehicle was just unlocked succesfully!");
////   delay(1000);
////
////   serialSIM800.write((char)26);
////   lcd.setCursor(0,1);
//   lcd.print("Sms sent!");
//   
//   delay(1000);
//   lcd.clear();
//   Serial.println("SMS sent!");
//  
//   
//    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    void sendsmslocked()
//  {
//     Serial.println("Sending sms...");
//     gprs.sendSMS("+2348082999099","Your vehicle was just locked"); //define phone number and text
//// 
////   serialSIM800.write("AT+CMGF=1\r\n");
////   delay(1000);
////
////   serialSIM800.write("AT+CMGS=\"+2348082999099\"\r\n");//+2348173125515
////   delay(1000);
////   serialSIM800.write("Your vehicle was just locked!");
////   delay(1000);
////
////   serialSIM800.write((char)26);
//   lcd.setCursor(0,1);
//    lcd.print("Sms sent!");
//   
//   delay(1000);
//   lcd.clear();
//   Serial.println("SMS sent!");
//    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
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
    //  sendsmslocked();
      Posi_tion = 0;
      delay(3000);
    //  digitalWrite(red, LOW);
      lcd.clear();
      }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
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
   //   sendsmsunlocked();
       Posi_tion = 0;
       delay(3000);
     //  digitalWrite(green, LOW);
       lcd.clear();
        }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// void sendsmslockedDuetoinvalidcode()
//  {
//   // delay (1000);
//     Serial.println("Sending sms...");
//     gprs.sendSMS("+2348082999099","Your vehicle was just locked due to the input of invalid codes! We strongly recommend that you check the status of your vehicle."); //define phone number and text
//// 
////   serialSIM800.write("AT+CMGF=1\r\n");
////   delay(1000);
////
////   serialSIM800.write("AT+CMGS=\"+2348082999099\"\r\n");
////   delay(1000);
////   serialSIM800.write("Your vehicle was just locked due to the input of an invalid code 3 times! We recomend you check on the status of your vehicle.");
////   delay(1000);
////
////   serialSIM800.write((char)26);
//    lcd.setCursor(0,1);
//    lcd.print("SecuritySms sent!");
//   
//   delay(1000);
//   lcd.clear();
//   Serial.println("SMS sent!");
// }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    void sendsms6tries()
//  {
//   // delay (1000);
//     Serial.println("Sending sms...");
//   serialSIM800.write("AT+CMGF=1\r\n");
//   delay(1000);
//
//   serialSIM800.write("AT+CMGS=\"+2348082999099\"\r\n");
//   delay(1000);
//   serialSIM800.write("Following a security breach, your vehicle has been locked for the next 30 minutes due to the input of too many invalid codes! We strongly recomend that you check on the status of your vehicle.");
//   delay(1000);
//
//   serialSIM800.write((char)26);
//   lcd.setCursor(0,1);
//    lcd.print("SecuritySms sent!");
//   
//   delay(1000);
//   lcd.clear();
//   Serial.println("SMS sent!");
//    }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void counterlimitreached3()
{
  Lock();
         // sendsmslockedDuetoinvalidcode();
        //sendsms6tries();
        delay (1000);
        lcd.clear();
        lcd.print("VEHICLE LOCKED");
        lcd.setCursor(0,1);
        lcd.print ("0:");
     int timer= (millis()/1000);
    int timeleft=90;
      do
       {
       int Timeleft=60- ((millis()/1000)-timer);
        lcd.setCursor(0,1);
        lcd.print("               ");
        lcd.setCursor(0,1);
        lcd.print ("0:");
        if (Timeleft<10)
        {
          lcd.print ("0");
           lcd.print(60- ((millis()/1000)-timer));
          }
          else
          {
        lcd.print(60- ((millis()/1000)-timer));
          }
      if (Timeleft==0)
     {
      lcd.clear();
      lcd.print(" Enter Pin");
      lcd.print(" ");
    lcd.print("(");
    
    lcd.print(counter);
    lcd.print(")");
      return (loop()) ;
    
      }
       delay (1000);
       }while(timeleft>0);
        }
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void counterlimitreached5()
{
  Lock();
        // sendsmslockedDuetoinvalidcode();
       // sendsms3tries();
        delay (1000);
        lcd.clear();
        lcd.print("VEHICLE LOCKED");
        lcd.setCursor(0,1);
        lcd.print ("FOR 30 MINUTES..");
        delay (1800000);
    
 }
 
  /////////////////////////////////////////////////////////////////////////////////////////
 void smsreceiver()
  {
  //  if(gprs.serialSIM800.available())
  //  {
      char lastCharRead = gprs.serialSIM800.read();
      //Read each character from serial output until \r or \n is reached (which denotes end of line)
      if(lastCharRead == '\r' || lastCharRead == '\n')
       {
         String lastLine = String(currentLine);
        
           //If last line read +CMT, New SMS Message Indications was received. 
            //Hence, next line is the message content.
            if(lastLine.startsWith("+CMT:"))
            {
          
               Serial.println(lastLine);
               nextLineIsMessage = true;
          
        } 
        else if (lastLine.length() > 0) {
          
          if(nextLineIsMessage) {
            Serial.println(lastLine);
            
            //Read message content and set status according to SMS content
            if(lastLine.indexOf("UNLOCK NOW 0000") >= 0){
              delay (5000);
              Unlock();
            } else if(lastLine.indexOf("LOCK NOW 0000") >= 0) {
                delay (5000);
              Lock();
            }
            
            nextLineIsMessage = false;
          }
//          
       }
//        
//        //Clear char array for next line of read
        for( int i = 0; i < sizeof(currentLine);  ++i ) {
         currentLine[i] = (char)0;
        }
        currentLineIndex = 0;
    } else {
      currentLine[currentLineIndex++] = lastCharRead;
    }
   // }
 }
 
//    
//
//



