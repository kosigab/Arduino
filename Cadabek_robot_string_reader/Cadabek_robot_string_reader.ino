
String complete_command[] = "";
String command = "";
String words = "";
String wor_d = "";
int command_position = 0;
int val = 0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()||val!=10)
  {

    //  do {
    val = Serial.read();

    if (val == 32)words = words + " ";
    if (val == 97)words = words + "a";
    if (val == 98)words = words + "b";
    if (val == 99)words = words + "c";
    if (val == 100)words = words + "d";
    if (val == 101)words = words + "e";
    if (val == 102)words = words + "f";
    if (val == 103)words = words + "g";
    if (val == 104)words = words + "h";
    if (val == 105)words = words + "i";
    if (val == 106)words = words + "j";
    if (val == 107)words = words + "k";
    if (val == 108)words = words + "l";
    if (val == 109)words = words + "m";
    if (val == 110)words = words + "n";
    if (val == 111)words = words + "o";
    if (val == 112)words = words + "p";
    if (val == 113)words = words + "q";
    if (val == 114)words = words + "r";
    if (val == 115)words = words + "s";
    if (val == 116)words = words + "t";
    if (val == 117)words = words + "u";
    if (val == 118)words = words + "v";
    if (val == 119)words = words + "w";
    if (val == 120)words = words + "x";
    if (val == 121)words = words + "y";
    if (val == 122)words = words + "z";
    if (val == 10)
    {
//      //words = words + " Done";
//      Serial.println(words);
//      val = 0;

    }
    // if (val == 44)words = words + ",";
    // if (!Serial.available())words = "";

    //} while (val != 44);


  }
  while (Serial.available())
  {
    val = Serial.read();
  }
  if (val == 10)
  {
    Serial.println(words);
    val = 0;

  }
  if (words != 0)
  {
    // Serial.println(words);
    words = "";
  }




}


//  for (int i = 0; i < words.length(); i++)
//  {
//
//    if (words[i] == ",")
//    {
//      complete_command[command_position] = command;
//      command = "";
//      command_position++;
//      Serial.println(words);
//
//    }
//
//    if (words[i] == ".")
//    {
//      complete_command[command_position] = command;
//      command = "";
//      command_position = 0;
//
//      for (int j = 0; j < 10; j++)
//      {
//        Serial.println(complete_command[j]);
//      }
//
//    }
//
//    else
//    {
//      command = command + words[i];
//    }
//
//  }
