#define red 2

#define g1 3
#define b1 4

#define g2 5
#define b2 6

#define g3 7
#define b3 8

int ontime = 300;
int offtime = 200;

int cycle = 0;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin b1 as an output.
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(g3, OUTPUT);
  pinMode(red, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(red, HIGH);
  delay(ontime);
  digitalWrite(red, LOW);
  delay(ontime);

  digitalWrite(b1, HIGH);
  delay(ontime);
  digitalWrite(b1, LOW);

  digitalWrite(b2, HIGH);
  delay(ontime);
  digitalWrite(b2, LOW);

  digitalWrite(b3, HIGH);
  delay(ontime);
  digitalWrite(b3, LOW);


  digitalWrite(g1, HIGH);
  delay(ontime);
  digitalWrite(g1, LOW);
  delay(offtime);

  digitalWrite(g2, HIGH);
  delay(ontime);
  digitalWrite(g2, LOW);
  delay(offtime);

  digitalWrite(g3, HIGH);
  delay(ontime);
  digitalWrite(g3, LOW);
  delay(offtime);


  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  digitalWrite(g3, HIGH);
  delay(ontime);
  digitalWrite(g1, LOW);
  digitalWrite(g2, LOW);
  digitalWrite(g3, LOW);
  delay(offtime);

  digitalWrite(b1, HIGH);
  digitalWrite(b2, HIGH);
  digitalWrite(b3, HIGH);
  delay(ontime);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(b3, LOW);
  delay(offtime);
 
  speedup();

}
void speedup()
{
  if ((ontime > 50) && (cycle == 0))
  {
    ontime = ontime - 31;
    offtime = offtime - 31;

    if (ontime < 50)
    {
      cycle = 1;
    }
  }
  if ((ontime < 270) && (cycle == 1))
  {
    ontime = ontime + 31;
    offtime = offtime + 31;
    if (ontime > 270)
    {
      cycle = 0;
    }
  }
}
