#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 20x4 display

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns
char keys[ROWS][COLS] = {
  { '1', '2', '3', '+' },
  { '4', '5', '6', '-' },
  { '7', '8', '9', 'C' },
  { '*', '0', '=', '/' }
};
byte rowPins[ROWS] = { 10, 9, 8, 7 }; // connect to the row pinouts of the keypad
byte colPins[COLS] = { 6, 5, 4, 3 }; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// list of strings to display on the LCD
String list[] = {"item 1", "item 2", "item 3", "item 4", "item 5"};
int listSize = sizeof(list) / sizeof(list[0]); // number of items in the list
int currentIndex = 0; // keep track of the current item being displayed

void setup() {
 lcd.init();  // ini
  lcd.backlight();
}

void loop() {
  char key = keypad.getKey();

  if (key == '1') { // move to the previous item in the list
    currentIndex--;
    if (currentIndex < 0) currentIndex = listSize - 1; // loop back to the last item in the list
    displayListItem();
  }

  if (key == '2') { // move to the next item in the list
    currentIndex++;
    if (currentIndex == listSize) currentIndex = 0; // loop back to the first item in the list
    displayListItem();
  }
}

// function to display the current item in the list
void displayListItem() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(list[currentIndex]);
}
