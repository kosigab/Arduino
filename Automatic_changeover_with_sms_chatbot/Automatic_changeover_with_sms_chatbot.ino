//Arduino Pin 7 -----> Sim800l RX
//Arduino Pin 8 ------> sim800l TX
#include <gprs.h>
#include <SoftwareSerial.h>

#include <virtuabotixRTC.h>

#define TIMEOUT    5000
#define gen_stopper 15
#define gen_starter 14
#define gen_status 13
#define relay 12


virtuabotixRTC myRTC(5, 4, 6);
String previousSMS = "";
double globalTime = 0;
int tempMin = 0;
double start_alarmTime = -1;
double stop_alarmTime = -1;

//Variable to hold last line of serial output from SIM800
char currentLine[50] = "";
int currentLineIndex = 0;

//Boolean to be set to true if message notificaion was found and next
//line of serial output is the actual SMS message content
bool nextLineIsMessage = false;

//Wiring SCLK -> 6, I/O -> 7, CE -> 8
//Or CLK -> 6 , DAT -> 7, Reset -> 8

bool cout = false;
bool cin = false;

char phone_num = "+2347011150239";
GPRS gprs;

//----------------------------------------------------------------------//
//----------------------------new method--------------------------------//


void setup()
{
  myRTC.setDS1302Time(0, 35, 20, 4, 19, 9, 2018); // seconds, minutes, hours, day of the week, day of the month, month, year
  pinMode(gen_stopper, OUTPUT);
  pinMode(gen_starter, OUTPUT);
  pinMode(gen_status, INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Starting SIM800 SMS Command Processor");
  gprs.preInit();
  delay(1000);

  while (0 != gprs.init())
  {
    delay(1000);
    Serial.print("init error\r\n");
  }

  if (0 != gprs.sendCmdAndWaitForResp("AT+CMGF=1\r\n", "OK", TIMEOUT))
  {
    ERROR("ERROR:CNMI");
    return;
  }

  //Start listening to New SMS Message Indications
  if (0 != gprs.sendCmdAndWaitForResp("AT+CNMI=1,2,0,0,0\r\n", "OK", TIMEOUT))
  {
    ERROR("ERROR:CNMI");
    return;
  }

  Serial.println("Init success");
}



//----------------------------------------------------------------------//
//----------------------------new method--------------------------------//

void loop()
{
  sms_Handler();
  myRTC.updateTime();
  if (myRTC.minutes > tempMin)
  {
    Serial.print("Temp Min = ");
    Serial.println(tempMin);
    globalTime++;
    if (start_alarmTime == globalTime)
    {
      start_gen();
    }
    if (stop_alarmTime == globalTime)
    {
      stop_gen();
    }
  }

  tempMin = myRTC.minutes;
  

}
//----------------------------------------------------------------------//
//----------------------------new method--------------------------------//

void sms_Handler()
{

  String receivedSMS = sms_Receiver();
  int minutes = 0;
  int numericSMS = 0;
  if (receivedSMS.length() > 0 && receivedSMS.startsWith("+CMT"))
  {
    receivedSMS = "";
  }
  if (receivedSMS.length() > 0)
  {
    Serial.print("\nSMS handler reads: " + receivedSMS + "\n");
    Serial.print("\nPrevious SMS received: " + previousSMS + "\n");
    numericSMS = receivedSMS.toInt();
    Serial.print("\nNumeric SMS = ");
    Serial.println(numericSMS);
  }
  if (receivedSMS == "TURN ON THE GEN")
  {
    //gprs.sendSMS(phone_num, "Starting the generator...");
    Serial.println("Starting the generator");
    delay(10000);
    start_gen();
  }

  if (receivedSMS == "TURN OFF THE GEN")
  {
    //gprs.sendSMS(phone_num, "Okay. Will turn off the generator shortly...");
    delay(10000);
    stop_gen();
  }
  if ((previousSMS == "SCHEDULE GEN START") && (numericSMS < 1) && cout == true && receivedSMS.length() > 0)
  {
    Serial.println("Please send only digits equivalent to how many minutes you want.");
    //gprs.sendSMS(phone_num, "Please send only digits equivalent to how many minutes you want.");
    cout = false;
  }
  if ((previousSMS == "SCHEDULE GEN START") && (numericSMS > 1440) && cout == true && receivedSMS.length() > 0)
  {
    Serial.println("Maximum of 1440 minutes -> 24hrs");
    //gprs.sendSMS(phone_num, "Maximum of 1440 minutes -> 24hrs");

    cout = false;
  }
  if (previousSMS == "SCHEDULE GEN START" && numericSMS > 1 && numericSMS < 1440 && cout == true && receivedSMS.length() > 0)
  {
    gen_start_scheduler(numericSMS);
    cout = false;
  }

  if (previousSMS == "SCHEDULE GEN START" && receivedSMS == "CANCEL" && cout == true && receivedSMS.length() > 0)
  {
    Serial.println("Start scheduling terminated!");
    cout = false;
  }

  //-----------------------------------------------------------------------------------------------------------------




  if ((previousSMS == "SCHEDULE GEN STOP") && (numericSMS < 1) && cin == true && receivedSMS.length() > 0)
  {
    Serial.println("Please send only digits equivalent to how many minutes you want.");
    //gprs.sendSMS(phone_num, "Please send only digits equivalent to how many minutes you want.");
    cin = false;
  }
  if ((previousSMS == "SCHEDULE GEN STOP") && (numericSMS > 1440) && cin == true && receivedSMS.length() > 0)
  {
    Serial.println("Maximum of 1440 minutes -> 24hrs");
    //gprs.sendSMS(phone_num, "Maximum of 1440 minutes -> 24hrs");
    cin = false;
  }
  if (previousSMS == "SCHEDULE GEN STOP" && numericSMS > 1 && numericSMS < 1440 && cin == true && receivedSMS.length() > 0)
  {
    gen_stop_scheduler(numericSMS);
    cin = false;
  }

  if (previousSMS == "SCHEDULE GEN STOP" && receivedSMS == "CANCEL" && cin == true && receivedSMS.length() > 0)
  {
    Serial.println("Stop-scheduling terminated!");
    cin = false;
  }

  //---------------------------------------------------------------------------------------------------------------
  if (receivedSMS == "SCHEDULE GEN START")
  {
    //gprs.sendSMS(phone_num, "How many minutes from now would you like the generator turned ON?");
    Serial.println("How many minutes from now do you want the generator turned on?");
    cout = true;
  }
  if (receivedSMS == "SCHEDULE GEN STOP")
  {
    //gprs.sendSMS(phone_num, "How many minutes from now would you like the generator turned OFF?");
    Serial.println("How many minutes from now do you want the generator turned off?");
    cin = true;


  }
  if (receivedSMS.length() > 0)
  {
    previousSMS = receivedSMS;

  }

}

//----------------------------------------------------------------------//
//----------------------------new method--------------------------------//

void gen_start_scheduler(int minutes)
{
  Serial.println("/sudo/cmd/c:/gen_start_scheduler.tor -> Launched successfully!");
  Serial.print("Minutes to gen start: ");
  Serial.println(minutes);
  start_alarmTime = globalTime + minutes;
}

//----------------------------------------------------------------------//
//----------------------------new method--------------------------------//

void gen_stop_scheduler(int minutes)
{
  Serial.println("/sudo/cmd/c:/gen_stop_scheduler.tor -> Launched successfully!");
  Serial.print("Minutes to gen stop: ");
  Serial.println(minutes);
  stop_alarmTime = globalTime + minutes;
}
//----------------------------------------------------------------------//
//----------------------------new method--------------------------------//



void start_gen()
{
  bool quitStart = false;
  bool gen_statu_s = check_gen_status();
  if (gen_statu_s == true)
  {
    Serial.println("Hmm... the generator appears to be on already");
    //gprs.sendSMS(phone_num, "Hmm... the generator appears to be on already");
  }
  if (gen_statu_s == false)
  {
    int tries = 0;
    do
    {
      digitalWrite(gen_starter, HIGH);
      delay (1500);
      digitalWrite(gen_starter, LOW);
      delay (1500);
      gen_statu_s = check_gen_status();
      if (gen_statu_s == true || tries > 4)
      {
        quitStart = true;
      }
      tries++;

    }
    while (quitStart == false);
    tries = 0;
    gen_statu_s = check_gen_status();

    if (gen_statu_s == false)
    {
      Serial.println("Generator failed to start after 5 tries.");
      //gprs.sendSMS(phone_num, "There was an error starting the generator!");
    }
    else
    {
      Serial.println("Start success!");
    }
  }

}
//----------------------------------------------------------------------//
//----------------------------new method--------------------------------//

void stop_gen()
{
  bool quitStop = false;
  bool gen_statu_s = check_gen_status();
  if (gen_statu_s == false)
  {
    //gprs.sendSMS(phone_num, "I think the generator is off already");
  }
  if (gen_statu_s == true)
  {
    int tries = 0;
    do
    {
      digitalWrite(gen_stopper, HIGH);
      delay (1500);
      digitalWrite(gen_stopper, LOW);
      delay (1500);
      gen_statu_s = check_gen_status();
      if (gen_statu_s == false || tries > 4)
      {
        quitStop = true;
      }
      tries++;
    }
    while (quitStop == true);
    if (gen_statu_s == true)
    {
      Serial.println("Generator failed to stop after 5 tries.");
      //gprs.sendSMS(phone_num, "There was an error stopping the generator!");

    }
    else
    {
      Serial.println ("The generator was turned off successfully!");
    }
  }
}
//----------------------------------------------------------------------//
//----------------------------new method--------------------------------//

bool check_gen_status()
{
  bool statu_s =  digitalRead(gen_status);

  return (statu_s);
}

String sms_Receiver()
{
  String lastLine = "";
  if (gprs.serialSIM800.available())
  {
    char lastCharRead = gprs.serialSIM800.read();
    //Read each character from serial output until \r or \n is reached (which denotes end of line)
    if (lastCharRead == '\r' || lastCharRead == '\n')
    {
      lastLine = String(currentLine);

      //If last line read +CMT, New SMS Message Indications was received.
      //Hence, next line is the message content.

      //------------============================------------


      if (lastLine.startsWith("+CMT:"))
      {
        phone_num = "";
        for (int i = 7; i < 20; i++)
        {
          phone_num = phone_num + lastLine[i];
        }
      }

      //------------============================------------


      if (lastLine.startsWith("+CMT:"))
      {
        // Serial.println ("Phone number extracted: " + phone_num);

        Serial.println(lastLine);
        nextLineIsMessage = true;
      }
      else if (lastLine.length() > 0)
      {
        if (nextLineIsMessage)
        {
          Serial.println(lastLine);

          nextLineIsMessage = false;
        }
      }
      //Clear char array for next line of read
      for ( int i = 0; i < sizeof(currentLine);  ++i )
      {
        currentLine[i] = (char)0;
      }
      currentLineIndex = 0;
    }
    else
    {
      currentLine[currentLineIndex++] = lastCharRead;
    }
  }
  return (lastLine);
}
//----------------------------------------------------------------------//
