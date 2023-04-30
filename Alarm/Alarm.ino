#include <virtuabotixRTC.h>

virtuabotixRTC myRTC(5, 4, 6);
int tempMin = 0;
void setup() {
  // put your setup code here, to run once:
  myRTC.setDS1302Time(0, 35, 20, 4, 19, 9, 2018);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  myRTC.updateTime();
if (myRTC.minutes > tempMin)
  {
    Serial.print("Temp Min = ");
    Serial.println(tempMin);
  }

  tempMin = myRTC.minutes;
  
}
