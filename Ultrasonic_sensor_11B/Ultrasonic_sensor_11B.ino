int LDRpin = 14;
int Light_intensity;
int First_LED = 10;

int ult_1_trig = 11;
int ult_1_echo = 15;
int ult_1_LED = 3;

int ult_2_trig = 2;
int ult_2_echo = 4;
int ult_2_LED = 5;

int ult_3_trig = 7;
int ult_3_echo = 8;
int ult_3_LED = 18;

int ult_4_trig = 12;
int ult_4_echo = 13;
int ult_4_LED = 9;

int ult_5_trig = 16;
int ult_5_echo = 17;

int state = 0;

long ult_1_duration, ult_1_distance;
long ult_2_duration, ult_2_distance;
long ult_3_duration, ult_3_distance;
long ult_4_duration, ult_4_distance;
long ult_5_duration, ult_5_distance;



//////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:

  pinMode (First_LED, OUTPUT);
  //pinMode (LDRpin, INPUT);

  pinMode (ult_1_trig, OUTPUT);
  pinMode (ult_1_echo, INPUT);
  pinMode (ult_1_LED, OUTPUT);

  // pinMode (LDRpin, OUTPUT);

  pinMode (ult_2_trig, OUTPUT);
  pinMode (ult_2_echo, INPUT);
  pinMode (ult_2_LED, OUTPUT);

  pinMode (ult_3_trig, OUTPUT);
  pinMode (ult_3_echo, INPUT);
  pinMode (ult_3_LED, OUTPUT);

  pinMode (ult_4_trig, OUTPUT);
  pinMode (ult_4_echo, INPUT);
  pinMode (ult_4_LED, OUTPUT);

  pinMode (ult_5_trig, OUTPUT);
  pinMode (ult_5_echo, INPUT);
  digitalWrite(ult_2_LED,LOW);

  //analogWrite(ult_1_LED, 5);
  //analogWrite(ult_2_LED, 5);
  //analogWrite(ult_3_LED, 5);
  //analogWrite(ult_4_LED, 5);


  Serial.begin(9600);
}
//////////////////////////////////////////////////////////////////////////////////////////

void loop()
{

  ult_1_distance_measure();
  ult_2_distance_measure();
  ult_3_distance_measure();
  ult_4_distance_measure();
  ult_5_distance_measure();

  Check_Light_intensity();
  
  // digitalWrite(ult_2_LED,LOW);

  //  if (ult_1_distance < 30)
  //  {
  //    state = 1;
  //  }
  //  if (state == 1)
  //  {
  //  do
  //  {
  //Check_Light_intensity();
  Light_intensity = analogRead(LDRpin);
  delay (100);
  //Serial.print("Light intensity = ");
  Serial.println( Light_intensity);
  // delay (10);

  if (Light_intensity > 250)
  {
    digitalWrite(ult_1_LED, LOW);
    digitalWrite(ult_2_LED, LOW);
    digitalWrite(ult_3_LED, LOW);
    digitalWrite(ult_4_LED, LOW);
    digitalWrite(First_LED, LOW);
    delay (100);
    loop();
  }
  else if (Light_intensity < 250)
  {
    digitalWrite(First_LED, HIGH);
    ult_1_distance_measure();
    ult_2_distance_measure();
    ult_3_distance_measure();
    ult_4_distance_measure();
    ult_5_distance_measure();

    if (ult_1_distance < 30)
    {
      digitalWrite(ult_1_LED, HIGH);
    }
    if ((ult_1_distance > 30) && (ult_3_distance < 30))
    {
      analogWrite(ult_1_LED, 10);
    }

    //2

    if (ult_2_distance < 20)
    {
      digitalWrite(ult_2_LED, HIGH);
    }

    if ((ult_2_distance > 30) && (ult_4_distance < 30))
    {
      analogWrite(ult_2_LED, 10);
    }

    //3

    if (ult_3_distance < 30)
    {
      digitalWrite(ult_3_LED, HIGH);
    }
    if ((ult_3_distance > 30) && (ult_5_distance < 30))
    {

      analogWrite(ult_3_LED, 10);
    }

    //4

    if (ult_4_distance < 30)
    {
      digitalWrite(ult_4_LED, HIGH);
    }
    if ((ult_4_distance > 30) & (ult_5_distance < 30))
    {
      //// delay (2000);
      analogWrite(ult_4_LED, 10);
    }
    //5
     if (ult_5_distance < 30)
  {
    digitalWrite(ult_1_LED, LOW);
    digitalWrite(ult_2_LED, LOW);
    digitalWrite(ult_3_LED, LOW);
    digitalWrite(ult_4_LED, LOW);
  }
    delay (10);

  }
}
//////////////////////////////////////////////////////////////////////////////////////////

void Check_Light_intensity()
{
  Light_intensity = analogRead(LDRpin);
  delay (100);
  if (Light_intensity < 250)
  {
    digitalWrite(First_LED, HIGH);
  }

  Serial.println( Light_intensity);
  
  if (Light_intensity > 250)
  {
    
    digitalWrite(ult_1_LED, LOW);
    digitalWrite(ult_2_LED, LOW);
    digitalWrite(ult_3_LED, LOW);
    digitalWrite(ult_4_LED, LOW);
    digitalWrite(First_LED, LOW);
    delay (100);
   
  }
}


