


// include the library code:<br>#include
//Declare Serial Read variables
int CmdCount = 1;
byte inData;
char inChar;
String BuildINString = "";
String DisplayString = "";
long DisplayValue;
String SentMessage = "";
int ByteCount = 0;
long A;
int B;
int WorkingVal;
String WorkingString = "";
//Declare Buttons
int MenuID = 0;

// initialize the library with the numbers of the interface pins

#include <Wire.h>

#include <Adafruit_SSD1306.h>


Adafruit_SSD\1306 display(128,32, &Wire,4);



void setup ()

{
  

 display.setCursor(0, 0);
  Bootup();//Simulate Bootup process doesnt have to be here this only makes it look cool
Retry:
 display.setCursor(0, 0);
  display.println("Connecting......    ");
  display.display();
  display.setCursor(0, 1);
 
  display.println("                    ");
  Serial.begin(38400);

  delay(500);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C,0,0);
                
  // set up the LCD's number of columns and rows:
display.setCursor(0,0);

display.clearDisplay(); // cancellare il display

  display.setTextSize(2); //imposta la dimensione del carattere

  display.setTextColor(WHITE);  //Imposta il colore del testo (Solo bianco)
  // Print a message to the LCD.
  
  
 

  //Send a test message to see if the ELM327 Chip is responding
  SentMessage = "ATI";
  Serial.println("ATI");delay(1000);ReadData();
  if (BuildINString.substring(1,0)=="ELM327")
  {
    display.setCursor(0, 0);
    display.println("Welcome..     ");
   display.display();
    display.setCursor(0, 1);
    display.println("Connection OK ");
   
    display.display();  //Invia il buffer da visualizzare al display
 delay(1500);
  }
  
  else
  {
    display.setCursor(0, 0);
    display.println("Error           ");
    display.setCursor(0, 1);
    display.println("No Connection!  ");
    delay(1500);
    

  }

  delay(1500);
}
void loop() {
  int x;
  x = analogRead (0);
  //Serial.println(x);
  display.setCursor(1, 1);
  if (x > 800 and x < 820) {
    display.println ("Select  ");
  }
  if (x > 620 and x < 630) {
    if (MenuID > 0) {
      MenuID--; //Left
    } delay(250);
  }
  if (x > 400 and x < 415) {
    display.println ("Down    ");
  }
  if (x > 190 and x < 215) {
    display.println ("Up      ");
  }
  if (x > -10 and x < 10) {
    if (MenuID < 11) {
      MenuID++; //Right
    } delay(250);
  }
  if (MenuID == 0) {
    display.setCursor(0, 0);
    display.println("01 Coolant Temp    ");
    display.setCursor(0, 1);
    display.println(DisplayString);
    SentMessage = "01 05";
    Serial.println("01 05");
    delay(300);
    ReadData();
  }
  if (MenuID == 1) {
    display.setCursor(0, 0);
    display.println("02 IAT Temp        ");
    display.setCursor(0, 1);
    display.println(DisplayString);
    SentMessage = "01 0F";
    Serial.println("01 0F");
    delay(300);
    ReadData();
  }
  if (MenuID == 2) {
    display.setCursor(0, 0);
    display.println("03 Ambient Temp    ");
    display.setCursor(0, 1);
    display.println(DisplayString);
    SentMessage = "01 46";
    Serial.println("01 46");
    delay(300);
    ReadData();
  }
  if (MenuID == 3) {
    display.setCursor(0, 0);
    display.println("04 Throttle %      ");
    display.setCursor(0, 1);
    display.println(DisplayString);
    SentMessage = "01 11";
    Serial.println("01 11");
    delay(300);
    ReadData();
  }
  if (MenuID == 4) {
    display.setCursor(0, 0);
    display.print("05 CAT 1 Temp      ");
    display.setCursor(0, 1);
    display.println("Not Implemented ");
  }
  if (MenuID == 5) {
    display.setCursor(0, 0);
    display.println("06 CAT 2 Temp      ");
    display.setCursor(0, 1);
    display.println("Not Implemented ");
  }
  if (MenuID == 6) {
    display.setCursor(0, 0);
    display.println("07 CAT 3 Temp      ");
    display.setCursor(0, 1);
    display.println("Not Implemented ");
  }
  if (MenuID == 7) {
    display.setCursor(0, 0);
    display.println("08 CAT 4 Temp      ");
    display.setCursor(0, 1);
    display.println("Not Implemented ");
  }
  if (MenuID == 8) {
    display.setCursor(0, 0);
    display.println("09 RPM             ");
    display.setCursor(0, 1);
    display.println(DisplayString);
    SentMessage = "01 0C";
    Serial.println("01 0C");
    delay(300);
    ReadData();
  }
  if (MenuID == 9) {
    display.setCursor(0, 0);
    display.println("10 Vehicle Speed   ");
    display.setCursor(0, 1);
    display.println(DisplayString);
    SentMessage = "01 0D";
    Serial.println("01 0D");
    delay(300);
    ReadData();
  }
  if (MenuID == 10) {
    display.setCursor(0, 0);
    display.println("11 Air Flow Rate  ");
    display.setCursor(0, 1);
    display.println(DisplayString);
    SentMessage = "01 10";
    Serial.println("01 10");
    delay(300);
    ReadData();
  }
  if (MenuID == 11) {
    display.setCursor(0, 0);
    display.println("12 Barometric     ");
    display.setCursor(0, 1);
    display.println(DisplayString);
    SentMessage = "01 33";
    Serial.println("01 33");
    delay(300);
    ReadData();
  }
}
//Read Data and act accordingly
void ReadData()
{
  BuildINString = "";
  while (Serial.available() > 0)
  {
    inData = 0;
    inChar = 0;
    inData = Serial.read();
    inChar = char(inData);
    BuildINString = BuildINString + inChar;
  }

  //if(BuildINString!=""){Serial.print(BuildINString);}
  BuildINString.replace(SentMessage, "");
  BuildINString.replace(">", "");
  BuildINString.replace("OK", "");
  BuildINString.replace("STOPPED", "");
  BuildINString.replace("SEARCHING", "");
  BuildINString.replace("NO DATA", "");
  BuildINString.replace("?", "");
  BuildINString.replace(",", "");
  //Serial.print(BuildINString);

  //Check which OBD Command was sent and calculate VALUE
  //Calculate RPM I.E Returned bytes wil be 41 0C 1B E0
  if (SentMessage == "01 0C")
  {
    WorkingString = BuildINString.substring(7, 9);
    A = strtol(WorkingString.c_str(), NULL, 0);
    WorkingString = BuildINString.substring(11, 13);
    B = strtol(WorkingString.c_str(), NULL, 0);

    DisplayValue = ((A * 256) + B) / 4;
    DisplayString = String(DisplayValue) + " rpm          ";
    display.setCursor(0, 1);
    display.println(DisplayString);
  }
  //Calculate Vehicle speed I.E Returned bytes wil be 41 0C 1B E0
  if (SentMessage == "01 0D")
  {
    WorkingString = BuildINString.substring(7, 9);
    A = strtol(WorkingString.c_str(), NULL, 0);
    DisplayValue = A;
    DisplayString = String(DisplayValue) + " km/h          ";
    display.setCursor(0, 1);
    display.println(DisplayString);
  }

  //Coolant Temp
  if (SentMessage == "01 05")
  {
    WorkingString = BuildINString.substring(7, 9);
    A = strtol(WorkingString.c_str(), NULL, 0);
    DisplayValue = A;
    DisplayString = String(DisplayValue) + " C            ";
    display.setCursor(0, 1);
    display.print(DisplayString);
  }

  //IAT Temp
  if (SentMessage == "01 0F")
  {
    WorkingString = BuildINString.substring(7, 9);
    A = strtol(WorkingString.c_str(), NULL, 0);
    DisplayValue = A;
    DisplayString = String(DisplayValue) + " C            ";
    display.setCursor(0, 1);
    display.print(DisplayString);
  }

  //Air flow Rate
  if (SentMessage == "01 10")
  {
    WorkingString = BuildINString.substring(7, 9);
    A = strtol(WorkingString.c_str(), NULL, 0);
    WorkingString = BuildINString.substring(11, 13);
    B = strtol(WorkingString.c_str(), NULL, 0);

    DisplayValue = ((A * 256) + B) / 100;
    DisplayString = String(DisplayValue) + " g/s          ";
    display.setCursor(0, 1);
    display.print(DisplayString);
  }

  //Ambient Temp
  if (SentMessage == "01 46")
  {
    WorkingString = BuildINString.substring(7, 9);
    A = strtol(WorkingString.c_str(), NULL, 0);
    DisplayValue = A;
    DisplayString = String(DisplayValue) + " C            ";
    display.setCursor(0, 1);
    display.print(DisplayString);
  }

  //Throttle position
  if (SentMessage == "01 11")
  {
    WorkingString = BuildINString.substring(7, 9);
    A = strtol(WorkingString.c_str(), NULL, 0);
    DisplayValue = A;
    DisplayString = String(DisplayValue) + " %            ";
    display.setCursor(0, 1);
    display.print(DisplayString);
  }
  //Barometric pressure
  if (SentMessage == "01 33")
  {
    WorkingString = BuildINString.substring(7, 9);
    A = strtol(WorkingString.c_str(), NULL, 0);
    DisplayValue = A;
    DisplayString = String(DisplayValue) + " kpa            ";
    display.setCursor(0, 0);
    display.println(DisplayString);
  }
}

void Bootup()
{

display.clearDisplay();
  display.println("WisperChip V2.00 ");
  for (int i = 0; i <= 5; i++)
  
    for (int j = 1; j <= 4; j++) // -/|\-
    {
      if (j == 1) {
        display.setCursor(0, 1);
         display.println ("-");
        delay(200);
      }
      if (j == 2) {
         display.setCursor(0, 1);
         display.println ("/");
        delay(200);
      }
      if (j == 3) {
         display.setCursor(0, 1);
         display.println ("|");
        delay(200);
      }
      if (j == 4) {
         display.setCursor(0, 1);
         display.println ("\\");
        delay(200);
      }
    }
  }
