#include <FastLED.h>

// Pin Definitions
#define LED_PIN 4 // GPIO 4 (D2 on ESP8266)
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Transition to green
  for (int j = 0; j < NUM_LEDS; j++) {
    leds[j] = CRGB(0, 255, 0); // Green
    FastLED.show();
    delay(50);
  }
  delay(10);

  // Transition to purple
  for (int j = 0; j < NUM_LEDS; j++) {
    leds[j] = CRGB(255, 0, 255); // Purple
    FastLED.show();
    delay(50);
  }
  delay(10);f
}
