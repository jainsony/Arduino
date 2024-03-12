#include <Servo.h>
#define datalen 4
#define threshold 5


int PWM1 = 9;
int DIR1 = 8;

int PWM2 = 6;
int DIR2 = 7;

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
  Serial.begin(115200); // initialize serial communication
  pinMode(PWM1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(DIR2, OUTPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(reac, OUTPUT);
  pinMode(igni, OUTPUT);
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
  if(dataArray[0] > threshold)
  {
    a_speed = dataArray[0];
    analogWrite(PWM1, a_speed);
    digitalWrite(DIR1, LOW);
    analogWrite(PWM2, a_speed);
    digitalWrite(DIR2, LOW);
  }
  else if(dataArray[0] < -threshold)
  {
    a_speed = -1*dataArray[0];
    analogWrite(PWM1, a_speed);
    digitalWrite(DIR1, HIGH);
    analogWrite(PWM2, a_speed);
    digitalWrite(DIR2, HIGH);
  }
  else if(dataArray[1] > threshold)
  {
    a_speed = dataArray[1];
    analogWrite(PWM1, a_speed);
    digitalWrite(DIR1, LOW);
    analogWrite(PWM2, a_speed);
    digitalWrite(DIR2, HIGH);

  }
  else if(dataArray[1] < -threshold)
  {
    a_speed = -1*dataArray[1];
    analogWrite(PWM1, a_speed);
    digitalWrite(DIR1, HIGH);
    analogWrite(PWM2, a_speed);
    digitalWrite(DIR2, LOW);
    
  }
  else
  {
    analogWrite(PWM1, LOW);
    analogWrite(PWM2, LOW);
    analogWrite(DIR1, LOW);
    analogWrite(DIR2, LOW);
    dataArray[0]=0;
    dataArray[1]=0;
    // dataArray[2]
    // dataArray[3]
  }

}

