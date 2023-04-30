//#include <Servo.h>
//Servo myservo; 
#define firstLDRpin A0
#define secondLDRpin A1

#define relayA1 3
#define relayA2 4

#define relayB1 5
#define relayB2 6

int value1 = 0;
int value2 = 0;
int pos = 90;
float newpos = pos;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode (relayA1, OUTPUT);
pinMode (relayA2, OUTPUT);
pinMode (relayB1, OUTPUT);
pinMode (relayB2, OUTPUT);

digitalWrite (relayA1, LOW);
digitalWrite (relayA2, LOW);
digitalWrite (relayB1, LOW);
digitalWrite (relayB2, LOW);

//myservo.attach(9);
//
//myservo.write (pos);
}

void loop() {
  // put your main code here, to run repeatedly:
value1 = analogRead(firstLDRpin);
Serial.println(value1);
value2 = analogRead(secondLDRpin);
//Serial.println("First ldr value = "+ value1);
//Serial.println("Second ldr value = "+ value2);
//
//delay (1000);

do
{
  value1 = analogRead(firstLDRpin);
  value2 = analogRead(secondLDRpin);
//   myservo.write(newpos);
//    newpos = newpos + 1;
    digitalWrite (relayA1, HIGH);
    digitalWrite (relayA2, HIGH);
    
    digitalWrite (relayB1, LOW);
    digitalWrite (relayB2, LOW);

    
    Serial.print("value 1 = ");
    Serial.println(value1);

    Serial.print("value 2 = ");
    Serial.println(value2);
     Serial.println();
    delay (1000);

//    delay (15);
}
    while ((value1>value2));

delay (1000);

do
{
  value1 = analogRead(firstLDRpin);
value2 = analogRead(secondLDRpin);
//   myservo.write(newpos);
//    newpos = newpos - 1;
    //delay (15);
    
    digitalWrite (relayA1, LOW);
    digitalWrite (relayA2, LOW);
    
    digitalWrite (relayB1, HIGH);
    digitalWrite (relayB2, HIGH);
   
    Serial.print("value 1 = ");
    Serial.println(value1);

    Serial.print("value 2 = ");
    Serial.println(value2);
     Serial.println();
    delay (1000);
    
    
}
while ((value1<value2));
Serial.print("value 1 = ");
    Serial.println(value1);

    Serial.print("value 2 = ");
    Serial.println(value2);
    Serial.println();
    

//digitalWrite (relayA1, LOW);
//digitalWrite (relayA2, LOW);
//digitalWrite (relayB1, LOW);
//digitalWrite (relayB2, LOW);
}
