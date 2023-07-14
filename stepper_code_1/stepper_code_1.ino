const int stepPin1 = 5; 
const int dirPin1 = 2; 
const int enPin1 = 8;

// const int stepPin2 = 5; 
// const int dirPin2 = 2; 
// const int enPin2 = 8;

int speed = 0;

int stepper_1_angle = 0;
int stepper_2_angle = 0;
int stepper_3_angle = 0;



void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);

  digitalWrite(enPin,LOW);
}

void loop() {

  mapped_angle_1 = map(parsed_val_1, 0, 180, 0, 1600); //    map(val, 0, 1023, 0, 180); 
  mapped_angle_2 = map(parsed_val_2, 0, 180, 0, 1600); //    map(val, 0, 1023, 0, 180); 
  mapped_angle_3 = map(parsed_val_3, 0, 180, 0, 1600); //    map(val, 0, 1023, 0, 180); 

  printData();
  control();
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
  if((mapped_angle_1 != 0)
  {
    digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction

    for(int x = 0; x < mapped_angle_1; x++) { // 800 for 90 deg // 3200 for 360 deg
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(50); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(50); 
    }
    delay(1000); // One second delay

    digitalWrite(dirPin,LOW); //Changes the direction of rotation

    for(int x = 0; x < mapped_angle_1; x++) {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(50);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(50);
    }
    delay(1000); 
  }

  if((mapped_angle_2 != 0)
  {
    digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction

    for(int x = 0; x < mapped_angle_2; x++) { // 800 for 90 deg // 3200 for 360 deg
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(50); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(50); 
    }
    delay(1000); // One second delay

    digitalWrite(dirPin,LOW); //Changes the direction of rotation

    for(int x = 0; x < mapped_angle_2; x++) {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(50);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(50);
    }
    delay(1000); 
  }

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