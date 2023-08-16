#include <Arduino.h>
#include <Espalexa.h>

// Define device names
const char* Device_1_Name = "Device1";
const char* Device_2_Name = "Device2";
const char* Device_3_Name = "Device3";

// Define callback functions for Alexa intents
void firstLightChanged(uint8_t state) {
    // Code for handling the first light change
}

void secondLightChanged(uint8_t state) {
    // Code for handling the second light change
}

void thirdLightChanged(uint8_t state) {
    // Code for handling the third light change
}

void setup() {
    Serial.begin(115200);
    delay(100);

    // Initialize the Espalexa library
    EspalexaDevice* devices[] = {
        new EspalexaDevice(Device_1_Name, firstLightChanged),
        new EspalexaDevice(Device_2_Name, secondLightChanged),
        new EspalexaDevice(Device_3_Name, thirdLightChanged)
    };

    // Create Espalexa object with devices
    Espalexa espalexa(devices, sizeof(devices) / sizeof(devices[0]));

    // Define custom phrases for your devices
    const char* customPhrases[] = {
        "Turn on the lights",
        "Turn off the lights",
        "Toggle the lights"
    };

    // Register custom phrases with each device
    devices[0]->addCustomPhrases(customPhrases, sizeof(customPhrases) / sizeof(customPhrases[0]));

    // Begin the Alexa library
    espalexa.begin();

    Serial.println("Setup complete");
}

void loop() {
    // Handle Alexa requests
    espalexa.loop();

    // Your other code here
}
