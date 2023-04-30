  int a=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(14, INPUT);
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
a = analogRead(14);
Serial.println (a);
delay
(500);
}
