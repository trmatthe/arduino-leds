
#include <FastLED.h>

#define LED_PIN 2
#define WIDTH 24 //max # of leds for this code
#define HEIGHT 20
#define COUNT 480
#define dist(a, b, c, d) sqrt(double((a-c) * (a-c) + (b - d) * (b - d)))
CRGB leds[WIDTH * HEIGHT];

const uint8_t kMatrixWidth = WIDTH;
const uint8_t kMatrixHeight = HEIGHT;

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;

void setup() {
  //be sure to add your leds
  FastLED.addLeds< WS2812B, LED_PIN, GRB >(leds, WIDTH * HEIGHT);
  FastLED.showColor(CRGB::Red);
  FastLED.setBrightness( 64);
  FastLED.show();
}
int count;
void loop() {

  wave();
  Serial.begin(57600);
      //threeSine();
    //walk();
    FastLED.show();
  //  delay(5);
  //  dump();
}
int i = 0;

byte f2b(float f) {

  return (byte)(f * (float)255);
}

int iFrame = 0;// 700000;


void wave() {

   iFrame += 1;
  
  float r, g, b;

  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {

      r = 0.5 + 0.5 * sin(0.025 * iFrame + (x / 16.0) + 0.);
      g = 0.5 + 0.5 * sin(0.025 * iFrame + (y / 8.0) + 2.);
      b = 0.5 + 0.5 * sin(0.025 * iFrame + (y / 16.0) + 4.);

     /* Serial.print("float r: ");
      Serial.print(r);
      Serial.print(" byte r: ");
      Serial.print((byte) (r * (float)255));
      Serial.println();
*/
      leds[XY(x, y)] = CRGB(f2b(r), f2b(g), f2b(b));
    }
  }
}

void dump() {

for (int i=0; i < kMatrixWidth; i++) {
  Serial.print(leds[i]);
}
Serial.println();

}

uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;


  if ( y & 0x01) {
    // Odd rows run backwards
    // Even rows run forwards
    i = (y * kMatrixWidth) + x;

  } else {

    uint8_t reverseX = (kMatrixWidth - 1) - x;
    i = (y * kMatrixWidth) + reverseX;

  }

  return i;
}


static byte offset  = 0; // counter for radial color wave motion
static int plasVector = 0; // counter for orbiting plasma center
void plasma() {

  // startup tasks

  // Calculate current center of plasma pattern (can be offscreen)
  int xOffset = cos8(plasVector / 256);
  int yOffset = sin8(plasVector / 256);

  // Draw one frame of the animation into the LED array
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      byte color = sin8(sqrt(sq(((float)x - 7.5) * 10 + xOffset - 127) + sq(((float)y - 2) * 10 + yOffset - 127)) + offset);
      leds[XY(x, y)] = CHSV(color, 255, 255);
      //  leds[XY(x+1,y)] = CHSV(color, 255, 255);
      //  leds[XY(x,y+1)] = CHSV(color, 255, 255);
      //  leds[XY(x+1,y+1)] = CHSV(color, 255, 255);
    }
  }

  offset++; // wraps at 255 for sin8
  plasVector += 64; // using an int for slower orbit (wraps at 65536)

}

static byte sineOffset = 0; // counter for current position of sine waves

void threeSine() {



  // Draw one frame of the animation into the LED array
  for (byte x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {

      // Calculate "sine" waves with varying periods
      // sin8 is used for speed; cos8, quadwave8, or triwave8 would also work here
      byte sinDistanceR = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 9 + x * 16)), 2);
      byte sinDistanceG = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 10 + x * 16)), 2);
      byte sinDistanceB = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 11 + x * 16)), 2);

      leds[XY(x, y)] = CRGB(255 - sinDistanceR, 255 - sinDistanceG, 255 - sinDistanceB);
    }
  }

  sineOffset++; // byte will wrap from 255 to 0, matching sin8 0-255 cycle

}
