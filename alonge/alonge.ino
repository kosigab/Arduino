int ult_1_trig = 2;
int ult_1_echo = 3;

int ult_2_trig = 4;
int ult_2_echo = 5;

long ult_1_duration, ult_1_distance;
long ult_2_duration, ult_2_distance;

#define MAX_DISTANCE 34
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
float B = 0, strols = 0;
float E = 0, strolx = 0;
float C = 0, G = 0, L = 0;
float D = 0, F = 0;
float x = 0, H = 0;
float y = 0, K = 0;
const byte ROWS = 5; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'A', 'B', '#', '*'},
  {'1', '2', '3', 'U'},
  {'4', '5', '6', 'D'},
  {'7', '8', '9', 'E'},
  {'L', '0', 'R', 'C'}
};
byte rowPins[ROWS] = {6, 7, 8, 9, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 12, 13, 14}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad kpd = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
int v1 = 0, z = 0;
int v2 = 0;
int v3 = 0;
int num = 0, strolz = 0;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.init();                      // initialize the lcd
  lcd.init();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.backlight();
  // put your setup code here, to run once:
  pinMode (ult_1_trig, OUTPUT);
  pinMode (ult_1_echo, INPUT);

  pinMode (ult_2_trig, OUTPUT);
  pinMode (ult_2_echo, INPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A6, OUTPUT);
  ult_1_distance_measure();
  ult_2_distance_measure();
  //B=MAX_DISTANCE-ult_1_distance;
  //lcd.setCursor(0,0); lcd.print("tankA= "); lcd.setCursor(7,0); lcd.print(B); delay(150); lcd.setCursor(10,0); lcd.print("cm");
  //lcd.print("");
}

