#include <Servo.h>
#define datalen 5

Servo myservo;
Servo myservo1;
Servo myservo2;

int Aone = A0;
int Atwo = A1;
int Bone = A2;
int Btwo = A3;
int enbA = A4;
int enbB = A4;

const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin = 13;    // the number of the LED pin
int reac = 6;
int igni = 7;

int move = 255;

String dataString = ""; // variable to hold input data
int dataArray[datalen]; // array to hold parsed integers
int dataIndex = 0; // index for dataArray

void setup() {
  Serial.begin(9600); // initialize serial communication
  pinMode(Aone, OUTPUT);
  pinMode(Atwo, OUTPUT);
  pinMode(Bone, OUTPUT);
  pinMode(Btwo, OUTPUT);
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(reac, OUTPUT);
  pinMode(igni, OUTPUT);
  myservo.attach(9);
  myservo1.attach(10);
  myservo2.attach(11);
  pinMode(buttonPin, INPUT);
  myservo.write(10); 
  myservo1.write(90); 
  myservo2.write(90); 
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
      printData();  // call function to print parsed data
    } else { // data character
      dataString += incomingChar; // add to input data
    }
  }

//   digitalWrite(Aone, HIGH);
//   digitalWrite(Atwo, LOW);

// for(int i=0; i<255; i++)
// {
//   analogWrite(enbA, i);
//   delay(30);
// }
    
// for(int i=255; i>0; i--)
// {
//   analogWrite(enbA, i);
//   delay(30);
// }
  
//   delay(500);
  
  // digitalWrite(Aone, HIGH);
  
  // printData();
}

void parseData() {
  int commaIndex = 0; // index for locating commas in input string
  while (dataIndex < datalen) { // parse up to 4 integers
    commaIndex = dataString.indexOf(","); // find next comma in input string
    if (commaIndex == -1) { // exit loop if no more commas found
      commaIndex = dataString.length();
    }
    dataArray[dataIndex] = dataString.substring(0, commaIndex).toInt(); // convert substring to integer and store in array
    dataString = dataString.substring(commaIndex + 1); // remove parsed substring and comma from input string
    dataIndex++; // move to next index in array
  }
}


void shoot()
{
  myservo.write(10);
  delay(100);
  digitalWrite(reac, HIGH);
  delay(4500);
  digitalWrite(reac, LOW);
  delay(100);
  myservo.write(90);
  delay(400);
  digitalWrite(igni, HIGH);
  delay(200);
  digitalWrite(igni, LOW);
}


void printData() {
  Serial.print("Parsed data: ");
  for (int i = 0; i < datalen; i++) {
    Serial.print(dataArray[i]);
    Serial.print(" ");
  }
  Serial.println();

  myservo1.write(dataArray[3]); 
  myservo2.write(dataArray[2]);

  if(dataArray[4] > 0)
  {
    dataArray[4] = 0;
    shoot();
  }

  if(dataArray[0] > 0)
  {
    // analogWrite(enbA, dataArray[0]);
    analogWrite(Aone, move);
    analogWrite(Bone, move);
  }
  else if(dataArray[0] < 0)
  {
    analogWrite(Atwo, move);
    analogWrite(Btwo, move);
  }
  else if(dataArray[1] > 0)
  {
    analogWrite(Aone, move);
    analogWrite(Btwo, move);
  }
  else if(dataArray[1] < 0)
  {
    analogWrite(Atwo, move);
    analogWrite(Bone, move);
  }
  else
  {
    analogWrite(Aone, LOW);
    analogWrite(Bone, LOW);
    analogWrite(Atwo, LOW);
    analogWrite(Btwo, LOW);
  }
}

