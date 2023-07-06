#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    60
#define violet      (143,0,255)
#define cyan        (0,255,255)
#define red        (255,0,0)
#define blue        (0,0,255)

CRGB leds[NUM_LEDS];

void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

}

void loop() {

  for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB cyan;
    FastLED.show();
    delay(40);
  }
  for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB violet;
    FastLED.show();
    delay(40);
  }
}