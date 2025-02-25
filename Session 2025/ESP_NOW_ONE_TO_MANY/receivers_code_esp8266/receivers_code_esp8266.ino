// #include <ESP8266WiFi.h>
// #include <espnow.h>

// //Structure example to receive data
// //Must match the sender structure
// typedef struct test_struct {
//   int x;
//   int y;
// } test_struct;

// //Create a struct_message called myData
// test_struct myData;

// //callback function that will be executed when data is received
// void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
//   memcpy(&myData, incomingData, sizeof(myData));
//   Serial.print("Bytes received: ");
//   Serial.println(len);
//   Serial.print("x: ");
//   Serial.println(myData.x);
//   Serial.print("y: ");
//   Serial.println(myData.y);
//   Serial.println();
// }
 
// void setup() {
//   //Initialize Serial Monitor
//   Serial.begin(115200);
  
//   //Set device as a Wi-Fi Station
//   WiFi.mode(WIFI_STA);

//   //Init ESP-NOW
//   if (esp_now_init() != 0) {
//     Serial.println("Error initializing ESP-NOW");
//     return;
//   }
  
//   // Once ESPNow is successfully Init, we will register for recv CB to
//   // get recv packer info
//   esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
//   esp_now_register_recv_cb(OnDataRecv);
// }
 
// void loop() {

// }

///////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct struct_message {
    int id;
    float temperature;
} struct_message;

void onReceive(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
    struct_message myData;
    memcpy(&myData, incomingData, sizeof(myData));

    Serial.print("Received from Master -> ID: ");
    Serial.print(myData.id);
    Serial.print(" | Temperature: ");
    Serial.println(myData.temperature);
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != 0) {
        Serial.println("ESP-NOW Init Failed");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(onReceive);
}

void loop() {
    // The ESP-NOW callback will handle incoming messages
}


//////////////////////////////////////////////////////////////////////


// #include <ESP8266WiFi.h>

// void setup() {
//     Serial.begin(115200);
//     WiFi.mode(WIFI_STA);  // Set device in Station mode
//     Serial.print("ESP8266 MAC Address: ");
//     Serial.println(WiFi.macAddress());  // Print MAC address
// }

// void loop() {
//     // Nothing needed here
// }
