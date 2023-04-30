
 int button = 5;
 int ind =13;
  int s=0;
void setup() {
  // put your setup code here, to run once:
 
 
  pinMode (button, INPUT);
  pinMode (ind, OUTPUT);


}

void loop() {
  int buttonstate=digitalRead(button);
  if (buttonstate == 0)
  {
   
  digitalWrite (ind, HIGH);
  
    }
   else 
   {
  digitalWrite (ind, LOW);
    
    }
  // put your main code here, to run repeatedly:

}
