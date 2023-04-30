const int micPin = A0;
int soundArray[10];

void setup() {

  Serial.begin(9600);
  pinMode(micPin, INPUT);

}

void loop() {

  int micValue = analogRead(micPin);
  Serial.println(micValue, DEC);
  //delay(400);

  for (int i = 0; i > 10; i++) {
    soundArray[i] = micValue;
    Serial.println(soundArray[i]);
  }
  delay(1000);
  Serial.println("End of for loop");


}
