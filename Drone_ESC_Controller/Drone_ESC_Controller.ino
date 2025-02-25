// /*
//  Controlling a servo position using a potentiometer (variable resistor)
//  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

//  modified on 8 Nov 2013
//  by Scott Fitzgerald
//  http://www.arduino.cc/en/Tutorial/Knob
// */

// #include <Servo.h>

// Servo myservo;  // create servo object to control a servo

// int potpin = A0;  // analog pin used to connect the potentiometer
// int val;    // variable to read the value from the analog pin

// void setup() {
//   myservo.attach(2, 3000, 5000);  // attaches the servo on pin 9 to the servo object
//   Serial.begin(9600);
//   myservo.write(0); 
//   delay(2000);
// }

// void loop() {
//   val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
//   val = map(val, 550, 1023, 0, 180);     // scale it for use with the servo (value between 0 and 180)
//   Serial.println(val);
//   myservo.write(val);                  // sets the servo position according to the scaled value
//   // delay(15);                           // waits for the servo to get there
// }


#include <Servo.h>

Servo esc;  // Create a Servo object to control the ESC

const int potPin = A0;  // Potentiometer connected to analog pin A0
const int escPin = 9;   // ESC signal wire connected to digital pin 9
int potValue = 0;       // Variable to store potentiometer value
int escValue = 0;       // Variable to store ESC signal value

void setup() {
  esc.attach(escPin);   // Attach ESC to pin 9
  // esc.writeMicroseconds(1000); // Send minimum signal to arm the ESC
  Serial.begin(9600);
  delay(2000);          // Wait for 2 seconds to allow ESC initialization
}

void loop() {
  potValue = analogRead(potPin);  // Read potentiometer value (0-1023)
  
  // Map potentiometer value to ESC signal range (1000-2000 microseconds)
  escValue = map(potValue, 0, 1023, 0, 2000);
  Serial.println(potValue);
  esc.writeMicroseconds(escValue);  // Send mapped value to ESC
  
  delay(20);  // Small delay for stability
}