void loop()
{
  ult_1_distance_measure();
  ult_2_distance_measure();
  /*lcd.setCursor(0,0); lcd.print("");  lcd.print(ult_1_distance); delay(150);
    lcd.print("");*/
  B = MAX_DISTANCE - (ult_1_distance);
  strols = MAX_DISTANCE - (ult_2_distance);
  G = (B * 12.25 * 3.142);  H = (strols * 12.25 * 3.142);
  // float q= G*1.6238;  float v= H*1.6238;
  //lcd.clear();  lcd.setCursor(0,0);  lcd.print(G); delay(1000);
  lcd.clear(); 
  lcd.print("Tank A="); 
  delay(1000);
  lcd.clear();
  lcd.print("0"); 
  delay(1000);
  lcd.clear();
  lcd.print("mL");
  delay(1000);
  //lcd.clear();  lcd.setCursor(0,1);  lcd.print(strols); delay(1000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Tank B=");
  lcd.clear(); 
  lcd.print("0");
  delay(1000);
  lcd.clear(); 
  lcd.print("mL");
  delay(1000);
  //E= MAX_DISTANCE-num; strolx= MAX_DISTANCE-num;
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Enter for Tank A");
  v1 = GetNumber();
  K = (num / 1.6238);
  lcd.clear();
  lcd.setCursor(0, 1); 
  lcd.print("");
  lcd.print("Enter for Tank B"); 
  delay(900);
  v2 = strolla();
  L = (strolz / 1.6238);
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print(num);
  lcd.setCursor(4, 0);
  lcd.print("cm");
  delay(800);
  lcd.setCursor(0, 1);
  lcd.print(""); 
  lcd.print(strolz);
  lcd.setCursor(4, 0);
  lcd.print("cm");
  delay(750);
  for (float a = 0;  a <= 1000000000; a++)
  {
    ult_1_distance_measure(); 
    ult_2_distance_measure();
    B = MAX_DISTANCE - ult_1_distance;
    strols = MAX_DISTANCE - ult_2_distance;
    G = (B * 7 * 3.142); 
    H = (strols * 7 * 3.142);
    Serial.println(G); 
    Serial.println(H);
    float t = K - 3;  
    float m = K + 3; 
    float strol = L - 3; 
    float stroo = L + 3;
    if (K > 617 || L > 617)
    {
      num = 0;
      strolz = 0;
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Value above size"); 
      lcd.setCursor(1, 0); 
      lcd.print("of tank");
      a = 10000; 
      return;
    }
    else if (K < 2 || L < 2)
    {
      num = 0;
      strolz = 0; 
      lcd.clear(); 
      lcd.setCursor(0, 0); 
      lcd.print("WRONG INPUT"); 
      delay(900);
      a = 10000;
      return;
    }
    else if (((G >= t) && (G <= m)) && ((H >= strol) && (H <= stroo)))
    {
      digitalWrite(A2, LOW);
      digitalWrite(A3, LOW);
      digitalWrite(A6, LOW);
      lcd.clear();  lcd.setCursor(0, 0); lcd.print("FILLED"); delay(1500);
      num = 0; strolz = 0; a = 10000;  return;
    }
    else if ((G < K) && (H < L))
    {
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      digitalWrite(A6, LOW);
      lcd.clear();  lcd.setCursor(0, 0); lcd.print("FILLING TANKS"); delay(100);
      if ((H >= strol) && (H <= stroo))
      {
        //digitalWrite(A2, HIGH);
        digitalWrite(A3, LOW);
        //digitalWrite(A6, LOW);
        lcd.clear();  lcd.setCursor(0, 0); lcd.print("TANK B FILLED"); delay(100);
        lcd.setCursor(1, 0); lcd.print("FILLING A");
      }
      else if ((G >= t) && (G <= m))
      {
        digitalWrite(A2, LOW);
        digitalWrite(A3, LOW);
        //digitalWrite(A6, LOW);
        lcd.clear();  lcd.setCursor(0, 0); lcd.print("TANKS FILLED"); delay(950);
        num = 0; strolz = 0;  a = 10000;  return;
      }
    }
    else if ((G < K) && (H > L))
    {
      digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH); delay(750);
      digitalWrite(A6, HIGH);
      lcd.clear();  lcd.setCursor(0, 0); lcd.print("WORKING"); delay(1000);
      if ((H >= strol) && (H <= stroo))
      {
        //digitalWrite(A2, LOW);
        digitalWrite(A3, LOW);
        digitalWrite(A6, LOW);
      }
    }
    else if ((G < K) && ((H >= strol) && (H <= stroo)))
    {
      digitalWrite(A3, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(A6, LOW);
      if ((G >= t) && (G <= m))
      {
        //digitalWrite(A3, LOW);
        digitalWrite(A2, LOW);
        //digitalWrite(A6, LOW);
        lcd.clear();  lcd.print("FILLED");
        num = 0;  strolz = 0; a = 10000;  return;
      }
    }
    else if ((G > K) && (H > L))
    {
      digitalWrite(A2, LOW);  digitalWrite(A3, HIGH); digitalWrite(A6, HIGH);
      lcd.clear();  lcd.print("WORKING");  delay(100);
      if ((H >= strol) && (H <= stroo))
      {
        digitalWrite(A6, LOW);
        digitalWrite(A3, LOW);
        //digitalWrite(A2, LOW);
        lcd.clear();  lcd.print("WORKING");  delay(100);
      }
    }
    else if ((G > K) && ((H >= strol) && (H <= stroo)))
    {
      digitalWrite(A2, LOW);  digitalWrite(A3, LOW);
      digitalWrite(A6, HIGH);
      lcd.clear();  lcd.print("WORKING");  delay(100);
      if ((G >= t) && (G <= m))
      {
        digitalWrite(A6, LOW);
        //digitalWrite(A2, LOW);  digitalWrite(A3, LOW);
        lcd.clear();  lcd.print("FILLED");
        num = 0; strolz = 0; a = 10000;  return;
      }
    }
    else if ((G > K) && (H < L))
    {
      digitalWrite(A6, LOW);  digitalWrite(A3, HIGH);
      digitalWrite(A2, HIGH);
      lcd.clear();  lcd.print("WORKING"); delay(100);
      if (((H >= strol) && (H <= stroo)))
      {
        digitalWrite(A3, LOW);  digitalWrite(A2, LOW);
        //digitalWrite(A6, LOW);
      }
    }
    /*else if((G>K)&&((strols>=strol)&&(strols<=stroo)))
    {
      digitalWrite(A2, LOW);  digitalWrite(A3, LOW);
      digitalWrite(A6, HIGH);
      if((G>=t)&&(G<=m))
      {
        digitalWrite(A6, LOW);
        digitalWrite(A2, LOW);  digitalWrite(A3, LOW);
        lcd.clear();  lcd.print("FILLED");
        a=10000; num=0; strolz=0; return;
      }
    }*/
  }
}
void ult_1_distance_measure()
{

  digitalWrite(ult_1_trig, HIGH);
  delayMicroseconds(200);

  digitalWrite(ult_1_trig, LOW);

  ult_1_duration = pulseIn(ult_1_echo, HIGH);
  ult_1_distance = (ult_1_duration / 2) / 29.1;
  //  Serial.println (ult_1_distance);
  // delay (10);
}

void ult_2_distance_measure()
{
  digitalWrite(ult_2_trig, HIGH);
  delayMicroseconds(200);

  digitalWrite(ult_2_trig, LOW);

  ult_2_duration = pulseIn(ult_2_echo, HIGH);
  ult_2_distance = (ult_2_duration / 2) / 29.1;
}
int GetNumber()
{
  char key = kpd.getKey();
  while (key != '#')
  {
    switch (key)
    {
      case NO_KEY:
        break;

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        //lcd.print(key);
        num = num * 10 + (key - '0');
        lcd.setCursor(0, 0);
        lcd.clear();
        delay(200);
        lcd.print(num);
        break;
      case '*':
        num = 0;
        lcd.clear();
        break;
    }
    key = kpd.getKey();
  }
}

int strolla()
{
  char stroll = kpd.getKey();
  while (stroll != '#')
  {
    switch (stroll)
    {
      case NO_KEY:
        break;

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        //lcd.print(key);
        strolz = strolz * 10 + (stroll - '0');
        lcd.setCursor(1, 0);
        lcd.clear();
        delay(200);
        lcd.print(strolz);
        break;
      case '*':
        strolz = 0;
        lcd.clear();
        break;
    }
    stroll = kpd.getKey();
  }
}

