#include <FastLED.h>

#define LED_PIN 4
#define NUM_LEDS 50

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  for (int j = 0; j < NUM_LEDS; j++) {
    leds[j] = CRGB(0, 255, 0);
    FastLED.show();
    delay(50);
  }
  delay(10);

  for (int j = 0; j < NUM_LEDS; j++) {
    leds[j] = CRGB(255, 0, 255);
    FastLED.show();
    delay(50);
  }
  delay(10);
}
