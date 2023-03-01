#include <Adafruit_NeoPixel.h>

#define LED_PIN 3
#define LED_COUNT 25

int r = 0, g = 0, b = 0;

int colordata[25][3] = {
{255, 0, 0},
{255, 0, 0},
{255, 0, 0},
{255, 0, 0},
{255, 0, 4},
{255, 0, 8},
{255, 0, 16},
{255, 0, 32},
{255, 0, 48},
{255, 0, 64},
{255, 0, 96},
{255, 0, 128},
{255, 0, 255},
{192, 0, 255},
{128, 0, 255},
{96, 0, 255},
{64, 0, 255},
{48, 0, 255},
{32, 0, 255},
{24, 0, 255},
{16, 0, 255},
{0, 0, 255},
{0, 0, 255},
{0, 0, 255},
{0, 0, 255},
};

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(225);
}

void loop() {
  colorWiping(5, 50);
  
  custompattern(5000);
  
  rainbow(10);
}





void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void colorWiping(int repeat, int waiting) {
  for (int i = 0; i < repeat; i++){
    randomSeed(analogRead(random(7)));
    r = random(255);
    randomSeed(analogRead(random(7)));
    g = random(255);
    randomSeed(analogRead(random(7)));
    b = random(255);
    colorWipe(strip.Color(r, g, b), waiting);
  }
}

void custompattern(int duration) {
  for (int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, colordata[i][0], colordata[i][1], colordata[i][2]);
  }
  strip.show();
  delay(duration);
}

void rainbow(int wait) {  
  for (long firstPixelHue = 0; firstPixelHue < 5 * 32768; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());      
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}
