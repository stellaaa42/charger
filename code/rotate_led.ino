// the leds change color by sequence

#include <FastLED.h>

#define LED_PIN     6       // The pin connected to the DIN of the LED strip
#define NUM_LEDS    30      // Number of LEDs in the strip
#define BRIGHTNESS  64      // Brightness level (0-255)
#define LED_TYPE    WS2812B // Type of LED
#define COLOR_ORDER GRB     // Color order

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the current LED to red
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(100); // Wait for 100 milliseconds

  }
  
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the current LED to green
    leds[i] = CRGB::Green;
    FastLED.show();
    delay(100); // Wait for 100 milliseconds


  }
  
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the current LED to blue
    leds[i] = CRGB::Blue;
    FastLED.show();
    delay(100); // Wait for 100 milliseconds

  }
}
