// uint8_t broadcastAddress[] = {0xA4, 0xCF, 0x12, 0xF3, 0x84, 0x5D}; 
/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp8266-nodemcu/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>


// REPLACE WITH THE MAC Address of your receiver 
// uint8_t broadcastAddress[] = {0xEC, 0xFA, 0xBC, 0xC1, 0xE6, 0xEA};
uint8_t broadcastAddress[] = {0xA4, 0xCF, 0x12, 0xBE, 0x6A, 0x7D};

uint8_t debug_mode = 1;

#define PWM1 5    // D1  these are working
#define DIR1 4      // D2

#define PWM2 0    // D3 these are working
#define DIR2 2      // D4

#define datalen 4
#define threshold 5

int i = 0;

int a_speed = 0;
int b_speed = 0;


// Define variables to store DHT readings to be sent
float Speed;
float Direction;

// Define variables to store incoming readings
float incomingSpeed;
float incomingDir;

String dataString = ""; // variable to hold input data
int dataArray[datalen]; // array to hold parsed integers
int dataIndex = 0; // index for dataArray

const long interval = 100; 
unsigned long previousMillis = 0;    // will store last time DHT was updated 

String success;

typedef struct struct_message {
    float speed;
    float dir;
} struct_message;

struct_message Data_structure;

struct_message incomingReadings;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  if(debug_mode == 1)
    Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    if(debug_mode == 1)
      Serial.println("Delivery success");
  }
  else{
    if(debug_mode == 1)
      Serial.println("Delivery fail");
  }
}

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  if(debug_mode == 1)
  {
    Serial.print("Bytes received: ");
    Serial.println(len);
  }

  incomingSpeed = incomingReadings.speed;
  incomingDir = incomingReadings.dir;
}

// ##edit this function
void getReadings(){
  // reciving data
  Speed = incomingSpeed; // ##replace this from speed 
  // Read Speed as Fahrenheit (isFahrenheit = true)
  //float t = dht.readTemperature(true);
  if (isnan(Speed)){
    Serial.println("Failed to read");
    Speed = 0.0;
  }
  // reciving data
  Direction = incomingDir;  // ##replace this from direction
  if (isnan(Direction)){
    Serial.println("Failed to read");
    Direction = 0.0;
  }
}

void printIncomingReadings(){
  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS");
  Serial.print("Speed: ");
  Serial.print(incomingSpeed);
  Serial.println(" units");
  Serial.print("Direction: ");
  Serial.print(incomingDir);
  Serial.println(" sign");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  pinMode(PWM1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(DIR2, OUTPUT);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  Serial.println("{0xA4, 0xCF, 0x12, 0xF3, 0x84, 0x5D}");
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
 
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;

    //Get DHT readings
    getReadings();

    //Set values to send
    Data_structure.speed = Speed;
    Data_structure.dir = Direction;

    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &Data_structure, sizeof(Data_structure));

    // Print incoming readings
          if(debug_mode == 1)
      {
        Serial.println("------------------------ Debug Mode ----------------------");
        Serial.println("------------------------ Incoming Data ----------------------");
        printIncomingReadings();
        control();
        Serial.println("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
      }
  }
}

//////////////////////////////////////////////

// work on "Speed" and Direction "vaiable"
void control()
{
  if(Speed > threshold)
  {
    a_speed = Speed;
    analogWrite(PWM1, a_speed);
    digitalWrite(DIR1, LOW);
    analogWrite(PWM2, a_speed);
    digitalWrite(DIR2, LOW);
  }
  else if(Speed < -threshold)
  {
    a_speed = -1*Speed;
    analogWrite(PWM1, a_speed);
    digitalWrite(DIR1, HIGH);
    analogWrite(PWM2, a_speed);
    digitalWrite(DIR2, HIGH);
  }
  else if(Direction > threshold)
  {
    b_speed = Direction;
    analogWrite(PWM1, b_speed);
    digitalWrite(DIR1, LOW);
    analogWrite(PWM2, b_speed);
    digitalWrite(DIR2, HIGH);

  }
  else if(Direction < -threshold)
  {
    b_speed = -1*Direction;
    analogWrite(PWM1, b_speed);
    digitalWrite(DIR1, HIGH);
    analogWrite(PWM2, b_speed);
    digitalWrite(DIR2, LOW);
    
  }
  else
  {
    analogWrite(PWM1, LOW);
    analogWrite(PWM2, LOW);
    analogWrite(DIR1, LOW);
    analogWrite(DIR2, LOW);
    Speed=0;
    Direction=0;
    // dataArray[2]
    // dataArray[3]
  }

}


////////////////////////////////////////////

