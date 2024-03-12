#include <Servo.h>
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin = 13;    // the number of the LED pin
int reac = 6;
int igni = 7;

Servo myservo;
Servo myservo1;
Servo myservo2;
int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:

  pinMode(ledPin, OUTPUT);
  pinMode(reac, OUTPUT);
  pinMode(igni, OUTPUT);
  myservo.attach(9);
  myservo1.attach(10);
  myservo2.attach(11);
  pinMode(buttonPin, INPUT);
  myservo.write(90); 
  myservo1.write(90); 
  myservo2.write(90); 
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH)
  {
    shoot();
  }
  //  {
  //   // turn LED on:
  //   digitalWrite(ledPin, HIGH);
  // } else {
  //   // turn LED off:
  //   digitalWrite(ledPin, LOW);
  // }
}

void shoot()
{
  myservo.write(10);
  delay(100);
  digitalWrite(reac, HIGH);
  delay(3000);
  digitalWrite(reac, LOW);
  delay(100);
  myservo.write(90);
  delay(400);
  digitalWrite(igni, HIGH);
  delay(200);
  digitalWrite(igni, LOW);
}
