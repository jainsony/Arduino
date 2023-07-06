#include <Servo.h>
#define datalen 4
#define threshold 10
// Servo myservo;
// Servo myservo1;
// Servo myservo2;
const int enbA = 3;
const int enbB = 5;

int i1 = 6;
int i2 = 9;
int i3 = 10;
int i4 = 11;

const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin = 13;    // the number of the LED pin
int reac = 6;
int igni = 7;
int i = 0;
int move = 254;
int a_speed = 0;
int b_speed = 0;


String dataString = ""; // variable to hold input data
int dataArray[datalen]; // array to hold parsed integers
int dataIndex = 0; // index for dataArray

void setup() {
  Serial.begin(9600); // initialize serial communication
  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
  pinMode(i3, OUTPUT);
  pinMode(i4, OUTPUT);
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(reac, OUTPUT);
  pinMode(igni, OUTPUT);
  // myservo.attach(9);
  // myservo1.attach(10);
  // myservo2.attach(11);
  // pinMode(buttonPin, INPUT);
  // myservo.write(10); 
  // myservo1.write(90); 
  // myservo2.write(90); 
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
      // printData();  // call function to print parsed data
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

    // myservo1.write(dataArray[3]); 
  // myservo2.write(dataArray[2]);

  // if(dataArray[4] > 0)
  // {
  //   dataArray[4] = 0;
  // }


  if(dataArray[0] > threshold)
  {
    a_speed = dataArray[0];
    b_speed = dataArray[0];
    analogWrite(enbA, a_speed);
    analogWrite(enbB, b_speed);
    analogWrite(i1, a_speed);
    analogWrite(i3, b_speed);
  }
  else if(dataArray[0] < -threshold)
  {
    a_speed = -1*dataArray[0];
    b_speed = -1*dataArray[0];
    analogWrite(enbA, a_speed);
    analogWrite(enbB, b_speed);
    analogWrite(i2, a_speed);
    analogWrite(i4, b_speed);
  }
  else if(dataArray[1] > threshold)
  {
    a_speed = dataArray[1];
    b_speed = dataArray[1];
    analogWrite(enbA, a_speed);
    analogWrite(enbB, b_speed);
    analogWrite(i1, a_speed);
    analogWrite(i4, b_speed);

  }
  else if(dataArray[1] < -threshold)
  {
    a_speed = -1*dataArray[1];
    b_speed = -1*dataArray[1];
    analogWrite(enbA, a_speed);
    analogWrite(enbB, b_speed);
    analogWrite(i2, a_speed);
    analogWrite(i3, b_speed);
    
  }
  else
  {
    analogWrite(enbA, LOW);
    analogWrite(enbB, LOW);
    analogWrite(i1, LOW);
    analogWrite(i3, LOW);
    analogWrite(i2, LOW);
    analogWrite(i4, LOW);
  }

}

