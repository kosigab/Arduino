int ult_1_trig = 14;
int ult_1_echo =15;
int ult_1_LED = 3;
 long ult_1_duration, ult_1_distance;
void setup() {
 pinMode (ult_1_trig, OUTPUT);
pinMode (ult_1_echo, INPUT);
pinMode (ult_1_LED, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 ult_1_distance_measure();



 
}
void ult_1_distance_measure()
 {
  
    digitalWrite(ult_1_trig,HIGH);
    delayMicroseconds(1000);

    digitalWrite(ult_1_trig,LOW);

    ult_1_duration = pulseIn(ult_1_echo, HIGH);
    ult_1_distance= (ult_1_duration/2)/29.1;
    Serial.println (ult_1_distance);
    delay (10);
    
 }
