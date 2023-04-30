//-------------------------------------------------------------------//
int val = 0;
String words = "";
String wordss = "";
int value = 0;
String number = "";
int food = 0;
int water = 0;
String wwater = "";
String wfood = "";
String wtemp = "";
String whumi = "";
int temp = 0;
int humi = 0;
String indicator = "";
int timer = 0;
//--------------------------------------------------------------------//

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define buzzer 16
#define red 14
#define blue_green 15

int  pos = 0;

LiquidCrystal_I2C lcd(0x3F, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
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
byte f7[8] = {
  0b11100,
  0b10100,
  0b11100,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

//--------------------------------------------------------------------//



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (buzzer, OUTPUT);
  pinMode (red, OUTPUT);
  pinMode (blue_green, OUTPUT);

  digitalWrite(buzzer, HIGH);

  digitalWrite(red, HIGH);
  delay(10);
  digitalWrite(red, LOW);
  delay(10);
  digitalWrite(red, HIGH);
  delay(10);
  digitalWrite(red, LOW);
  digitalWrite(blue_green, HIGH);
  delay(30);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(blue_green, LOW);
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.createChar(0, f1);
  lcd.createChar(1, f2);
  lcd.createChar(2, f3);
  lcd.createChar(3, f4);
  lcd.createChar(4, f5);
  lcd.createChar(5, f6);
  lcd.createChar(6, f7);
  lcd.setCursor(0, 0);
  startup();

}

void loop() {
  // put your main code here, to run repeatedly:
  int new_time = millis()-timer;
  if (new_time > 20000)
        {
          delay(100);
          digitalWrite(buzzer, HIGH);
          digitalWrite(red, HIGH);
          delay(100);
          digitalWrite(buzzer, LOW);
          digitalWrite(red, LOW);
          lcd.clear();
          lcd.print("NETWORK");
          lcd.setCursor(0,1);
          lcd.print("ERROR!!!");
          
        }
  while (Serial.available())
  {
    timer = millis();
    
    val = Serial.read();
    if (val == 46)number = number + ".";
    if (val == 48)number = number + "0";
    if (val == 49)number = number + "1";
    if (val == 50)number = number + "2";
    if (val == 51)number = number + "3";
    if (val == 52)number = number + "4";
    if (val == 53)number = number + "5";
    if (val == 54)number = number + "6";
    if (val == 55)number = number + "7";
    if (val == 56)number = number + "8";
    if (val == 57)number = number + "9";
    if (val == 32)words = words + " ";
    if (val == 97)words = words + "a";
    if (val == 98)words = words + "b";
    if (val == 99)words = words + "c";
    if (val == 100)words = words + "d";
    if (val == 101)words = words + "e";
    if (val == 102)words = words + "f";
    if (val == 103)words = words + "g";
    if (val == 104)words = words + "h";
    if (val == 105)words = words + "i";
    if (val == 106)words = words + "j";
    if (val == 107)words = words + "k";
    if (val == 108)words = words + "l";
    if (val == 109)words = words + "m";
    if (val == 110)words = words + "n";
    if (val == 111)words = words + "o";
    if (val == 112)words = words + "p";
    if (val == 113)words = words + "q";
    if (val == 114)words = words + "r";
    if (val == 115)words = words + "s";
    if (val == 116)words = words + "t";
    if (val == 117)words = words + "u";
    if (val == 118)words = words + "v";
    if (val == 119)words = words + "w";
    if (val == 120)words = words + "x";
    if (val == 121)words = words + "y";
    if (val == 122)words = words + "z";
    if (val == 13)
    {
      while (Serial.available())
      {
        val = Serial.read();
      }
      if (val == 10)
      {
        Serial.println(words);
        delay (1);

        if (words == "food")
        {
          timer = millis();
          wfood = number;
          food = number.toInt();
          wordss = "Quantity of food = " + wfood + "%";
          Serial.println(wordss);
          wordss = "";
          words = "";
          number = "";
          lcd_Update();

          return;

        }
        if (words == "water")
        {
          timer = millis();
          wwater = number;
          water = number.toInt();
          wordss = "Quantity of water = " + wwater + "%";
          Serial.println(wordss);
          wordss = "";
          words = "";
          number = "";
          lcd_Update();
          return;
        }

        if (words == "temperature")
        {
          timer = millis();
          wtemp = number;
          temp = number.toInt();
          wordss = "Temperature is = " + wtemp + "%";
          Serial.println(wordss);
          wordss = "";
          words = "";
          number = "";
          lcd_Update();
          return;
        }
        if (words == "humidity")
        {
          timer = millis();
          whumi = number;
          humi = number.toInt();
          wordss = "Humidity is = " + whumi + "%";
          Serial.println(wordss);
          wordss = "";
          words = "";
          number = "";
          lcd_Update();
          return;
        }
        


      }

    }
  }


  delay(10);

  delay (50);
  //Serial.println("---------");

}
/////////////////////////////////////////////////////////////////////
void lcd_Update()
{
  digitalWrite(blue_green, HIGH);
  delay(70);
  digitalWrite(blue_green, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp = ");
  lcd.print(wtemp);
  lcd.write(6);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity = ");
  lcd.print(whumi);
  lcd.print("%");

  lcd.setCursor(0, 2);
  lcd.print("Food = ");
  lcd.print(wfood);
  lcd.print("%");

  lcd.setCursor(0, 3);
  lcd.print("Water = ");
  lcd.print(wwater);
  lcd.print("%");

  if ((food < 10) || (water < 10) || (temp < 20) || (temp > 35))
  {
    digitalWrite(buzzer, HIGH);
    digitalWrite(red, HIGH);
    delay(70);
    digitalWrite(buzzer, LOW);
    digitalWrite(red, LOW);
  }
  if ((food > 10) && (water > 10) && (temp > 20) && (temp < 35))
  {

    digitalWrite(buzzer, LOW);
    digitalWrite(red, LOW);
  }





}
/////////////////////////////////////////////////////////////////////
void startup()
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

  for (int i = 0; i < 3; i++)
  {
    lcd.setCursor(10, 1);
    lcd.write(0);
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

