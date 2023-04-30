#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define reSet 15
#define buzzer 5
#define tankA_inlet_pump 3
#define tankB_inlet_pump 4
#define tankC_inlet_pump 30
#define tankA_outlet_valve 31
#define tankB_outlet_valve 32
#define AB_crossFeed_valve 33

#define ult_1_trig 16
#define ult_1_echo 17
#define ult_2_trig 18
#define ult_2_echo 19
#define ult_3_trig 22
#define ult_3_echo 23
#include <math.h>
/// below contains initialization of some characters.
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




const byte ROWS = 5; //four rows
const byte COLS = 5; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'A', 'B', '#', '*'},
  {'1', '2', '3', 'U'},
  {'4', '5', '6', 'D'},
  {'7', '8', '9', 'Q'},
  {'L', '0', 'R', 'E'}
};
byte rowPins[ROWS] = {14, 13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad kpd = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

String words = "";
int numbers = 0;
int tankA = 0;
double tankAvol = 0;
double tankBvol = 0;
double tankCvol = 0;
double radius = 8.57066;
double volumeConstant = PI * (pow(radius, 2));
int tankB = 0;
int tankC = 0;
int pos = 0;
double ult_1_duration = 0, ult_1_distance = 0;
double ult_2_duration = 0, ult_2_distance = 0;
double ult_3_duration = 0, ult_3_distance = 0;

char customKey = kpd.getKey();
void setup() {
  // put your setup code here, to run once:

  digitalWrite(reSet, HIGH);

  pinMode (ult_1_trig, OUTPUT);
  pinMode (ult_1_echo, INPUT);
  pinMode (ult_2_trig, OUTPUT);
  pinMode (ult_2_echo, INPUT);
  pinMode (ult_3_trig, OUTPUT);
  pinMode (ult_3_echo, INPUT);
  pinMode(reSet, OUTPUT);
  pinMode (buzzer, OUTPUT);
  pinMode (tankA_inlet_pump, OUTPUT);
  pinMode (tankB_inlet_pump, OUTPUT);
  pinMode (tankC_inlet_pump, OUTPUT);
  pinMode (tankA_outlet_valve, OUTPUT);
  pinMode (tankB_outlet_valve, OUTPUT);
  pinMode (AB_crossFeed_valve, OUTPUT);
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
  lcd.setCursor(0, 0);


  kosviewintro();
  //checkinglcdloading();
  Serial.begin(9600);
}

void loop()
{
  doloop();
  //getTankA();

}
void doloop()
{
  customKey = 0;
  currentVolumes();
}
///////////////////////////////////////////////////////////
void getTankA()
{
  lcd.clear();
  lcd.print("Enter desired value");
  lcd.setCursor(0, 1);
  lcd.print("for Tank A");
  char customKey = kpd.getKey();

  do {
    char customKey = kpd.getKey();
    //lcd.print ("Tank A = ");
    if (customKey) {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
      if ((words.length() < 3) && (customKey != 'A') && (customKey != 'B') && (customKey != '#') && (customKey != '*') && (customKey != 'U') && (customKey != 'D') && (customKey != 'L') && (customKey != 'R') && (customKey != 'Q') && (customKey != 'E') )
      {
        if (words == "0")
        {
          words = "";
        }
        words = words + customKey ;
        numbers = words.toInt();
      }
      if (customKey == 'L')
      {
        words = "0";
        numbers = 0;
      }
      if (customKey == '*')
      {
        digitalWrite(reSet, LOW);
      }
      if (customKey == 'Q')
      {
        lcd.clear();
        lcd.print("Quiting...");
        delay(1500);
        doloop();
      }
      if (customKey == 'E')
      {
        if (numbers > 200)
        {
          lcd.setCursor(1, 1);
          lcd.print("Max value is 200");
          delay (1000);
          lcd.setCursor(0, 0);
          Serial.println("Max value is 200");
          words = "0";
          numbers = 0;
          getTankA();
        }
        tankA = numbers;
        words = "0";
        numbers = 0;
        getTankB();
      }

      lcd.clear();
      lcd.print ("Tank A = ");
      lcd.print (words + "cl");


      Serial.println(numbers);
    }
  } while (customKey != 'E');

}
///////////////////////////////////////////////////////////
void getTankB()
{
  lcd.clear();
  lcd.print("Enter desired value");
  lcd.setCursor(0, 1);
  lcd.print("for Tank B");
  char customKey = kpd.getKey();
  do {
    char customKey = kpd.getKey();
    //lcd.print ("Tank B = ");
    if (customKey) {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
      if ((words.length() < 3) && (customKey != 'A') && (customKey != 'B') && (customKey != '#') && (customKey != '*') && (customKey != 'U') && (customKey != 'D') && (customKey != 'L') && (customKey != 'R') && (customKey != 'Q') && (customKey != 'E') )
      {
        if (words == "0")
        {
          words = "";
        }
        words = words + customKey ;
        numbers = words.toInt();
      }
      if (customKey == 'Q')
      {
        lcd.clear();
        lcd.print("Quiting...");
        delay(1500);
        doloop();
      }
      if (customKey == 'L')
      {
        words = "0";
        numbers = 0;
      }
      if (customKey == '*')
      {
        digitalWrite(reSet, LOW);
      }
      if (customKey == 'E')
      {
        if (numbers > 200)
        {
          lcd.setCursor(1, 1);
          lcd.print("Max value is 200");
          delay (1000);
          lcd.setCursor(0, 0);
          Serial.println("Max value is 200");
          words = "0";
          numbers = 0;
          getTankB();
        }
        tankB = numbers;
        words = "0";
        numbers = 0;
        getTankC();
      }

      lcd.clear();
      lcd.print ("Tank B = ");
      lcd.print (words + "cl");


      Serial.println(numbers);
    }
  } while (customKey != 'E');
}
///////////////////////////////////////////////////////////
void getTankC()
{
  lcd.clear();
  lcd.print("Enter desired value");
  lcd.setCursor(0, 1);
  lcd.print("for Tank C");
  char customKey = kpd.getKey();
  do {
    char customKey = kpd.getKey();
    //lcd.print ("Tank C = ");
    if (customKey) {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
      if ((words.length() < 3) && (customKey != 'A') && (customKey != 'B') && (customKey != '#') && (customKey != '*') && (customKey != 'U') && (customKey != 'D') && (customKey != 'L') && (customKey != 'R') && (customKey != 'Q') && (customKey != 'E') )
      {
        if (words == "0")
        {
          words = "";
        }
        words = words + customKey ;
        numbers = words.toInt();
      }
      if (customKey == 'Q')
      {
        lcd.clear();
        lcd.print("Quiting...");
        delay(1500);
        doloop();
      }
      if (customKey == '*')
      {
        digitalWrite(reSet, LOW);
      }
      if (customKey == 'L')
      {
        words = "0";
        numbers = 0;
      }
      if (customKey == 'E')
      {
        if (numbers > 200)
        {
          lcd.setCursor(1, 1);
          lcd.print("Max value is 200");
          delay (1000);
          lcd.setCursor(0, 0);
          Serial.println("Max value is 200");
          words = "0";
          numbers = 0;
          getTankC();
        }
        tankC = numbers;
        words = "0";
        numbers = 0;
        action();
      }

      lcd.clear();
      lcd.print ("Tank C = ");
      lcd.print (words + "cl");


      Serial.println(numbers);
    }
  } while (customKey != 'E');
}
///////////////////////////////////////////////////////////
void empty_tank_A()
{
  double tank_A_vol =  tank_A_volume_measure();
  while (tank_A_vol > 0.1)
  {

    delay(300);
    lcd.clear();
    lcd.print("Tank A = ");
    lcd.print(tank_A_vol);
    char customKey = kpd.getKey();
    if (customKey)
    {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
    }
    if (customKey == 'Q')
    {
      lcd.clear();
      lcd.print("Quiting...");
      digitalWrite(tankA_inlet_pump, LOW);
      digitalWrite(tankB_inlet_pump, LOW);
      digitalWrite(tankC_inlet_pump, LOW);
      digitalWrite(tankA_outlet_valve, LOW);
      digitalWrite(tankB_outlet_valve, LOW);
      delay(1500);
      doloop();
    }
    if (customKey == '*')
    {
      digitalWrite(reSet, LOW);
    }
    tank_A_vol =  tank_A_volume_measure();
    // Activate A outlet valve
    digitalWrite (tankA_outlet_valve, HIGH);
  }
  if (tank_A_vol < 1)
  {
    digitalWrite (tankA_outlet_valve, LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
}
///////////////////////////////////////////////////////////
void empty_tank_B()
{
  double tank_B_vol =  tank_B_volume_measure();
  while (tank_B_vol > 0.1)
  {

    delay(300);
    lcd.clear();
    lcd.print("Tank B = ");
    lcd.print(tank_B_vol);
    char customKey = kpd.getKey();
    if (customKey)
    {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
    }
    if (customKey == 'Q')
    {
      lcd.clear();
      lcd.print("Quiting...");
      digitalWrite(tankA_inlet_pump, LOW);
      digitalWrite(tankB_inlet_pump, LOW);
      digitalWrite(tankC_inlet_pump, LOW);
      digitalWrite(tankA_outlet_valve, LOW);
      digitalWrite(tankB_outlet_valve, LOW);
      delay(1500);
      doloop();
    }
    if (customKey == '*')
    {
      digitalWrite(reSet, LOW);
    }
    tank_B_vol =  tank_B_volume_measure();
    // Activate A outlet valve
    digitalWrite (tankB_outlet_valve, HIGH);
     digitalWrite (tankA_outlet_valve, HIGH);
  }
  if (tank_B_vol < 1)
  {
      empty_tank_A();
    digitalWrite (tankB_outlet_valve, LOW);
    digitalWrite (tankA_outlet_valve, LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);

}
///////////////////////////////////////////////////////////
void empty_tank_C()
{
  double tank_C_vol =  tank_C_volume_measure();
  while (tank_C_vol > 0.1)
  {
    delay(300);
    lcd.clear();
    lcd.print("Tank C = ");
    lcd.print(tank_C_vol);
    char customKey = kpd.getKey();
    if (customKey)
    {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
    }
    if (customKey == 'Q')
    {
      lcd.clear();
      lcd.print("Quiting...");
      digitalWrite(tankA_inlet_pump, LOW);
      digitalWrite(tankB_inlet_pump, LOW);
      digitalWrite(tankC_inlet_pump, LOW);
      digitalWrite(tankA_outlet_valve, LOW);
      digitalWrite(tankB_outlet_valve, LOW);
      delay(1500);
      doloop();
    }
    if (customKey == '*')
    {
      digitalWrite(reSet, LOW);
    }
    tank_C_vol =  tank_C_volume_measure();
    // Activate A outlet valve
    digitalWrite (tankA_inlet_pump, HIGH);
    digitalWrite (tankA_outlet_valve, HIGH);
  }
  if (tank_C_vol < 1)
  {
      empty_tank_A();
    digitalWrite (tankA_outlet_valve, LOW);
    digitalWrite (tankA_inlet_pump, LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);


}
///////////////////////////////////////////////////////////
void empty_all_tanks()
{
  empty_tank_A();
  empty_tank_B();
  empty_tank_C();
  empty_tank_A();
}
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
void fill_tank_A()
{

  double tank_A_vol =  tank_A_volume_measure();
  while (tank_A_vol < 200)
  {
    delay(300);
    lcd.clear();
    lcd.print("Tank A = ");
    lcd.print(tank_A_vol);

    char customKey = kpd.getKey();
    if (customKey)
    {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
    }
    if (customKey == 'Q')
    {
      lcd.clear();
      lcd.print("Quiting...");
      digitalWrite(tankA_inlet_pump, LOW);
      digitalWrite(tankB_inlet_pump, LOW);
      digitalWrite(tankC_inlet_pump, LOW);
      digitalWrite(tankA_outlet_valve, LOW);
      digitalWrite(tankB_outlet_valve, LOW);
      delay(1500);
      doloop();
    }
    if (customKey == '*')
    {
      digitalWrite(reSet, LOW);
    }
    tank_A_vol =  tank_A_volume_measure();
    // Activate A outlet valve
    digitalWrite (tankA_inlet_pump, HIGH);
  }
  if (tank_A_vol > 210)
  {
    digitalWrite (tankA_inlet_pump, LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);

}
///////////////////////////////////////////////////////////
void fill_tank_B()
{

  double tank_B_vol =  tank_B_volume_measure();
  while (tank_B_vol < 200)
  {
    delay(300);
    lcd.clear();
    lcd.print("Tank B = ");
    lcd.print(tank_B_vol);

    char customKey = kpd.getKey();
    if (customKey)
    {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
    }
    if (customKey == 'Q')
    {
      lcd.clear();
      lcd.print("Quiting...");
      digitalWrite(tankA_inlet_pump, LOW);
      digitalWrite(tankB_inlet_pump, LOW);
      digitalWrite(tankC_inlet_pump, LOW);
      digitalWrite(tankA_outlet_valve, LOW);
      digitalWrite(tankB_outlet_valve, LOW);
      delay(1500);
      doloop();
    }
    if (customKey == '*')
    {
      digitalWrite(reSet, LOW);
    }
    tank_B_vol =  tank_B_volume_measure();
    // Activate A outlet valve
    digitalWrite (tankB_inlet_pump, HIGH);
  }
  if (tank_B_vol > 210)
  {
    digitalWrite (tankB_inlet_pump, LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);

}
void fill_tank_C()
{

  double tank_C_vol =  tank_C_volume_measure();
  while (tank_C_vol < 200)
  {
    delay(300);
    lcd.clear();
    lcd.print("Tank C = ");
    lcd.print(tank_C_vol);

    char customKey = kpd.getKey();
    if (customKey)
    {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
    }
    if (customKey == 'Q')
    {
      lcd.clear();
      lcd.print("Quiting...");
      digitalWrite(tankA_inlet_pump, LOW);
      digitalWrite(tankB_inlet_pump, LOW);
      digitalWrite(tankC_inlet_pump, LOW);
      digitalWrite(tankA_outlet_valve, LOW);
      digitalWrite(tankB_outlet_valve, LOW);
      delay(1500);
      doloop();
    }
    if (customKey == '*')
    {
      digitalWrite(reSet, LOW);
    }
    tank_C_vol =  tank_C_volume_measure();
    // Activate A outlet valve
    digitalWrite (tankC_inlet_pump, HIGH);
  }
  if (tank_C_vol > 210)
  {
    digitalWrite (tankC_inlet_pump, LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);

}
///////////////////////////////////////////////////////////
void fill_all_tanks()
{

  fill_tank_B();
  fill_tank_C();
  fill_tank_A();
  fill_tank_C();
  fill_tank_A();
  fill_tank_C();
}
///////////////////////////////////////////////////////////
void setTankA()
{
  double tank_A_vol =  tank_A_volume_measure();
  while (tank_A_vol < tankA)
  {
    delay(300);
    lcd.clear();
    lcd.print("Tank A = ");
    lcd.print(tank_A_vol);

    char customKey = kpd.getKey();
    if (customKey)
    {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
    }
    if (customKey == 'Q')
    {
      lcd.clear();
      lcd.print("Quiting...");
      digitalWrite(tankA_inlet_pump, LOW);
      digitalWrite(tankB_inlet_pump, LOW);
      digitalWrite(tankC_inlet_pump, LOW);
      digitalWrite(tankA_outlet_valve, LOW);
      digitalWrite(tankB_outlet_valve, LOW);
      delay(1500);
      doloop();
    }
    if (customKey == '*')
    {
      digitalWrite(reSet, LOW);
    }
    tank_A_vol =  tank_A_volume_measure();
    // Activate A outlet valve
    digitalWrite (tankA_inlet_pump, HIGH);
  }
  if (tank_A_vol > tankA)
  {
    digitalWrite (tankA_inlet_pump, LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);

}
///////////////////////////////////////////////////////////
void setTankB()
{
  
  double tank_B_vol =  tank_B_volume_measure();
  while (tank_B_vol < tankB)
  {
    delay(300);
    lcd.clear();
    lcd.print("Tank B = ");
    lcd.print(tank_B_vol);

    char customKey = kpd.getKey();
    if (customKey)
    {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
    }
    if (customKey == 'Q')
    {
      lcd.clear();
      lcd.print("Quiting...");
      digitalWrite(tankA_inlet_pump, LOW);
      digitalWrite(tankB_inlet_pump, LOW);
      digitalWrite(tankC_inlet_pump, LOW);
      digitalWrite(tankA_outlet_valve, LOW);
      digitalWrite(tankB_outlet_valve, LOW);
      delay(1500);
      doloop();
    }
    if (customKey == '*')
    {
      digitalWrite(reSet, LOW);
    }
    tank_B_vol =  tank_B_volume_measure();
    // Activate A outlet valve
    digitalWrite (tankB_inlet_pump, HIGH);
  }
  if (tank_B_vol > tankB)
  {
    digitalWrite (tankB_inlet_pump, LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
}
///////////////////////////////////////////////////////////
void setTankC()
{
  double tank_C_vol =  tank_C_volume_measure();
  while (tank_C_vol < tankC)
  {
    delay(300);
    lcd.clear();
    lcd.print("Tank C = ");
    lcd.print(tank_C_vol);

    char customKey = kpd.getKey();
    if (customKey)
    {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
    }
    if (customKey == 'Q')
    {
      lcd.clear();
      lcd.print("Quiting...");
      digitalWrite(tankA_inlet_pump, LOW);
      digitalWrite(tankB_inlet_pump, LOW);
      digitalWrite(tankC_inlet_pump, LOW);
      digitalWrite(tankA_outlet_valve, LOW);
      digitalWrite(tankB_outlet_valve, LOW);
      delay(1500);
      doloop();
    }
    if (customKey == '*')
    {
      digitalWrite(reSet, LOW);
    }
    tank_C_vol =  tank_C_volume_measure();
    // Activate A outlet valve
    digitalWrite (tankC_inlet_pump, HIGH);
  }
  if (tank_C_vol > tankC)
  {
    digitalWrite (tankC_inlet_pump, LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
}
///////////////////////////////////////////////////////////
void setTankC_for_A()
{
  double tank_C_vol =  tank_C_volume_measure();
  int new_tankC = tankA+15;
  while (tank_C_vol < new_tankC)
  {
    delay(300);
    lcd.clear();
    lcd.print("Tank C = ");
    lcd.print(tank_C_vol);

    char customKey = kpd.getKey();
    if (customKey)
    {
      digitalWrite (buzzer, HIGH);
      delay(50);
      digitalWrite (buzzer, LOW);
    }
    if (customKey == 'Q')
    {
      lcd.clear();
      lcd.print("Quiting...");
      digitalWrite(tankA_inlet_pump, LOW);
      digitalWrite(tankB_inlet_pump, LOW);
      digitalWrite(tankC_inlet_pump, LOW);
      digitalWrite(tankA_outlet_valve, LOW);
      digitalWrite(tankB_outlet_valve, LOW);
      delay(1500);
      doloop();
    }
    if (customKey == '*')
    {
      digitalWrite(reSet, LOW);
    }
    tank_C_vol =  tank_C_volume_measure();
    // Activate A outlet valve
    digitalWrite (tankC_inlet_pump, HIGH);
  }
  if (tank_C_vol > new_tankC)
  {
    digitalWrite (tankC_inlet_pump, LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(70);
}
///////////////////////////////////////////////////////////
void action()
{

 empty_all_tanks();
 

}
///////////////////////////////////////////////////////////
void currentVolumes()
{
  numbers = 0;
  words = "";
  customKey = 0;
  tank_A_volume_measure();
  tank_B_volume_measure();
  double tank_A_vol =  tank_A_volume_measure();
  double tank_B_vol =  tank_B_volume_measure();
  double tank_C_vol =  tank_C_volume_measure();
  char customKey = kpd.getKey();
  if (customKey)
  {
    if (customKey == 'B')
    {
      lcd.clear();
      lcd.print("Emptying all tanks...");
      delay(1500);
      empty_all_tanks();
    }
    if (customKey == 'A')
    {
      lcd.clear();
      lcd.print("Filling all tanks...");
      delay(1500);
      fill_all_tanks();
    }
    getTankA();
    customKey = 0;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tank A = ");
  lcd.print(tank_A_vol);
  lcd.print("cl");
  lcd.setCursor(0, 1);
  lcd.print("Tank B = ");
  lcd.print(tank_B_vol);
  //lcd.print(ult_2_distance);
  lcd.print("cl");
  lcd.setCursor(0, 2);
  lcd.print("Tank C = ");
  lcd.print(tank_C_vol);
  lcd.print("cl");

  delay(600);
  doloop();
}
////////////////////////////////////////////////////////////////
double volumeCalc(double ult_dist)
{
  double volume = 0;
  double fluid_height = 8.5 - ult_dist;
  if (fluid_height < 0)
  {
    fluid_height = 0;
  }
  volume = (fluid_height * volumeConstant) / 10;
  return volume;
}
///////////////////////////////////////////////////////////
double tank_A_volume_measure()
{

  digitalWrite(ult_1_trig, HIGH);
  delayMicroseconds(1000);

  digitalWrite(ult_1_trig, LOW);

  ult_1_duration = pulseIn(ult_1_echo, HIGH);
  ult_1_distance = ((ult_1_duration / 2) / 29.1) - 3.3;

  double tank_A_vol = volumeCalc(ult_1_distance);
  Serial.println (tank_A_vol);
  delay (10);
  return tank_A_vol;
}

///////////////////////////////////////////////////////////
double tank_B_volume_measure()
{

  digitalWrite(ult_2_trig, HIGH);
  delayMicroseconds(1000);

  digitalWrite(ult_2_trig, LOW);

  ult_2_duration = pulseIn(ult_2_echo, HIGH);
  ult_2_distance = ((ult_2_duration / 2) / 29.1) - 3.3;

  double tank_B_vol = (volumeCalc(ult_2_distance));
  Serial.println (tank_B_vol);
  delay (10);
  return tank_B_vol;
}

///////////////////////////////////////////////////////////
double tank_C_volume_measure()
{

  digitalWrite(ult_3_trig, HIGH);
  delayMicroseconds(1000);

  digitalWrite(ult_3_trig, LOW);

  ult_3_duration = pulseIn(ult_3_echo, HIGH);
  ult_3_distance = ((ult_3_duration / 2) / 29.1) - 3.3;

  double tank_C_vol = volumeCalc(ult_3_distance);
  Serial.println (tank_C_vol);
  delay (10);
  return tank_C_vol;
}

///////////////////////////////////////////////////////////
void checkinglcdloading()
{
  for (int i = 0; i < 3; i++)
  {
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(10);
    delay (200);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(1);
    delay (200);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(2);
    delay (200);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(3);
    delay (200);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(4);
    delay (200);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(5);
    delay (200);
    lcd.clear();
    delay (2);

  }
}
/////////////////////////////////////////////////////////////
void kosviewintro()
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

  do
  {
    lcd.scrollDisplayLeft();
    pos++;
    delay(5);
  }
  while (pos < 40);

  pos = 0;

  do
  {
    lcd.scrollDisplayRight();
    pos++;
    delay(5);
  }
  while (pos < 40);
  delay (1000);
  pos = 0;
  lcd.clear();



}
