
int heart_rate= 0;
double timer1 = 0;
double timer2 = 0;
int state  = 0;


//  Variables
int PulseSensorPurplePin = 14;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.


// The SetUp Function:
void setup() {
  pinMode(LED13,OUTPUT); 
 //  pinMode(14,INPUT); 
  // pin that will blink to your heartbeat!
   Serial.begin(9600);         // Set's up Serial Communication at certain speed.

}

// The Main Loop Function
void loop() {

  Signal = analogRead(14);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.

   Serial.println(Signal);                    // Send the Signal value to Serial Plotter.

if ((Signal > Threshold)&(state == 0))
{
   timer1 = millis();
   delay(74);
  
}
 
if ((Signal > Threshold) & (state == 1))
{
   timer2 = millis();
   timer2 = timer2 + 74;
   state =0;
   heart_rate = timer2 - timer1;
}
 
  state = 1;

   if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED13,HIGH);
   } else {
     digitalWrite(LED13,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }


//delay(10);


}
