#include <SPI.h>
#include "RF24.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};
float cell = 0;

int val;
int tempPin = 14;

struct package
{
  int id = 1;
  float cel = 0;
  char  text[100] = "Node 1 temperature";
};


typedef struct package Package;
Package data;

// Connect LM35 pin 2 to Arduino pin A1//

void setup()
{
  Serial.begin(115200);
  delay(1000);
  myRadio.begin();
  myRadio.setChannel(205);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);
}

void loop()
{
  val = analogRead(tempPin);
  float mv = ( val / 1024.0) * 5000;
  float cel = mv / 10;
  struct package
  {
    int id = 1;
    float cel = mv / 10;
    char  text[100] = "Node 1 temperature";
  };
  myRadio.write(&data, sizeof(data));

  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.cel);
  Serial.println(data.text);
  data.id = data.id + 1;
  //data.temperature = data.temperature+0.1;

data.cel = cel;



//  float farh = (cel * 9) / 5 + 32;
 
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();

  delay(1000);

}
