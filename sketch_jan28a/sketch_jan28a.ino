
// 0 pin is your RX-Pin on Arduino UNO,connect with A7 UTXD pin
// 1 pin is your TX-Pin on Arduino UNO,connect with a7 URXD pin
char phone_no[]="+2348082999099"; //

void setup()
{
Serial.begin(9600);  
delay(200);
Serial.println("AT");
delay(1000);
Serial.print("ATD");
Serial.println(phone_no);
//Serial.println(";");
delay(10000);
Serial.println("ATH");
}

void loop()
{


}

