// {0x8C, 0xAA, 0xB5, 0x52, 0xA2, 0xFB}; brodd
// a esp01 : a4:cf:12:ff:a6:d5
// b esp01 : 5c:cf:7f:49:c6:50
// {0xA4, 0xCF, 0x12, 0xBE, 0x6A, 0x7D};  brodd bro

// Send serial data
#include <ESP8266WiFi.h>
#include <espnow.h>

// MAC Address of your salve 
uint8_t broadcastAddress[] = {0x5C, 0xCF, 0x7F, 0x49, 0xC6, 0x50};
uint8_t debug_mode = 0;

#define datalen 4
#define threshold 5

int i = 0;

int a_speed = 0;
int b_speed = 0;

float Speed;
float Direction;

String dataString = ""; // variable to hold input data
int dataArray[datalen]; // array to hold parsed integers
int dataIndex = 0; // index for dataArray

const int buttonPin = D5;
int buttonState = 0;
int counter = 1;
// Define variables to store incoming readings
float FeedBackSpeed;
float FeedBackDirection;


const long interval = 100; 
unsigned long previousMillis = 0;    // 

// Variable to store if sending data was successful
String success;

typedef struct struct_message {
    float speed;
    float dir;
} struct_message;

// Create a struct_message called Data_structure to hold sensor readings
struct_message Data_structure;

// Create a struct_message to hold incoming sensor readings
struct_message incomingData;


void parseData();
void printData();
// Callback when data is sent to slave
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("sent successfully");
  }
  else{
    Serial.println("fail to sent");
  }
}

// Callback when data is received from slave
void OnDataRecv(uint8_t * mac, uint8_t *IncomingData, uint8_t len) {
  memcpy(&incomingData, IncomingData, sizeof(incomingData));
  if (debug_mode == 1)
  {
    Serial.print("Bytes received: ");
    Serial.println(len);
  }
  FeedBackSpeed = incomingData.speed;
  FeedBackDirection = incomingData.dir;
}


// // ##edit this function
// void getReadings(){ // To get data from another esp
//   // Read Speed

//   Speed = 50; // ##replace this from speed 

//   if (isnan(Speed)){
//     Serial.println("Failed to read");
//     Speed = 0.0;
//   }

//   Direction = 1;  // ##replace this from direction

//   if (isnan(Direction)){
//     Serial.println("Failed to read");
//     Direction = 0.0;
//   }
// }

void printincomingData(){
  // Display Readings in Serial Monitor
  Serial.println("FEEDBACK READINGS");
  Serial.print("Speed: ");
  Serial.print(FeedBackSpeed);
  Serial.println(" units");
  Serial.print("Direction: ");
  Serial.print(FeedBackDirection);
  Serial.println(" sign");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  // Serial.println("I am Rec_controller : {0xA4, 0xCF, 0x12, 0xBE, 0x6A, 0x7D}");
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Set ESP-NOW Role
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}

void get_serial_reading()
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
        // control();
      } else { // data character
        dataString += incomingChar; // add to input data
      }
  }
}

void loop() {
  unsigned long currentMillis = millis();
  get_serial_reading();
  if (currentMillis - previousMillis >= interval) 
    {
      // time for last updated data
      previousMillis = currentMillis;
      get_serial_reading();

      //Set values to send
      // Data_structure.speed = dataArray[0];
      Data_structure.dir = dataArray[1];

      buttonState = digitalRead(buttonPin);

// condition for serial
      if(buttonState == HIGH)
      {
        Serial.println("------------------------ Button Pressed ----------------------");
        Serial.println(counter);
        counter = counter + 1;
        Data_structure.speed = counter;
        delay(500);
      }
      // else
      // {
      //    dataArray[0] = 0;
      // }

      // Send message via ESP-NOW
      esp_now_send(broadcastAddress, (uint8_t *) &Data_structure, sizeof(Data_structure));

      // Print incoming readings
      if(debug_mode == 1)
      {
        Serial.println("------------------------ Debug Mode ----------------------");
        Serial.println("------------------------ FeedBack Data ----------------------");
        printincomingData();
        Serial.println("------------------------ Parsed Data ----------------------");
        printData();
        Serial.println("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
      }
    }

}

  //////////////////////////////////////////////////////////////////////

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


///////////////////////////////////////////////////////////////////////////


