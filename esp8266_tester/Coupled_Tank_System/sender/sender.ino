int val = 100;
int val2 = 1000;
String a = "food";
String b = "water";


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(val);
    delay(3000);
  val++;
  Serial.println(a);
  delay(2000);

  Serial.println(val2);
    delay(1000);
  val2++;

    
   Serial.println(b);
  delay(2000);
 
   
}
