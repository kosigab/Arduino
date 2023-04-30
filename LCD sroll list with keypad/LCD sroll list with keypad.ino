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
String list[] = {"item 1", "item 2", "item 3", "item 4", "item 5", "item 6", "item 7", "item 8", "item 9", "item 10"};
int listSize = sizeof(list) / sizeof(list[0]); // number of items in the list
int currentIndex = 0; // keep track of the current item being displayed
int firstVisibleIndex = 0; // keep track of the first item visible on the LCD

void setup() {
  lcd.init();
  lcd.backlight();
  displayList();
}

void loop() {
  char key = keypad.getKey();

  if (key == '1') { // scroll up
    if (firstVisibleIndex > 0) firstVisibleIndex--;
    displayList();
  }

  if (key == '2') { // scroll down
    if (firstVisibleIndex < listSize - 4) firstVisibleIndex++;
    displayList();
  }
}

// function to display the current items in the list
void displayList() {
  lcd.clear();
  for (int i = 0; i < 4; i++) {
    lcd.setCursor(0, i);
    if (firstVisibleIndex + i < listSize) {
      lcd.print(list[firstVisibleIndex + i]);
    }
  }
}
