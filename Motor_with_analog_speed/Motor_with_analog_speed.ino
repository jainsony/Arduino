#define datalen 4

int Aone = A0;
int Atwo = A1;
int Bone = A2;
int Btwo = A3;
int enbA = A4;
int enbB = A4;

int move = 255;

String dataString = ""; // variable to hold input data
int dataArray[datalen]; // array to hold parsed integers
int dataIndex = 0; // index for dataArray

void setup() {
  Serial.begin(9600); // initialize serial communication
  pinMode(Aone, OUTPUT);
  pinMode(Atwo, OUTPUT);
  pinMode(Bone, OUTPUT);
  pinMode(Btwo, OUTPUT);
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);
}

void loop() {
  // if (Serial.available()) { // check if there is incoming data
  //   char incomingChar = Serial.read(); // read incoming character
  //   // Serial.print(incomingChar);
  //   if (incomingChar == '<') { // start of data
  //     dataString = ""; // clear input data
  //     dataIndex = 0; // reset index for dataArray
  //   } else if (incomingChar == '>') { // end of data
  //     parseData(); // call function to parse input data
  //     printData();  // call function to print parsed data
  //   } else { // data character
  //     dataString += incomingChar; // add to input data
  //   }
  // }

  digitalWrite(Aone, HIGH);
  digitalWrite(Atwo, LOW);

for(int i=0; i<255; i++)
{
  analogWrite(enbA, i);
  delay(30);
}
    
for(int i=255; i>0; i--)
{
  analogWrite(enbA, i);
  delay(30);
}
  
  delay(500);
  
  // digitalWrite(Aone, HIGH);
  
  // printData();
}

void parseData() {
  int commaIndex = 0; // index for locating commas in input string
  while (dataIndex < datalen) { // parse up to 4 integers
    commaIndex = dataString.indexOf(","); // find next comma in input string
    if (commaIndex == -1) { // exit loop if no more commas found
      commaIndex = dataString.length();
    }
    dataArray[dataIndex] = dataString.substring(0, commaIndex).toInt(); // convert substring to integer and store in array
    dataString = dataString.substring(commaIndex + 1); // remove parsed substring and comma from input string
    dataIndex++; // move to next index in array
  }
}

void printData() {
  Serial.print("Parsed data: ");
  for (int i = 0; i < datalen; i++) {
    Serial.print(dataArray[i]);
    Serial.print(" ");
  }
  Serial.println();
   if(dataArray[0] > 0)
  {
    // analogWrite(enbA, dataArray[0]);
    analogWrite(Aone, move);
    analogWrite(Bone, move);
  }
  else if(dataArray[0] < 0)
  {
    analogWrite(Atwo, move);
    analogWrite(Btwo, move);
  }
  else if(dataArray[1] > 0)
  {
    analogWrite(Aone, move);
    analogWrite(Btwo, move);
  }
  else if(dataArray[1] < 0)
  {
    analogWrite(Atwo, move);
    analogWrite(Bone, move);
  }
  else
  {
    analogWrite(Aone, LOW);
    analogWrite(Bone, LOW);
    analogWrite(Atwo, LOW);
    analogWrite(Btwo, LOW);
  }
  
}

// void set_car_command(){
//   if(dataArray[0] == 1)
//   {
//     analogWrite(Aone, HIGH);
//     analogWrite(Bone, HIGH);
//   }
//   else if(dataArray[1] == 1)
//   {
//     analogWrite(Atwo, HIGH);
//     analogWrite(Btwo, HIGH);
//   }
//   else if(dataArray[2] == 1)
//   {
//     analogWrite(Aone, HIGH);
//     analogWrite(Btwo, HIGH);
//   }
//   else if(dataArray[3] == 1)
//   {
//     analogWrite(Atwo, HIGH);
//     analogWrite(Bone, HIGH);
//   }
//   else
//   {
//     analogWrite(Atwo, LOW);
//     analogWrite(Bone, LOW);
//     analogWrite(Atwo, LOW);
//     analogWrite(Btwo, LOW);
//   }
// }
