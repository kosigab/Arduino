
#define mA1 2
#define mA2 3
#define mB1 4
#define mB2 5
#define red 10
#define green 11
#define servopin 6
#define buzzer 9
#include <Servo.h>
int ult_1_trig = 7;
int ult_1_echo = 8;
long ult_1_duration, ult_1_distance;
long straight_Distance, left_45_Distance, left_30_Distance, right_135_Distance, right_150_Distance;
Servo myservo;
int random_Move = 0;

///////////////////////////////////////////////////

void setup() {
  pinMode (ult_1_trig, OUTPUT);
  pinMode (ult_1_echo, INPUT);
  pinMode (buzzer, OUTPUT);
  pinMode (mA1, OUTPUT);
  pinMode (mA2, OUTPUT);
  pinMode (mB1, OUTPUT);
  pinMode (mB2, OUTPUT);

  pinMode (red, OUTPUT);
  pinMode (green, OUTPUT);
  myservo.attach(servopin);
  look_Around();
}

///////////////////////////////////////////////////

void loop()
{

  if (straight_Distance > 20)
  {
    go_Straight();
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    stop_Movement();
    myservo.write(90);
    delay(50);
    ult_1_distance_measure();
    straight_Distance = ult_1_distance;

  }

  if (straight_Distance <= 20)
  {
     digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    stop_Movement();
    reverse();
    buzz_Fast();
    delay(50);

    stop_Movement();
    look_Around();

    if ((left_45_Distance > right_135_Distance) && (left_45_Distance > 20))
    {
      turn_Left();
      delay (120);
      stop_Movement();
      look_Around();
    }

    else if ((right_135_Distance > left_45_Distance) && (right_135_Distance > 20))
    {
      turn_Right();
      delay(150);
      stop_Movement();
      look_Around();
    }
  }
  loop();

  //  random_Move = rand() % 30;
  //
  //  if ((random_Move == 7)||(random_Move == 15))
  //  {
  //    stop_Movement();
  //    turn_Left();
  //    delay(700);
  //
  //    turn_Right();
  //    delay(700);
  //    stop_Movement();
  //    go_Straight();
  //    delay(100);
  //     stop_Movement();
  //    reverse();
  //    delay(100);
  //  }


}

///////////////////////////////////////////////////

void ult_1_distance_measure()
{

  digitalWrite(ult_1_trig, HIGH);
  delayMicroseconds(200);

  digitalWrite(ult_1_trig, LOW);

  ult_1_duration = pulseIn(ult_1_echo, HIGH);
  ult_1_distance = (ult_1_duration / 2) / 29.1;

}


///////////////////////////////////////////////////

void look_Straight()
{
  myservo.write(90);
  delay(100);
  ult_1_distance_measure();
  straight_Distance = ult_1_distance;
}

///////////////////////////////////////////////////

void look_Left()
{
  myservo.write(165);
  delay(200);
  ult_1_distance_measure();
  left_45_Distance = ult_1_distance;

  myservo.write(180);
  delay(150);
  ult_1_distance_measure();
  left_30_Distance = ult_1_distance;

}

////////////////////////////////////////////////////

void look_Right()
{
  myservo.write(20);
  delay(200);
  ult_1_distance_measure();
  right_135_Distance = ult_1_distance;

  myservo.write(0);
  delay(150);
  ult_1_distance_measure();
  right_150_Distance = ult_1_distance;
}

////////////////////////////////////////////////////

void go_Straight()
{
  digitalWrite (mA2, HIGH);
  digitalWrite (mA1, LOW);

  digitalWrite (mB2, HIGH);
  digitalWrite (mB1, LOW);

}

///////////////////////////////////////////////////

void reverse()
{
  digitalWrite (mA1, HIGH);
  digitalWrite (mA2, LOW);

  digitalWrite (mB1, HIGH);
  digitalWrite (mB2, LOW);
}

///////////////////////////////////////////////////

void turn_Left()
{
  digitalWrite (mA2, HIGH);
  digitalWrite (mA1, LOW);

  digitalWrite (mB2, LOW);
  digitalWrite (mB1, HIGH);
}

//////////////////////////////////////////////////

void turn_Right()
{
  digitalWrite (mA1, HIGH);
  digitalWrite (mA2, LOW);

  digitalWrite (mB1, LOW);
  digitalWrite (mB2, HIGH);
}

//////////////////////////////////////////////////

void stop_Movement()
{
  digitalWrite (mA1, LOW);
  digitalWrite (mA2, LOW);

  digitalWrite (mB1, LOW);
  digitalWrite (mB2, LOW);
}

//////////////////////////////////////////////////

void look_Around()
{
  look_Straight();
  look_Left();
  look_Right();
  look_Straight();
}

////////////////////////////////////////////////////

void buzz_Fast()
{
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
  delay(40);
}

////////////////////////////////////////////////////
void buzz_Slow()
{

}
