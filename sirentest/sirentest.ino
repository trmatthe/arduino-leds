#include "FastLED.h"

// Pride2015
// Animated, ever-changing rainbows.
// by Mark Kriegsman

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    2
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    150
#define BRIGHTNESS  255

CRGB leds[NUM_LEDS];


void setup() {

  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

bool doRed = false;

void loop()
{
  for (int i=0; i < 150; i++) {
    leds[i] = doRed ? CRGB::Red : CRGB::Blue;
  }
  doRed = !doRed;
  
  FastLED.show();
  delay(20);

for (int i=0; i < 150; i++) {
    leds[i] = CRGB(0,0,0);
  }

  FastLED.show();
  delay(5);

  
}
