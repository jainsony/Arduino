/**********************************************************************************
 *  Download the libraries:
 *  https://github.com/Aircoookie/Espalexa
 *  Preferences--> Aditional boards Manager URLs : 
 *  https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *  
 *  Download Board:
 *  For ESP8266 NodeMCU (2.5.1): https://github.com/esp8266/Arduino
 *  For ESP32                  : https://github.com/espressif/arduino-esp32
 **********************************************************************************/
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endifhots
#include <Espalexa.h>
// define the GPIO connected with Relays
#define RelayPin1 0  //D3 phone charger checked
#define RelayPin2 14 //D5 laptop charger checked
#define RelayPin3 5  // D1 checked light
// BuiltInCheck using gpio 13 D7
// #define RelayPin4 5 //D1
// #define RelayPin5 12 //D6

// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void BuiltInCheckfun(uint8_t brightness);

// WiFi Credentials
// const char* ssid = "WoUniversity Mgmt";
// const char* password = "Woxsen#$2020";

const char* ssid = "DOOM123";
const char* password = "laptoptowifi@";

// device names
String Device_1_Name = "Phone charger";
String Device_2_Name = "laptop charger";
String Device_3_Name = "light";
String BuiltInCheck = "Built in Check";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // Initialise wifi connection
  // wifiConnected = connectWifi();

  // if (wifiConnected)
  // {
  //   // Define your devices here.
  //   espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
  //   espalexa.addDevice(Device_2_Name, secondLightChanged);
  //   espalexa.addDevice(Device_3_Name, thirdLightChanged);

  //   espalexa.begin();
  // }
  // else
  // {
    while (!wifiConnected)
    {
        delay(100);
        // built in LOW added in wifi connect function !
        wifiConnected = connectWifi();

  if (wifiConnected)
  {
    // Define your devices here.
    digitalWrite(LED_BUILTIN, LOW); // when connect led turn on, reverse logic
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, secondLightChanged);
    espalexa.addDevice(Device_3_Name, thirdLightChanged);
    espalexa.addDevice(BuiltInCheck, BuiltInCheckfun);
    espalexa.begin();
  }
  else{
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
  }
    }
  // }
}

void loop()
{
  espalexa.loop();
  delay(1);
}

// //our callback functions
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness == 255)
    {
      digitalWrite(RelayPin1, HIGH);
      Serial.print(Device_1_Name);
      Serial.println(" ON");
    }
  else
  {
    digitalWrite(RelayPin1, LOW);
      Serial.print(Device_1_Name);
      Serial.println(" OFF");  
      }
}

void secondLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin2, HIGH);
      Serial.print(Device_2_Name);
      Serial.println(" ON");    
      }
  else
  {
    digitalWrite(RelayPin2, LOW);
      Serial.print(Device_2_Name);
      Serial.println(" OFF");  
      }
}

void thirdLightChanged(uint8_t brightness)
{
  //Control the device  
  if (brightness == 255)
    {
      digitalWrite(RelayPin3, HIGH);
      Serial.print(Device_3_Name);
      Serial.println(" ON");    
      }
  else
  {
    digitalWrite(RelayPin3, LOW);
      Serial.print(Device_3_Name);
      Serial.println(" OFF");  
      }
}

void BuiltInCheckfun(uint8_t brightness)
{
  //Control the device  
  if (brightness == 255)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print(BuiltInCheck);
      Serial.println(" ON");    
      }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
      Serial.print(BuiltInCheck);
      Serial.println(" OFF");  
      }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH); // logic reverse
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
