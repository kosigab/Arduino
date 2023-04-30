//References
//http://tronixstuff.com/2014/01/08/tutorial-arduino-and-sim900-gsm-modules/

// This sketch is used for SIM800L EVB

// Connect VIO to +5V
// Connect GND to Ground
// Connect RX (data into SIM800L) to Digital 11
// Connect TX (data out from SIM800L) to Digital 10

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX


int flag =1;    //alarm status 1 = active, 0 = Inactive
int counter;    //for character reading (string length)
int count;      //is being used in compareNum()
int countsec;   //is being used in compareNum()
int check;      //should be 10 chars in order to send or not sms
int switchState=0;
//unsigned long hourInterval = 3600000;    // One hour Interval
const int magnetSwitch = 6; //Pin Read
const int led = 9; //Led Pin
unsigned long hourInterval = 300000;    // five minutes
unsigned long previousMillis = 0;        // will store last time 
String inData;  //Will hold the incoming character from the GSM shield
char mynumber[]="6940000000";
char secnumber[]="6940000000";




void setup()  
{
  pinMode(magnetSwitch, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(19200);
  mySerial.print("\r");
  mySerial.begin(19200);
  delay (1000);
  //new start 
  mySerial.print("AT+CLIP=1\r"); // turn on caller ID notification
  delay(1000);
  mySerial.print("AT+CNMI=2,2,0,0,0\r"); //old good working
  delay(1000);
}





void loop() // run over and over
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= hourInterval) {
      previousMillis = currentMillis;  
      flag=1;
  }
  
  while (mySerial.available() > 0)
    { 
        delay(10); //new
        char recieved = mySerial.read();  //old good
        inData += recieved;               //old good

        // Process message when new line character is recieved
        if (recieved == '\n')
        {
            Serial.print("Arduino Received: ");
            Serial.print(inData);
            //mySerial.print("Arduino Received: ");
            //mySerial.print(inData);
             
            counter=0; //counter reset
            for (int i=0; i <30; i++)
            {
              if (inData[i]!='\0')  //Calculates each string comes from mySerial to inData string
                counter++;          //is being used in for loop to calculate the array's length
            }
            Serial.print("Counter = ");
            Serial.println(counter);
            //TEST
            //Serial.print("character="); //traces  
            //Serial.println(inData[10]); //traces for incomming sms. character 10 is the first number of the cellphone
            //TEST
            check=0;
            if (counter > 10)
              check = compareNum();       
            if (inData[0]=='s')   //When receive sms with letter s it prints the current status            
            {
              Serial.print ("Status =");
              Serial.println(flag);     //1=ACTIVE, 2= INACTIVE
              if (flag==1)
                {
                sendAlarmStatus("Alarm Active");
                mySerial.write(0x1A);  //Equivalent to sending Ctrl+Z   
                }
              else
                {
                sendAlarmStatus("Alarm Inactive");
                mySerial.write(0x1A);  //Equivalent to sending Ctrl+Z   
                }
            }            
            inData = ""; // Clear received buffer
        }//if bracket
    }//while loop bracket
    //20160303 new block end

    
    if ((check == 10) && (flag==1))   //check receives the result of the comparison (cellphone number comparison)
    {
      sendAlarmStatus("Alarm Deactivated");
      flag=0; //Alarm Deactivated
      mySerial.println("AT");  //NEW TEST
      delay(200);
    }
//    if ((check == 10) && (flag==0))
//    {
//      sendAlarmStatus("Alarm Activated");
//      flag=1; //Alarm Activated
//      delay(200);
//    }
    


    //Serial block reads Serial input
    if (Serial.available()){
    char c = (char)Serial.read();    //Read characters/commands in the serial monitor input
    if(c == '#')
        mySerial.write((char)26);
    else
        mySerial.write(c);          //will send the commands to mySerial, to Sim800L
    }

//20160303 start 
 if(flag==1)
 {
  switchState = !digitalRead(magnetSwitch); //When switch is closed it reads High(1), but it registers LOW(0) - the opposite -
  if (switchState == HIGH)
  {
    digitalWrite(led, HIGH);
    sendAlarmStatus("---Caution--- The door Is OPEN");
    flag = 0;
  }
  
  else
  {
    digitalWrite(led, LOW);
  }
 }
 else
  digitalWrite(led, LOW);
//20160303 stop

}//loop end bracket





void sendAlarmStatus(char *alm)
{
    mySerial.print("AT+CMGF=1\r");                      // AT command to send SMS message  
    delay(100);
    if (count==10)
      {
      mySerial.println("AT+CMGS=\"+306940000000\"");      // recipient's mobile number, in international format
      delay(200);
      }
    else if (countsec==10)
      {
      mySerial.println("AT+CMGS=\"+306940000000\"");      // recipient's mobile number, in international format
      delay(200);
      }
    else
      {
      mySerial.println("AT+CMGS=\"+306940000000\"");      // recipient's mobile number, in international format
      delay(200);
      }
    mySerial.println(alm);      // message to send
    delay(200);
    mySerial.println((char)26);                       // End AT command with a ^Z, ASCII code 26
    delay(100); 
    mySerial.println("");
    delay(5000);
}




void call()
{
  mySerial.println("ATD+306940000000;");
}

void hang_up()
{
  mySerial.println("ATH");
}

void del_sms_all()
{
  mySerial.println("AT+CMGD=1,4"); // delete all SMS
}

int compareNum(){
  int z=0;      //index
  count=0;   
  countsec=0;   
  for (int j=11;j<21;j++)
  {
    if (mynumber[z]==inData[j]) //cell. number would be compared with the caller's number char by char
    {
     z++;  
     count++;    //If count==10 then diactivates alarm
    }
  }
  z=0;
  for (int j=11;j<21;j++)
  {
    if (secnumber[z]==inData[j]) //cell. number would be compared with the caller's number char by char
    {
     z++;  
     countsec++;    //If countsec==10 then diactivates alarm
    }
  }
  Serial.print("Characters matching = ");
  Serial.print(countsec);
  Serial.print("----------");
  Serial.println(count);    //If check equals to ten, Then the caller is me and will do action           
  if (count==10)
    return(count);
  else
    return (countsec);
}









//Steps to send sms
/*{
    mySerial.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
    delay(1000);
    mySerial.print("AT+CMGS=\"");
    mySerial.print(snFull);
    mySerial.print("\"\r");
    delay(1000);
    mySerial.print("Unknown Command: ");
    mySerial.print(sms);
    mySerial.print("\r");
    delay(1000);
    mySerial.write(0x1A);  //Equivalent to sending Ctrl+Z     
    return;
}*/

