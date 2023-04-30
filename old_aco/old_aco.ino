//Arduino Pin 7 -----> Sim800l RX
//Arduino Pin 8 ------> sim800l TX
#include <gprs.h>
#include <SoftwareSerial.h>
#define TIMEOUT    5000
#define gen_stopper 15
#define gen_starter 14
#define gen_status 13
#define relay 12

String lastLine = "";


//Variable to hold last line of serial output from SIM800
char currentLine[500] = "";
int currentLineIndex = 0;

//Boolean to be set to true if message notificaion was found and next
//line of serial output is the actual SMS message content
bool nextLineIsMessage = false;


const char phone_num = "+2347011150239";
GPRS gprs;
//-----------------new method--------------------------//
void setup()
{
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

}

//----------------------------------------------------------------------//
//----------------------------new method--------------------------------//



String sms_Handler()
{
  int count = 0;
  String previousSMS = "";
  String minutes = "";
  int numericSMS = 0;
  String receivedSMS = sms_Receiver();
  if (receivedSMS.length() > 0 && receivedSMS.startsWith("+CMT"))
  {
    receivedSMS = "";
  }
  if (receivedSMS.length() > 0)
  {
    Serial.print("\nSMS handler reads: " + receivedSMS + "\n");

  }
  numericSMS = receivedSMS.toInt();
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
  if (previousSMS == "SCHEDULE GEN START")
  {

  }
  if (receivedSMS == "SCHEDULE GEN START")
  {


  }
  if (receivedSMS == "SCHEDULE GEN STOP")
  {

  }

  previousSMS = receivedSMS;


  return (minutes);
}

//----------------------------------------------------------------------//
//----------------------------new method--------------------------------//

void gen_start_scheduler()
{

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

  //----------------------------------------------------------------------//
  //----------------------------new method--------------------------------//


}
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


//----------------------------------------------------------------------//
//----------------------------new method--------------------------------//


String sms_Receiver()
{
  if (gprs.serialSIM800.available())
  {
    char lastCharRead = gprs.serialSIM800.read();
    //Read each character from serial output until \r or \n is reached (which denotes end of line)
    if (lastCharRead == '\r' || lastCharRead == '\n')
    {
      lastLine = String(currentLine);

      //If last line read +CMT, New SMS Message Indications was received.
      //Hence, next line is the message content.
      if (lastLine.startsWith("+CMT:"))
      {
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
