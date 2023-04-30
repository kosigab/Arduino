#include <Wire.h>
#include <LiquidCrystal_I2C.h>


int pos = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
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
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(14, INPUT);
  Serial.begin(9600);

  lcd.init();  // initialize the lcd
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
  displayIntro();
}

void loop() {
  loading(700);
}




void displayIntro() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("----------_________.");
  lcd.setCursor(0, 1);
  lcd.print("|     KOSVIEW      |");
  lcd.setCursor(0, 2);
  lcd.print("|     PROJECTS     |");
  lcd.setCursor(0, 3);
  lcd.print("----------_________|");
  delay(2000);

  do {
    lcd.scrollDisplayLeft();
    pos++;
    delay(5);
  } while (pos < 40);

  pos = 0;

  do {
    lcd.scrollDisplayRight();
    pos++;
    delay(5);
  } while (pos < 40);
  delay(1000);
  pos = 0;
  lcd.clear();
}

void loading(int speed) {

  lcd.setCursor(10, 1);
    lcd.write(0);
    delay(speed);
    lcd.clear();
    lcd.setCursor(10, 1);
    lcd.write(1);
    delay(speed);
    lcd.clear();
    lcd.setCursor(10, 1);
    lcd.write(2);
    delay(speed);
    lcd.clear();
    lcd.setCursor(10, 1);
    lcd.write(3);
    delay(speed);
    lcd.clear();
    lcd.setCursor(10, 1);
    lcd.write(4);
    delay(speed);
    lcd.clear();
    lcd.setCursor(10, 1);
    lcd.write(5);
    delay(speed);
    lcd.clear();
    
}
