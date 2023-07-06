#include <Servo.h>
#define datalen 4
#define threshold 0

int a = 0;
int b = 0;
int c = 0;
int d = 0; 

int IN1 = A3;
int IN2 = A4;
int IN3 = A1;
int IN4 = A2;

int PWM1 = 9;
int DIR1 = 8;

int PWM2 = 6;
int DIR2 = 7;

const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin = 13;    // the number of the LED pin
int reac = 6;
int igni = 7;
int i = 0;
int move = 50;
int a_speed = move;
int b_speed = 0;


String dataString = ""; // variable to hold input data
int dataArray[datalen]; // array to hold parsed integers
int dataIndex = 0; // index for dataArray

void setup() {
  Serial.begin(115200); // initialize serial communication

  pinMode(IN1, INPUT);
  pinMode(IN2, INPUT);
  pinMode(IN3, INPUT);
  pinMode(IN4, INPUT);

  pinMode(PWM1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(DIR2, OUTPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(reac, OUTPUT);
  pinMode(igni, OUTPUT);

  // attachInterrupt(digitalPinToInterrupt(IN1), control, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(IN2), control, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(IN3), control, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(IN4), control, CHANGE);
  
}

void loop() {
//   if (Serial.available()) { // check if there is incoming data
//     char incomingChar = Serial.read(); // read incoming character
//     // Serial.print(incomingChar);
//     if (incomingChar == '<') { // start of data
//       dataString = ""; // clear input data
//       dataIndex = 0; // reset index for dataArray
//     } else if (incomingChar == '>') { // end of data
//       parseData(); // call function to parse input data
//       // printData();  // call function to print parsed data
//       control();
//     } else { // data character
//       dataString += incomingChar; // add to input data
//     }
//   }

a = digitalRead(IN1);
b = digitalRead(IN2);
c = digitalRead(IN3);
d = digitalRead(IN4);

Serial.print("IN1 = ");
Serial.print(a);

Serial.print(", IN2 = ");
Serial.print(b);

Serial.print(", IN3 = ");
Serial.print(c);

Serial.print(", IN4 = ");
Serial.println(d);

control();

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

  if(a > threshold)
  {
    // a = analogRead(IN1);
    // a_speed = a;
    // analogWrite(PWM1, a_speed); //left motor fwd
    // digitalWrite(DIR1, LOW);

    analogWrite(PWM2, a_speed); //right motor fwd
    digitalWrite(DIR2, LOW);
  }
  else if(b > threshold)
  {
    // b = analogRead(IN2);
    // a_speed = b;
    // analogWrite(PWM1, a_speed);
    // digitalWrite(DIR1, HIGH);Serial.print("IN1 = ");
    Serial.println("value written");
    analogWrite(PWM2, a_speed); //right motor bck
    digitalWrite(DIR2, HIGH);
  }
  else if(c > threshold)
  {
    // c = analogRead(IN3);
    // a_speed = c;
    analogWrite(PWM1, a_speed); //left motor fwd
    digitalWrite(DIR1, LOW);

  }
  else if(d > threshold)
  {
    // d = analogRead(IN4);
    // a_speed = d;
    analogWrite(PWM1, a_speed); //left motor bck
    digitalWrite(DIR1, HIGH);
    // analogWrite(PWM2, a_speed);
    // digitalWrite(DIR2, LOW);
    
  }
  else
  {
    analogWrite(PWM1, LOW);
    analogWrite(PWM2, LOW);
    analogWrite(DIR1, LOW);
    analogWrite(DIR2, LOW);
  }

}

