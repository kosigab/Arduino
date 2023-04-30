#include <Keypad.h>
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

const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
char keys[ROWS][COLS] = {
  { '1', '2', '3', '+' },
  { '4', '5', '6', '-' },
  { '7', '8', '9', 'C' },
  { '*', '0', '=', '/' }
};
byte rowPins[ROWS] = { 10, 9, 8, 7 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 6, 5, 4, 3 };   //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
String input = "";
String fullLine = "";

unsigned long cursorBlinkDelay = 500;  // time in milliseconds for cursor blink delay
unsigned long lastCursorBlink = 0;
int cursorPosition = 0;  // current cursor position
boolean cursorBlinkState = false;


void setup() {
  Serial.begin(9600);
  Serial.println("initialized...");
  pinMode(2, OUTPUT);
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
  displayIntro(.001);
}



void loop() {
  // loading(700);
  keypadInput();
  cursorBlinkNoDelay();
}

void cursorBlinkNoDelay() {
  if (millis() - lastCursorBlink >= cursorBlinkDelay) {
    lastCursorBlink = millis();
    cursorBlinkState = !cursorBlinkState;
    // lcd.setCursor(cursorPosition, 0); // set cursor position
    if (cursorBlinkState) {
      lcd.cursor();  // turn on cursor
    } else {
      lcd.noCursor();  // turn off cursor
    }
  }
}

//string val = "";

void keypadInput() {

  char key = keypad.getKey();
  displayKey(key);
  if ((key == '*') || (key == '/') || (key == '+') || (key == '-') || (key == '=')) {
    double val = input.toDouble();
    mathOp(key, val);
    fullLine += input;
    lcd.setCursor(0, 1);
    lcd.print(fullLine);
    lcdClearLine(0);

    input = "";
  }
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void lcdClearLine(int line) {
  lcd.setCursor(0, line);
  for (int i = 0; i < 20; i++) {
    lcd.print(" ");
  }

  lcd.setCursor(0, line);
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

double val1 = 1557.1557;
double val2 = 1557.1557;
double sol = 0;
char prevOp = 'a';

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void mathOp(char op, double val) {


  if (val1 == 1557.1557) {
    val1 = val;
    Serial.print("Val1 = ");
    Serial.println(val);
  }

  else {
    val2 = val;
    Serial.print("Val2 = ");
    Serial.println(val);
  }
  if ((val2 != 1557.1557) || (op == '=')) {
    Serial.print("In SWITCH");
    switch (prevOp) {
      case '*':
        sol = val1 * val2;
        val1 = sol;
        
        Serial.print("prevOp *>|  ");
        Serial.println(prevOp);
        break;
      case '+':
        sol = val1 + val2;
        val1 = sol;
        
        Serial.print("prevOp +>|  ");
        Serial.println(prevOp);
        break;
      case '-':
        sol = val1 - val2;
        val1 = sol;
        
        Serial.print("prevOp ->|  ");
        Serial.println(prevOp);
        break;
      case '/':
        sol = val1 / val2;
        val1 = sol;
       ;
        Serial.print("prevOp />|  ");
        Serial.println(prevOp);
        break;
        default:
        sol = val1;
    }
  }
  prevOp = op;
  Serial.print("prevOp ~>  ");
  Serial.println(prevOp);
  lcd.setCursor(0, 3);
  // lcd.rightToLeft();
  lcd.print(sol);
  Serial.print("sol = ");
  Serial.println(sol);
  lcd.setCursor(0, 0);

}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void displayKey(char key) {
  if (key) {
    digitalWrite(2, HIGH);
    delay(10);
    digitalWrite(2, LOW);
    if (key == 'C') {  //if the # key is pressed, return the input string
      lcd.clear();
      val1 = 1557.1557;
      val2 = 1557.1557;
      sol = 0;
      fullLine = "";


      input = "";  //clear the input string for next time
    } else {
      input += key;
      //lcd.clear();
      lcd.print(key);  //add the pressed key to the input string
    }
  }
}

void displayIntro(double duration) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("----------_________.");
  lcd.setCursor(0, 1);
  lcd.print("|     KOSVIEW      |");
  lcd.setCursor(0, 2);
  lcd.print("|     PROJECTS     |");
  lcd.setCursor(0, 3);
  lcd.print("----------_________|");
  duration = duration > 1 ? 1 : duration;
  delay(2000 * duration);

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
  delay(1000 * duration);
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
