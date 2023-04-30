/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 16. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 5017
  by Scott Fitzgerald
 */


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 16 as an output.
  pinMode(5, OUTPUT);
   pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(5, HIGH);
    // turn the LED on (HIGH is the voltage level)
  delay(600);   
  digitalWrite(6, HIGH);
   digitalWrite(5, LOW);// turn the LED on (HIGH is the voltage level)
  delay(600);  
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);// turn the LED on (HIGH is the voltage level)
  delay(600); 
  digitalWrite(7, LOW); 
}
