
#include <LiquidCrystal.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define blue 13
#define green 12
#define red 11
#define buzzer 18
#define ph_monitor 16
#define turbidity_monitor1 17

LiquidCrystal lcd(2, 3, 4, 5, 6, 9);

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

double ph_gradient = 0;
double turbidity_gradient = 0;
double ph_impurity = 0;
double turbidity_impurity = 0;
double impurity = 0;
double ph = 0;
double ph_analog_value = 0;
int turbidity = 0;





void setup()
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  lcd.begin (16, 2);
  lcd.setCursor(0, 0);

  Serial.begin(9600);

  pinMode (ph_monitor, INPUT);
  pinMode (turbidity_monitor1, INPUT);

  pinMode (blue, OUTPUT);
  pinMode (green, OUTPUT);
  pinMode (red, OUTPUT);
  pinMode (buzzer, OUTPUT);



}
void loop()
{
  measure_PH();
  measure_turbidity();
  Impurity_level();

  if (impurity > 30)
  {

    high_impurity();

  }
  else
  {
    low_impurity();

  }

  delay(1000);
  lcd.clear();
}
void measure_PH()
{
  ph_analog_value = analogRead(ph_monitor);
  ph = (7.0 / 390) * ph_analog_value;
  Serial.print("ph analog reading = ");
  Serial.println(ph_analog_value);
  Serial.print("ph = ");
  Serial.println(ph);
  lcd.setCursor(0, 0);
  lcd.print("PH = ");
  lcd.print(ph);
  delay (10);

}

void measure_turbidity()
{
  turbidity = analogRead(turbidity_monitor1);
  turbidity = turbidity - 800;
  Serial.print("turbidity1 = ");
  Serial.println(turbidity);
//  lcd.setCursor(0, 1);
//  lcd.print("Turbidity = ");
//  lcd.print(turbidity);
  delay(100);
}



void Impurity_level()
{
  ph_gradient = (ph - 7) * 1.0;
  if (ph_gradient < 0)
  {
    ph_gradient = ph_gradient * -1;
  }
  // ph_gradient = abs(ph_gradient);
  ph_impurity = 1.0 * (100 * ph_gradient) / 7;


  turbidity_impurity = (100 * (turbidity)) / 1023;

  if (ph_impurity > turbidity_impurity)
  {
    impurity = ph_impurity;
  }

  if (ph_impurity < turbidity_impurity)
  {
    impurity = turbidity_impurity;
  }
  impurity = abs(impurity);
  radio.write(&impurity, sizeof(impurity));
  lcd.setCursor(0, 2);
  lcd.print("Impurity ");
  lcd.setCursor(1, 1);
  lcd.print("-index = ");
  lcd.print(impurity);
  lcd.print("%");
}

void low_impurity()
{
  digitalWrite (buzzer, LOW);
  digitalWrite (blue, HIGH);
  delay(30);

  digitalWrite (blue, LOW);

  delay (30);
  digitalWrite (green, HIGH);
  delay (30);
  digitalWrite (green, LOW);
}


void high_impurity()
{

  digitalWrite (red, HIGH);
  digitalWrite (buzzer, HIGH);
  delay(60);

  digitalWrite (red, LOW);

  delay (60);
  digitalWrite (red, HIGH);
  delay (60);
  digitalWrite (red, LOW);
  delay (60);
  digitalWrite (red, HIGH);
  delay(30);

  digitalWrite (red, LOW);

  delay (30);
  digitalWrite (red, HIGH);
  delay (30);
  digitalWrite (red, LOW);
}

