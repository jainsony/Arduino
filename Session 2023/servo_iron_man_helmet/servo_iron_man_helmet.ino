// C++ code
//
/*
  Sweep

  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

int pos1 = 35;
int pos2 = 120;
int counter = -1;

Servo servo1;
Servo servo2;

const int buttonPin = 6;
int buttonState = 0;

void setup()
{
  Serial.begin(9600);
  
  servo1.attach(2);
  servo2.attach(4);
  
  servo1.write(90);
  servo2.write(90);
  
  pinMode(buttonPin, INPUT);
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  
    if (counter%2 == 0 and counter > -1) 
    {
      
    	servo1.write(pos1);
      	servo2.write(pos2);
      	delay(100);
        Serial.println("down = ");
        Serial.print(pos1);
        Serial.print(", ");
        Serial.println(pos2);
  	} 
  	else if(counter%2 != 0 and counter > -1)
    {
    	servo1.write(pos2);
      	servo2.write(pos1);
      	delay(100);
        Serial.println("up = ");
        Serial.print(pos1);
        Serial.print(", ");
        Serial.println(pos2);
  	}
  
    if (buttonState == HIGH) 
    {
    	counter = counter + 1;
      delay(500);
  	} 
}