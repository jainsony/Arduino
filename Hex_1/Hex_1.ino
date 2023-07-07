#include <Servo.h>

#define datalen 3

int fix;

int leg_1_theta_J1_off = 103; // limit 77 degree  180 - 103(leg_1_theta_J1_off) = 77
int leg_1_theta_J2_off = 115; // limit 65 degree
int leg_1_theta_J3_off = 97;  // limit 83 degree

int mod_theta_1 = 0;
int mod_theta_2 = 0;
int mod_theta_3 = 0;

Servo j1;
Servo j2;
Servo j3;

String dataString = ""; // variable to hold input data
int dataArray[datalen]; // array to hold parsed integers
int dataIndex = 0; // index for dataArray

void setup() 
{
  Serial.begin(9600); // initialize serial communication
  
  j1.attach(9);  
  j2.attach(10);
  j3.attach(11);

  j1.write(leg_1_theta_J1_off);
  j2.write(leg_1_theta_J2_off);
  j3.write(leg_1_theta_J3_off);

  delay(1000);
}

void loop() {
  go_to_serial(); // -> 
}

void fix_values()
{
  for(int i=0; i<datalen; i++)
  {
    fix = dataArray[i];           
    dataArray[i] = map(fix, -90, 90, -60, 60);
  }
}

void control()
{
  /* 
    For Testing I am ignoring safety measures like:
    1. angle ranges
    2. handling array
    more will be added soon
   */

  mod_theta_1 = leg_1_theta_J1_off + dataArray[0];
  mod_theta_2 = leg_1_theta_J2_off + dataArray[1];
  mod_theta_3 = leg_1_theta_J3_off + dataArray[2];

  j1.write(mod_theta_1);
  j2.write(mod_theta_2);
  j3.write(mod_theta_3);
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

void go_to_serial()
{
    if (Serial.available()) { // check if there is incoming data
    char incomingChar = Serial.read(); // read incoming character
    // Serial.print(incomingChar);
    if (incomingChar == '<') { // start of data
      dataString = ""; // clear input data
      dataIndex = 0; // reset index for dataArray
    } else if (incomingChar == '>') { // end of data
      parseData(); // call function to parse input data
      // printData();  // call function to print parsed data
      fix_values();
      control();
    } else { // data character
      dataString += incomingChar; // add to input data
    }
  }
}

