

#define vent 8
int state=0;
void setup() {
  // put your setup code here, to run once:
pinMode (vent, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  state=digitalRead (vent);
  
  Serial.println (state);
  delay (10);

}
