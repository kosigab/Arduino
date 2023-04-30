#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 20x4 display

const byte ROWS = 4;  // four rows
const byte COLS = 4;  // four columns
char keys[ROWS][COLS] = {
  { '1', '2', '3', '+' },
  { '4', '5', '6', '-' },
  { '7', '8', '9', 'C' },
  { '*', '0', '=', '/' }
};
byte rowPins[ROWS] = { 10, 9, 8, 7 };  // connect to the row pinouts of the keypad
byte colPins[COLS] = { 6, 5, 4, 3 };   // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

double num1, num2, result;
String input = "";
boolean isDecimal = false;
char operation;

unsigned long decimalHoldStart = 0;
const int decimalHoldThreshold = 2000;  // 2 seconds

void setup() {
  lcd.init();  // initialize the LCD
  lcd.backlight();
  lcd.clear();
  lcd.print("Welcome to Calculator");
  delay(1000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    if (key >= '0' && key <= '9') {
      if (key == '0' && (millis() - decimalHoldStart >= decimalHoldThreshold)) {
        if (!isDecimal) {
          input += '.';
          lcd.print('.');
          isDecimal = true;
        }
        decimalHoldStart = 0;
      } else {
        if (key == '0') {
          input += key;
        } else {
          input += key;
          lcd.print(key);
        }
        decimalHoldStart = 0;
      }
    } else if (key == '+' || key == '-' || key == '*' || key == '/') {
      num1 = input.toDouble();
      input = "";
      isDecimal = false;
      operation = key;
      lcd.print(key);
    } else if (key == '=') {
      num2 = input.toDouble();
      input = "";
      isDecimal = false;
      switch (operation) {
        case '+':
          result = num1 + num2;
          break;
        case '-':
          result = num1 - num2;
          break;
        case '*':
          result = num1 * num2;
          break;
        case '/':
          result = num1 / num2;
          break;
      }
      lcd.clear();
      lcd.print(result);
    } else if (key == 'C') {
      input = "";
      num1 = 0;
      num2 = 0;
      isDecimal = false;
      lcd.clear();
    }
    if (key == '0') {
      decimalHoldStart = millis();
    }
  }
}
