#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 9);

#define smoke_sensor_1  14
#define smoke_sensor_2  15
#define red 8
#define blue 9
#define green 10

#define fan 12
int measure = 0;
void setup()
{
  lcd.begin(20, 4) ;
  Serial.begin(9600);
  pinMode (smoke_sensor_1, INPUT);
  pinMode (smoke_sensor_2, INPUT);
  pinMode (red, OUTPUT);
  pinMode (blue, OUTPUT);
  pinMode (green, OUTPUT);
//  pinMode (buzzer, OUTPUT);
  pinMode (fan, OUTPUT);
  digitalWrite(fan, HIGH);
  digitalWrite(green, HIGH);

  delay(1000);
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);
  delay(1000);
  digitalWrite(blue, LOW);
  digitalWrite(red, HIGH);
//  digitalWrite(buzzer, HIGH);
  delay(1000);
//  digitalWrite(buzzer, LOW);
  digitalWrite(fan, LOW);
   digitalWrite(red, LOW);

  lcd.clear();
  delay(10);
  lcd.setCursor(0, 0);
  lcd.print("    KOSVIEW");
  lcd.setCursor(0, 1);
  delay (1000);
  lcd.print("    PROJECTS   ");

  delay (1000);
  lcd.clear();
  delay (3000);

  ;
}

void loop() {
  measure = analogRead (smoke_sensor_1);
  Serial.println(measure);
  if (measure < 100)
  {
    Low_smoke_level();
  }


  if (measure > 100)
  {
    High_smoke_level();
  }


}
void High_smoke_level()
{
  digitalWrite(fan, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  digitalWrite (red, HIGH);
  delay(50);
  digitalWrite (red, LOW);
  delay(50);
  digitalWrite (red, HIGH);
  delay(50);
  digitalWrite (red, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dangerous ");
  lcd.setCursor(0, 1);
  lcd.print("Smoke levels! ");
}
void Low_smoke_level()
{
  digitalWrite(fan, LOW);
    digitalWrite(red, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print ("Testing air");
    lcd.setCursor(0, 1);
    lcd.print ("Quality...");
    digitalWrite(blue, HIGH);
    delay(50);
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    delay(50);
    digitalWrite(green, LOW);
    delay (1000);

    lcd.clear();
    lcd.print("Smoke value ");
    lcd.setCursor(0, 1);
    lcd.print(" = ");
    lcd.print(measure);
    digitalWrite(blue, HIGH);
    delay(50);
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    delay(50);
    digitalWrite(green, LOW);
    delay(1000);
    lcd.clear();

}

