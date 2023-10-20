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

int pos1 = 60;
int pos2 = 120;
int counter = -1;
int potpin = A0;
int val;
int a_val;
int debug = 1;


Servo servo1;
Servo servo2;
int factor;

const int buttonPin = 8;
int buttonState = 0;

void setup()
{
  Serial.begin(9600);
  
  servo1.attach(4); // base
  servo2.attach(2); // d
  
  servo1.write(90);
  servo2.write(90);
  
  pinMode(buttonPin, INPUT);
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  if(debug == 0)
  {
    if (counter%2 == 0 and counter > -1) 
  {
    servo1.write(pos1);
      servo2.write(pos2);
      delay(100);
  } 
  else if(counter%2 != 0 and counter > -1)
  {
    servo1.write(pos2);
      servo2.write(pos1);
      delay(100);
  }

  if (buttonState == HIGH) 
  {
    counter = counter + 1;
    delay(500);
  }
  }
  else
  {
    // val = analogRead(potpin);            
    // val = map(val, 0, 1023, 90, 170); 

    // open
    for(int val=92; val<=170; val++)
    {
      if(val > 85 and val < 170)
      {
        servo1.write(val+7); 
        if(val < 135)   
          servo2.write(val);
        else
        {
          factor = val +1-135;
          a_val = 135 - factor;
          Serial.print("factor : ");
          Serial.println(factor);
          Serial.print("ser 2 (applied value) : ");
          Serial.println(a_val);
          if(a_val > 130)
            servo2.write(a_val);
        } 
        Serial.print("val : ");
        Serial.println(val+7);
      }
      else
      {
        Serial.println("value out of range");
      }
      delay(15); 
    } 
    delay(2000);
    // close
    for(int val=170; val>=92; val--)
    {
      if(val > 85 and val < 170)
      {
        servo1.write(val+7); 
        if(val < 135)   
          servo2.write(val);
        else
        {
          factor = val +1-135;
          a_val = 135 - factor;
          Serial.print("factor : ");
          Serial.println(factor);
          Serial.print("ser 2 (applied value) : ");
          Serial.println(a_val);
          if(a_val > 130)
            servo2.write(a_val);
        } 
        Serial.print("val : ");
        Serial.println(val+7);
      }
      else
      {
        Serial.println("value out of range");
      }
      delay(15); 
    }                         
    // delay(15);                         
  }
}