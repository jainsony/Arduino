#include <Servo.h>
#include <Math.h>
#include <Ramp.h>

// Debug
#define DEBUG
#ifdef DEBUG
  #define DEBUG_PRINTL(x)  Serial.println(x)
  #define DEBUG_PRINT(x)  Serial.print(x)
#else
  #define DEBUG_PRINTL(x)
  #define DEBUG_PRINT(x)
#endif

// MIDDLE LEFT LEG
//          x
//          ^
//          |
//          |
// y <------o

// Servo pins
#define J1Pin 9
#define J2Pin 10
#define J3Pin 11

#define J190 100
#define J290 80
#define J390 95


// Servos
Servo Joint1;
Servo Joint2;
Servo Joint3;

// Constants
const double J2L = 50.0; // Length of J2 (57 - 2.35)mm
const double J3L = 100.0; // Length of J3 110mm

const double Y_Rest =  90.0;
const double Z_Rest =  30.0;

const double J3_LegAngle = 15.4;

// Joint Variables
// double J1Act = 0.0;
// double J2Act = 0.0;
// double J3Act = 40.0;

// rampDouble J1Tar = 0.0;
// rampDouble J2Tar = 0.0;
// rampDouble J3Tar = 40.0;

// Command Variables
bool started = false;
bool ended = false;
uint8_t commandStep = 0;

// Commands

void setup() {
  // DEBUG
  #ifdef DEBUG
  Serial.begin(9600);
  #endif

  // Servo instances
  // Joint1.attach(J1Pin, 500, 2500);
  // Joint2.attach(J2Pin, 400, 2400);
  // Joint3.attach(J3Pin, 750, 2400);

  Joint1.attach(J1Pin);
  Joint2.attach(J2Pin);
  Joint3.attach(J3Pin);

  // UpdatePosition(0, 50, 30);
  // delay(3000);

  int go_from = -70;
  int go_till = 70;

  // X move
  // CartesianMove(0,0,0);
  // delay(2000);
  // for(int i = go_from; i<=go_till; i++){
  //   CartesianMove(i,0,0);
  //     delay(100);
  // }
  // delay(3000);

  // CartesianMove(0,0,0);
  // delay(1000);
    // Y move

  delay(3000);
  for(int i = go_from; i<=go_till; i++){
    CartesianMove(30,i,0);
      delay(100);
  }
  delay(3000);
  CartesianMove(0,50,0);
    // Z move
  // CartesianMove(0,0,0);
  // delay(3000);
  // for(int i = go_from; i<=go_till; i++){
  //   CartesianMove(0,0,i);
  //     delay(100);
  // }
  // delay(3000);

  // CartesianMove(0,0,10);
  // CartesianMove(10,0,0);

  // UpdatePosition(0, 50, 30);
  // CartesianMove(0,30,0);
  // CartesianMove(0,0,20);
  // CartesianMove(20,0,0);
  // delay(3000);
  // UpdatePosition(0, 50, 30);
  // CartesianMove(0,40,0);
  // CartesianMove(0,0,30);
  // CartesianMove(30,0,0);
  // delay(3000);

}

void loop() {
//cut
}

void CartesianMove(double X, double Y, double Z){
// OFFSET TO REST POSITION
X += 50;
Y += Y_Rest;
Z += Z_Rest;

// CALCULATE INVERSE KINEMATIC SOLUTION
double J1 = atan(X / Y) * (180 / PI);
double H = sqrt((Y * Y) + (X * X));
double L = sqrt((H * H) + (Z * Z));
double J3 = acos(   ((J2L * J2L) + (J3L * J3L) - (L * L))   /   (2 * J2L * J3L)   ) * (180 / PI);
double B = acos(   ((L * L) + (J2L * J2L) - (J3L * J3L))   /   (2 * L * J2L)   ) * (180 / PI);
double A = atan(Z / H) * (180 / PI);  // BECAUSE Z REST IS NEGATIVE, THIS RETURNS A NEGATIVE VALUE
double J2 = (B + A);  // BECAUSE 'A' IS NEGATIVE AT REST WE NEED TO INVERT '-' TO '+'

UpdatePosition(J1, J2, J3);
}

void UpdatePosition(double J1, double J2, double J3){
  // MOVE TO POSITION
  Joint1.write(J190 - J1);
  Joint2.write(J290 - J2);
  Joint3.write(J3 - J390);

  DEBUG_PRINT("J1: "); DEBUG_PRINTL(J1);
  DEBUG_PRINT("J2: "); DEBUG_PRINTL(J2);
  DEBUG_PRINT("J3: "); DEBUG_PRINTL(J3);
}