//////////////////////////////////////////////////////////////////////////////////////////

void ult_1_distance_measure()
{

  digitalWrite(ult_1_trig, HIGH);
  delayMicroseconds(200);

  digitalWrite(ult_1_trig, LOW);

  ult_1_duration = pulseIn(ult_1_echo, HIGH);
  ult_1_distance = (ult_1_duration / 2) / 29.1;
  //  Serial.println (ult_1_distance);
  // delay (10);

}
//////////////////////////////////////////////////////////////////////////////////////////,

void ult_2_distance_measure()
{
  digitalWrite(ult_2_trig, HIGH);
  delayMicroseconds(200);

  digitalWrite(ult_2_trig, LOW);

  ult_2_duration = pulseIn(ult_2_echo, HIGH);
  ult_2_distance = (ult_2_duration / 2) / 29.1;
  //  Serial.println (ult_2_distance);
  // delay (10);

}
//////////////////////////////////////////////////////////////////////////////////////////

void ult_3_distance_measure()
{


  digitalWrite(ult_3_trig, HIGH);
  delayMicroseconds(200);

  digitalWrite(ult_3_trig, LOW);

  ult_3_duration = pulseIn(ult_3_echo, HIGH);
  ult_3_distance = (ult_3_duration / 2) / 29.1;
  // Serial.println (ult_3_distance);
  //  delay (10);

}
//////////////////////////////////////////////////////////////////////////////////////////
//
void ult_4_distance_measure()                      //
{ //
  //
  digitalWrite(ult_4_trig, HIGH);                  //
  delayMicroseconds(200);                          //
  //
  digitalWrite(ult_4_trig, LOW);                   //
  //
  ult_4_duration = pulseIn(ult_4_echo, HIGH);      //
  ult_4_distance = (ult_4_duration / 2) / 29.1;    //
  // Serial.println(ult_4_distance);               //
  // delay (10);                                   //
  //
}                                                  //
//////////////////////////////////////////////////////////////////////////////////////////

void ult_5_distance_measure()
{

  digitalWrite(ult_5_trig, HIGH);
  delayMicroseconds(200);

  digitalWrite(ult_5_trig, LOW);

  ult_5_duration = pulseIn(ult_5_echo, HIGH);
  ult_5_distance = (ult_5_duration / 2) / 29.1;
}


void mainloop()
{
  //  digitalWrite(First_LED, HIGH);
  //
  //  if (ult_1_distance < 30)
  //  {
  //    state = 1;
  //  }
  //  if (state == 1)
  //  {
  //  do
  //  {
  //    //Check_Light_intensity();
  //      Light_intensity = analogRead(LDRpin);
  //  delay (100);
  //  //Serial.print("Light intensity = ");
  //  Serial.println( Light_intensity);
  //  // delay (10);
  //
  //   if (Light_intensity > 250)
  //  {
  //    digitalWrite(ult_1_LED, LOW);
  //    digitalWrite(ult_2_LED, LOW);
  //    digitalWrite(ult_3_LED, LOW);
  //    digitalWrite(ult_4_LED, LOW);
  //    digitalWrite(First_LED, LOW);
  //    delay (100);
  //    loop();
  //  }
  //    ult_1_distance_measure();
  //    ult_2_distance_measure();
  //    ult_3_distance_measure();
  //    ult_4_distance_measure();
  //    ult_5_distance_measure();
  //
  //    if (ult_1_distance < 30)
  //    {
  //      digitalWrite(ult_1_LED, HIGH);
  //    }
  //    if ((ult_1_distance > 30) & (ult_3_distance < 30))
  //    {
  //      analogWrite(ult_1_LED, 10);
  //    }
  //
  //    //2
  //
  //    if (ult_2_distance < 30)
  //    {
  //      digitalWrite(ult_2_LED, HIGH);
  //    }
  //
  //    if ((ult_2_distance > 30) & (ult_4_distance < 30))
  //    {
  //      analogWrite(ult_2_LED, 10);
  //    }
  //
  //    //3
  //
  //    if (ult_3_distance < 30)
  //    {
  //      digitalWrite(ult_3_LED, HIGH);
  //    }
  //    if ((ult_3_distance > 30) & (ult_5_distance < 30))
  //    {
  //
  //      analogWrite(ult_3_LED, 10);
  //    }
  //
  //    //4
  //
  //    if (ult_4_distance < 30)
  //    {
  //      digitalWrite(ult_4_LED, HIGH);
  //    }
  //    if ((ult_4_distance > 30) & (ult_5_distance < 30))
  //    {
  //      //// delay (2000);
  //      analogWrite(ult_4_LED, 10);
  //    }

  if (ult_5_distance < 30)
  {
    state = 2;
  }
  //    if (Light_intensity > 250)
  //    {
  //      digitalWrite(ult_1_LED, LOW);
  //      digitalWrite(ult_2_LED, LOW);
  //      digitalWrite(ult_3_LED, LOW);
  //      digitalWrite(ult_4_LED, LOW);
  //      digitalWrite(First_LED, LOW);
  //      delay (1000);
  //    }

}




////////////////////////////////////////
// delay (1000);



