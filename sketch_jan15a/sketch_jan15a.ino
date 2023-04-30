
int led = 9;
int trigger = 4;
int echo =5;
int indicator=7;
int Ready=2;
void setup() {
  // put your setup code here, to run once:
pinMode (led, OUTPUT);
pinMode (trigger, OUTPUT);
pinMode (echo, INPUT);
pinMode (Ready, OUTPUT);
// digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//  digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//  digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//  digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(100); 
//   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);              // wait for a second
//  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000); 
//   digitalWrite(Ready, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
long duration, distance;
digitalWrite(trigger,HIGH);
delayMicroseconds(1000);
digitalWrite(trigger,LOW);
duration=pulseIn(echo, HIGH);
distance=(duration/2)/29.1;
//Serial.print(distance);
//Serial.print("CH");
delay(10);

if(distance<=35)
{
   // delay(500);
    digitalWrite(led, HIGH);
  digitalWrite(Ready, HIGH);
}

if(distance>35)
{
   // 
     digitalWrite(led, LOW);
     digitalWrite(Ready, LOW);
     delay(500);
  }

 digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);              // wait for a second
  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
  delay(100); 
   digitalWrite(indicator, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(300);              // wait for a second
  digitalWrite(indicator, LOW);    // turn the LED off by making the voltage LOW
  delay(500); 

 
}
