
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



LiquidCrystal_I2C lcd(0x3F, 20 , 4);

RF24 radio(2, 3); // CE, CSN
//RF24 radio2(2, 3);
const byte address[6] = "00001";
const byte address2[6] = "00002";

double soil_moist = 0;
double humidity = 0;
double impurity =0 ;




int  pos = 0;

byte degree[8] = {
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

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







void setup()
{
   lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  radio.begin();
   // radio2.begin();
  radio.openReadingPipe(0, address[1]);
 // radio2.openReadingPipe(0, address2[1]);

  radio.setPALevel(RF24_PA_MAX);
  //radio2.setPALevel(RF24_PA_MAX);
    radio.startListening();
//   radio2.startListening();
 
  lcd.setCursor(0, 0);

  Serial.begin(9600);
  lcd.createChar(10, f1);
  lcd.createChar(6, degree);
  lcd.createChar(1, f2);
  lcd.createChar(2, f3);
  lcd.createChar(3, f4);
  lcd.createChar(4, f5);
  lcd.createChar(5, f6);
kosview_intro();
checkinglcdloading();
}
void loop()
{ 
   if (radio.available()) {
    //   char text[32] = "";

    radio.read(&humidity, sizeof(humidity));
      
 }

 delay (200);



//if (radio2.available()) {
//    //   char text[32] = "";
//
//    radio2.read(&impurity, sizeof(impurity));
//      
// }

  lcd.clear();
  soil_moist = analogRead(14);
  soil_moist = 1023 - soil_moist;
  soil_moist = 100 * soil_moist/1023;
  Serial.println(soil_moist);
  lcd.setCursor(0,0);
  lcd.print("Soil =");
   lcd.print(soil_moist);
  
  lcd.print("%");
  lcd.setCursor(0,1);

   lcd.print("Impurity =");
   lcd.print(impurity);
  
  lcd.print("%");

   lcd.setCursor(0,2);

   lcd.print("humidity =");
   lcd.print(humidity);
  
  lcd.print("%");
 
  //radio.write(&soil_moist, sizeof(soil_moist));
  delay (700);
}

  void kosview_intro()
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
}

void checkinglcdloading()
{
  for (int i = 0; i < 3; i++)
  {
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(10);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(1);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(2);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(3);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(4);
    delay (300);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Checking system");
    lcd.setCursor(10, 1);
    lcd.write(5);
    delay (300);
    lcd.clear();
    delay (2);

  }
}
