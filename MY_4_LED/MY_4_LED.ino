// http://tronixstuff.com/2014/01/08/tutorial-arduino-and-sim900-gsm-modules/
// base sketch: Example 55.7
// rewrite after phote by niq_ro from http://nicuflorica.blogspot.com/
// and http://arduinotehniq.blogspot.com/
// rewrite for serialSIM800 GPRS module by niq_ro - 18.08.2015, Craiova  - Romania, Europe, Earth

 
#include <SoftwareSerial.h> 
char inchar; // Will hold the incoming character from the GSM shield



#define SIM800_TX_PIN 7
#define SIM800_RX_PIN 8

// initialize the library instances
SoftwareSerial serialSIM800(SIM800_TX_PIN, SIM800_RX_PIN);
 
int led1 = 10;
int led2 = 11;
int led3 = 12;
int led4 = 13;
 
void setup()
{
 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    serialSIM800.begin(9600);
    delay(1000);
      
      }
      serialSIM800.begin(9600);
    delay(1000);
    
//serialSIM800.write("AT+CMGF=1\r\n");
//   delay(1000);
//
//   serialSIM800.write("AT+CMGS=\"+2348082999099\"\r\n");
//   delay(1000);
//   serialSIM800.write("sms receiver is ready");
//   delay(1000);
//
//   serialSIM800.write((char)26);
//   delay(1000);
//   Serial.println("SMS sent!");
   
serialSIM800.print("AT+CSCS=\"GSM\"");
serialSIM800.print("\r");
delay(1000);


serialSIM800.print("AT+CMGF=1\r");  // set SMS mode to text
delay(1000);

serialSIM800.print("AT+CNMI=2,2,0,0,0\r"); 
delay(1000);

serialSIM800.println("AT+CMGD=1,4"); // delete all SMS

delay(1000);  
}
 
void loop() 
{
  if(serialSIM800.available() >0)
    {
digitalWrite(led1, HIGH);
      
      inchar=serialSIM800.read(); 
    
    if (inchar=='#')
    {
      delay(10);
 
      inchar=serialSIM800.read(); 
      if (inchar=='a')
      {
        delay(10);
        
       inchar=serialSIM800.read();
        if (inchar=='0')
        {
          digitalWrite(led1, LOW);
          
        } 
        else if (inchar=='1')
        {
          digitalWrite(led1, HIGH);
          
        }
        delay(10);
        
      inchar=serialSIM800.read(); 
        if (inchar=='b')
        {
      inchar=serialSIM800.read(); 
          if (inchar=='0')
          {
            digitalWrite(led2, LOW);
            
          } 
          else if (inchar=='1')
          {
            digitalWrite(led2, HIGH);
         
          }
          delay(10);
          
      inchar=serialSIM800.read(); 
          if (inchar=='c')
          {
      inchar=serialSIM800.read(); 
            if (inchar=='0')
            {
              digitalWrite(led3, LOW);
           
            } 
            else if (inchar=='1')
            {
              digitalWrite(led3, HIGH);
            
            }
            delay(10);
           
       inchar=serialSIM800.read(); 
            if (inchar=='d')
            {
       inchar=serialSIM800.read(); 
              if (inchar=='0')
              {
                digitalWrite(led4, LOW);
           
              } 
              else if (inchar=='1')
              {
                digitalWrite(led4, HIGH);
              
              }
              delay(10);
            }
          }
            serialSIM800.println("AT+CMGD=1,4"); // delete all SMS
            
        }
      }
    }
  }
 
}
