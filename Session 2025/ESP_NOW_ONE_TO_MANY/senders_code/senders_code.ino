// // #include <ESP8266WiFi.h>
// #include <espnow.h>
// #include <WiFi.h>

// // REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
// uint8_t broadcastAddress1[] = {0xEC, 0xFA, 0xBC, 0xC1, 0xE6, 0xEA};
// // uint8_t broadcastAddress2[] = {0xFF, , , , , };
// // uint8_t broadcastAddress3[] = {0xFF, , , , , };

// typedef struct test_struct {
//   int x;
//   int y;
// } test_struct;

// test_struct test;

// esp_now_peer_info_t peerInfo;

// // callback when data is sent
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   char macStr[18];
//   Serial.print("Packet to: ");
//   // Copies the sender mac address to a string
//   snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
//            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//   Serial.print(macStr);
//   Serial.print(" send status:\t");
//   Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
// }
 
// void setup() {
//   Serial.begin(9600);
 
//   WiFi.mode(WIFI_STA);
 
//   if (esp_now_init() != ESP_OK) {
//     Serial.println("Error initializing ESP-NOW");
//     return;
//   }
  
//   esp_now_register_send_cb(OnDataSent);
   
//   // register peer
//   peerInfo.channel = 0;  
//   peerInfo.encrypt = false;
//   // register first peer  
//   memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
//   if (esp_now_add_peer(&peerInfo) != ESP_OK){
//     Serial.println("Failed to add peer");
//     return;
//   }
//   // register second peer  
//   memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
//   if (esp_now_add_peer(&peerInfo) != ESP_OK){
//     Serial.println("Failed to add peer");
//     return;
//   }
//   /// register third peer
//   memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
//   if (esp_now_add_peer(&peerInfo) != ESP_OK){
//     Serial.println("Failed to add peer");
//     return;
//   }
// }
 
// void loop() {
//   test.x = random(0,20);
//   test.y = random(0,20);
 
//   esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct));
   
//   if (result == ESP_OK) {
//     Serial.println("Sent with success");
//   }
//   else {
//     Serial.println("Error sending the data");
//   }
//   delay(2000);
// }

#include <ESP8266WiFi.h>
#include <espnow.h>

// Replace these with your Slave ESP8266 MAC addresses
uint8_t slave1_mac[] = {0x3C, 0x61, 0x05, 0xDD, 0xE3, 0xA2};  // Example MAC
uint8_t slave2_mac[] = {0x5C, 0xCF, 0x7F, 0x49, 0xC6, 0x50};  // Example MAC

typedef struct struct_message {
    int id;
    float temperature;
} struct_message;

struct_message myData;

void onSent(uint8_t *mac_addr, uint8_t status) {
    Serial.print("Delivery Status: ");
    Serial.println(status == 0 ? "Success" : "Fail");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);  // Station mode required for ESP-NOW
    if (esp_now_init() != 0) {
        Serial.println("ESP-NOW Init Failed");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_register_send_cb(onSent);

    // Add peers (Slaves)
    esp_now_add_peer(slave1_mac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
    esp_now_add_peer(slave2_mac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
    myData.id = random(1, 100);  // Example ID
    myData.temperature = random(20, 30);  // Fake temperature data

    Serial.print("Sending to Slave 1: ");
    Serial.println(myData.temperature);
    esp_now_send(slave1_mac, (uint8_t *) &myData, sizeof(myData));

    Serial.print("Sending to Slave 2: ");
    Serial.println(myData.temperature);
    esp_now_send(slave2_mac, (uint8_t *) &myData, sizeof(myData));

    delay(100);  // Send every 2 seconds
}
