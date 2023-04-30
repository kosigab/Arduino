double a =0;
double b =0;
void setup() {
Serial.begin(9600);
pinMode (10, OUTPUT);
pinMode (11, OUTPUT);
pinMode (12, OUTPUT);
pinMode (13, OUTPUT);
digitalWrite (10, LOW);
digitalWrite (11, LOW);
digitalWrite (12, LOW);
digitalWrite (13, LOW);
}

void loop() {
  for (int i=0; i<100; i++)
  {
  a = analogRead (18);
  if (a>b) b =a;
  delay (10);
  }
  
  Serial.println(b);
  
  delay (300);
}
