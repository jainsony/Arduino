#include <Servo.h>
#define datalen 4

Servo myservo1;
Servo myservo2;
Servo myservo3;

const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin = 13;    // the number of the LED pin
int reac = 6;
int igni = 7;
int i = 0;
int move = 254;

String dataString = ""; // variable to hold input data
int dataArray[datalen]; // array to hold parsed integers
int dataIndex = 0; // index for dataArray

void setup() {
  Serial.begin(115200); // initialize serial communication
  
  pinMode(ledPin, OUTPUT);
  pinMode(reac, OUTPUT);
  pinMode(igni, OUTPUT);
  myservo1.attach(11);
  myservo2.attach(10);
  myservo3.attach(9);

  myservo1.write(90); 
  myservo2.write(90); 
  myservo3.write(90); 
}

void loop() {
  if (Serial.available()) { // check if there is incoming data
    char incomingChar = Serial.read(); // read incoming character
    // Serial.print(incomingChar);
    if (incomingChar == '<') { // start of data
      dataString = ""; // clear input data
      dataIndex = 0; // reset index for dataArray
    } else if (incomingChar == '>') { // end of data
      parseData(); // call function to parse input data
      control();
    } else { // data character
      dataString += incomingChar; // add to input data
    }
  }

//testing
  // parseData(); // call function to parse input data
  // printData();  // call function to print parsed data
}

void parseData() {
  int commaIndex = 0; // index for locating commas in input string
  while (dataIndex < datalen) { // parse up to 4 integers
    commaIndex = dataString.indexOf(","); // find next comma in input string
    if (commaIndex == -1) { 
      commaIndex = dataString.length();
    }
    dataArray[dataIndex] = dataString.substring(0, commaIndex).toInt(); // convert substring to integer and store in array
    dataString = dataString.substring(commaIndex + 1); // remove parsed substring and comma from input string
    dataIndex++; // move to next index in array
  }
}


void printData() {
  Serial.print("Parsed data: ");
  for (i = 0; i < datalen; i++) {
    Serial.print(dataArray[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void control()
{
  myservo1.write(dataArray[0]); // 11 pin  tibia
  myservo2.write(dataArray[1]); // 10 pin  femur
  myservo3.write(dataArray[2]); // 9 pin   coxa

}

