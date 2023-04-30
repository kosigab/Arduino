
#include <LiquidCrystal.h>

LiquidCrystal lcd(11, 12, 5, 4, 3, 2);
int a = 0;
int b = 0;
int c = 0;
// include the GSM library
#include <GSM.h>

// PIN Number for the SIM
#define PINNUMBER ""

// initialize the library instances
GSM gsmAccess;
GSM_SMS sms;

// Array to hold the number a SMS is retreived from
char senderNumber[20];

void setup()
{
  
  lcd.begin(16, 2) ;
  lcd.clear();
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println("SMS Messages Receiver");
  lcd.print("SMS Messages Receiver");
  delay (2000);
  lcd.clear();

  // connection state
  boolean notConnected = true;

  // Start GSM connection
  while (notConnected)
  {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      lcd.print("Not connected");
      delay(2000);
      lcd.clear();
    }
  }

  Serial.println("GSM initialized");
  lcd.print("GSM initialized");
  lcd.setCursor(0, 1);
  Serial.println("Waiting for messages");
  lcd.print("Waiting for messages");
  delay (1500);
 

}
void loop()
{
  char c;

  // If there are any SMSs available()
  if (sms.available())
  {
    lcd.clear();
    Serial.println("Message received from:");
    lcd.print("Message received from:");

    // Get remote number
    sms.remoteNumber(senderNumber, 20);
    Serial.println(senderNumber);
    lcd.clear();
    lcd.print(senderNumber);

    // An example of message disposal
    // Any messages starting with # should be discarded
    if (sms.peek() == '#')
    {
      Serial.println("Discarded SMS");
      lcd.clear();
      lcd.print("Access granted!");
      delay (2000);
      lcd.clear();
      lcd.print("Discarded SMS");
      sms.flush();
    }

    // Read message bytes and print them
    while (c = sms.read())
      Serial.print(c);
    lcd.clear();
    lcd.print(c);
    delay (4000);
    //      lcd.clear();
    Serial.println("\nEND OF MESSAGE");
    lcd.setCursor(0, 1);
    lcd.print("END OF MESSAGE");
    delay (1500);
    lcd.clear();

    // Delete message from modem memory
    sms.flush();
    Serial.println("MESSAGE DELETED");
    lcd.print("MESSAGE DELETED!");
    delay (1500);
    lcd.clear();
  }


  delay(1000);

}


