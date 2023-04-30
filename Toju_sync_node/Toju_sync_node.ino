/*
  Arduino Wireless Communication Tutorial
        Example 1 - Receiver Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>

#define blue 10
LiquidCrystal lcd(2, 3, 4, 5, 6, 9);
RF24 radio(7, 8); // CE, CSN
const byte address[6] = {"00001"};
float ref_node_temp = 0;
float lcd_temp = 0;
bool state = false;


int  pos = 0;

byte degree[8] = {
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

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


 int tolerance = 0;

void setup() {
  lcd.begin(20, 4);
  lcd.setCursor(0,0);
  kosview_intro();
  Serial.begin(9600);
  radio.begin();
  // radio.openReadingPipe(0, address[0]);
  //  radio.openReadingPipe(1, address[1]);
   radio.openReadingPipe(0, address);

  radio.setPALevel(RF24_PA_MAX);
    radio.startListening();
  pinMode (14, INPUT);
    pinMode (10, OUTPUT);
    digitalWrite (10, LOW);

  lcd.createChar(10, f1);
  lcd.createChar(6, degree);
  lcd.createChar(1, f2);
  lcd.createChar(2, f3);
  lcd.createChar(3, f4);
  lcd.createChar(4, f5);
  lcd.createChar(5, f6);
    checkinglcdloading();
}
void loop() {
 
  if (radio.available()) {
    //   char text[32] = "";

    radio.read(&ref_node_temp, sizeof(ref_node_temp));
      digitalWrite (10, LOW);
      delay (50);
        digitalWrite (10, HIGH);
        delay (50);
         digitalWrite (10, LOW);
      delay (50);
        digitalWrite (10, HIGH);
  delay (50);
         digitalWrite (10, LOW);
 }
  if (!radio.available()) {
    //   char text[32] = "";
digitalWrite (10, LOW);
      delay (50);
        digitalWrite (10, HIGH);
        delay (20);
         digitalWrite (10, LOW);
      delay (50);
        digitalWrite (10, HIGH);
        delay (20);
         digitalWrite (10, LOW);
      delay (50);
        digitalWrite (10, HIGH);
        delay (20);
         digitalWrite (10, LOW);
     
    //radio.read(&ref_node_temp, sizeof(ref_node_temp));
   
    ref_node_temp=0;
 }

 Serial.print("Reference node temp = ");
    Serial.print(ref_node_temp);
    Serial.println("*C");
  int val = analogRead(14);
  float mv = ( val / 1024.0) * 5000;
  float cel = (mv / 10)-11;
  Serial.print("Sync node temp = ");
  Serial.print(cel);
  Serial.println("*C");

  tolerance = ( ref_node_temp - cel);
  if (tolerance <0)tolerance=tolerance*-1;
  Serial.print("Difference = ");
  Serial.print(tolerance);
  Serial.println("*C");
   Serial.println("\n\n");


  if ((tolerance > 20) || (tolerance == 20))
  {

    lcd_temp = ref_node_temp;
    if (state == false)
    {
      lcd.clear();
      delay(1000);
      lcd.setCursor(0, 0);
      lcd.print("Wrong sensor values");
      lcd.setCursor(0, 1);
      lcd.print("have been detected!");
    
      delay(2000);
       lcd.clear();
      //recalibrating
      recalibrating();
      lcd.clear();
      state = true;
    }


  }
  if (tolerance < 20)
  {
    lcd_temp = cel;
    if (state == true)
    {
      state = false;
      lcd.clear();
      delay(1000);
      lcd.setCursor(0, 0);
      lcd.print("Returning to default");
      lcd.setCursor(7, 1);
      lcd.print("Values");
      
      delay(2000);
      lcd.clear();
    }


  }
    lcd.clear();
   if (!radio.available()) {
    lcd_temp = cel;
     lcd.setCursor(0, 3);
    lcd.print("Connection lost");
   }
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature= ");
  lcd.print(lcd_temp);
  //lcd.write degree
  lcd.write(6);
  lcd.print("C");
  Serial.print ("state  ");
        Serial.println (state);
          Serial.print ("\n\n\n");
  delay(1000);


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
void recalibrating()
{
  for (int i = 0; i < 3; i++)
  {
    lcd.setCursor(1, 0);
    lcd.print("Recalibrating");
    lcd.setCursor(10, 1);
    lcd.write(10);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Recalibrating");
    lcd.setCursor(10, 1);
    lcd.write(1);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Recalibrating");
    lcd.setCursor(10, 1);
    lcd.write(2);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Recalibrating");
    lcd.setCursor(10, 1);
    lcd.write(3);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Recalibrating");
    lcd.setCursor(10, 1);
    lcd.write(4);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Recalibrating");
    lcd.setCursor(10, 1);
    lcd.write(5);
    delay (300);
    lcd.clear();
    delay (2);

  }
}
