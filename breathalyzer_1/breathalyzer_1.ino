
#include <LiquidCrystal.h>
#define relayPin 11
#define red 13
#define green 12
#define buzzer 3
float bac_pin = A0;
unsigned int val = 0; //breathalyzer value
unsigned char PIN = 0;
int intNumber = 1023; //max value
int delayTime = 1000;
float bac = 0;
float bacArray[30];
float largest = 0 ;
float temp = 0;

int count = 0;

LiquidCrystal lcd(10, 9, 4, 5, 6, 7);

float BAC = 0.877;
////////////////////////////////////////////////////////////


volatile int  flow_frequency;
volatile int  flow_frequency_; // Measures flow meter pulses
float  l_hour;
float  l_hour_; // Calculated litres/hour
  // Flow Meter Pin number
unsigned long currentTime;
unsigned long cloopTime;
unsigned long currentTime_;
unsigned long cloopTime_;

////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("Calculating BAC...");
  //Serial.begin(9600);
  pinMode(bac_pin, INPUT);
  pinMode(buzzer, OUTPUT);
  unsigned char flowmeter = 2;
  

  /*********************************************************/
  pinMode(flowmeter, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode (red, OUTPUT);
  pinMode (green, OUTPUT);
  digitalWrite(relayPin, LOW);
  digitalWrite (red, HIGH);
 

digitalWrite (red, HIGH);

   
  Serial.begin(9600);
  attachInterrupt(0, flow, RISING); // Setup Interrupt
  // see http://arduino.cc/en/Reference/attachInterrupt
  sei();                            // Enable interrupts
  currentTime = millis();
  cloopTime = currentTime;
  currentTime_ = millis();
  cloopTime_ = currentTime_;
  /*********************************************************/

}

void loop() {
 
  get_l_hour();
  if (l_hour > 380)
  {
    delay(1000);
       get_l_hour();
    if (l_hour > 400)
    {
      measure();
      Display_measurment();
      delay (5000);

    }



  }

  else if (l_hour < 380)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Blow into the de");
    lcd.setCursor(0, 1);
    lcd.print("-vice for 5 secs");

    delay(1000);
  }

}

//  int delayTime = 100; //delay

//}
void flow ()                  // Interruot function
{
  flow_frequency++;
}

void measure()
{
  lcd.clear();
  lcd.print("Calculating BAC...");
  for (int i = 0; i < 30; i++)
  {
    Find();
    bacArray[i] = bac;
    
 Serial.println(bacArray[i]);
 largest = bacArray[0];

temp = bacArray[i];
      if (temp > largest)
      {
        largest = temp;
      }

    
   
 
 //Serial.println(bac);
    delay(10);
  }
   BAC = largest;


//    largest = bacArray[0];
//
//    for (int i = 0; i < 30; i++)
//    {
//      temp = bacArray[i];
//      if (temp > largest)
//      {
//        largest = temp;
//      }
//
//    }
//    BAC = largest;
//  




  Serial.println(BAC);
  //Serial.println(val);

}
void Display_measurment()
{ lcd.clear();
  lcd.print("BAC = ");
  lcd.print(BAC, 4);

  if (BAC > 0.08)
  {
    // lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("BAC is too high!");
    Lock();
   
   
   // delay (5000);
  }
  if ((BAC < 0.08) && (bac > 0.04))
  {
    // lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("BAC is OK");
    Unlock();
    delay (3000);
  }
  if (BAC < 0.04)
  {
    //lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("BAC is low.");

    
    Unlock();
    delay (3000);
    

  }
}
void get_l_hour()
{
  currentTime = millis();
  // Every second, calculate and print litres/hour
  if (currentTime >= (cloopTime + 1000))
  {
    cloopTime = currentTime;              // Updates cloopTime
    // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min. (Results in +/- 3% range)
    l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flow rate in L/hour
    flow_frequency = 0;                   // Reset Counter
    Serial.print(l_hour, DEC);            // Print litres/hour
    Serial.println(" L/hour");
  }
}
void Find()
{
  val = analogRead(bac_pin);
    if (val <= 735)
    {
      bac = 0;
     
    }

    else if (val > 735 && val < 800) {
      bac = val * .0015 - 1.1125;

    }

    else if (val > 800) {
      bac = val * 0.0053 - 4.1867;


    }


}
void Lock()
{
  
 digitalWrite(relayPin, LOW);
     digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    
    digitalWrite(buzzer, HIGH);
    delay (500);
    digitalWrite(buzzer, LOW);
    delay (100);
     digitalWrite(buzzer, HIGH);
    delay (500);
    digitalWrite(buzzer, LOW);
    delay (100);
     digitalWrite(buzzer, HIGH);
    delay (500);
    digitalWrite(buzzer, LOW);
    delay (100);
     digitalWrite(buzzer, HIGH);
    delay (500);
    digitalWrite(buzzer, LOW);
    delay (100);
     digitalWrite(buzzer, HIGH);
    delay (500);
    digitalWrite(buzzer, LOW);
    delay (100);
     digitalWrite(buzzer, HIGH);
    delay (500);
    digitalWrite(buzzer, LOW);
    delay (100);
     digitalWrite(buzzer, HIGH);
    delay (500);
    digitalWrite(buzzer, LOW);
    delay (100);
     digitalWrite(buzzer, HIGH);
    delay (500);
    digitalWrite(buzzer, LOW);
    delay (100);

}
 void Unlock()
{
    digitalWrite(relayPin, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);

     digitalWrite(buzzer, HIGH);
    delay (200);
    digitalWrite(buzzer, LOW);
    delay (50);
     digitalWrite(buzzer, HIGH);
    delay (200);
    digitalWrite(buzzer, LOW);
    delay(50);
     digitalWrite(buzzer, HIGH);
    delay (200);
    digitalWrite(buzzer, LOW);
    delay (50);

}



