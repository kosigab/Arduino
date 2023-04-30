
int Light_intensity;
int LDRpin =14;

void setup() {
   Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
{
 Light_intensity = analogRead(LDRpin);
  //delay (1000);
  //Serial.print("Light intensity = ");
  Serial.println( Light_intensity);
  // delay (10);

}
}
