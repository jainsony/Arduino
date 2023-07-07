/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

int leg_1_theta_J1_off = 103; // limit 80 degree
int leg_1_theta_J2_off = 115; // limit 65 degree
int leg_1_theta_J3_off = 97;  // limit 

Servo j1;
Servo j2;
Servo j3;

int pos = 0; 

void setup() 
{
  j1.attach(9);  
  j2.attach(10);
  j3.attach(11);

  j1.write(leg_1_theta_J1_off);
  j2.write(leg_1_theta_J2_off);
  j3.write(leg_1_theta_J3_off);
}

void loop() {

  j1.write(leg_1_theta_J1_off);
  j2.write(leg_1_theta_J2_off);
  j3.write(leg_1_theta_J3_off);

}
