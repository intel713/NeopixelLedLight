#include <Adafruit_NeoPixel.h>

#define LED_PIN 3
#define LED_COUNT 25
#define BRIGHTNESS 255

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int red[3] = {255, 0, 0};
int green[3] = {0, 255, 0};
int blue[3] = {0, 0, 255};

void setup() {
  strip.begin();
  strip.setBrightness(255);
}

void loop() {
  colorGradient(red, blue);
  delay(10000);
  colorGradient(blue, green);
  delay(10000);
  colorGradient(green, red);
  delay(10000);
  rainbow(15000, 20, 2.5);
}



void colorGradient(int col_1[], int col_2[])
{
  for (int i = 0; i < LED_COUNT; i++)
  {
    int red = map(i, 0, LED_COUNT, col_1[0], col_2[0]);
    int green = map(i, 0, LED_COUNT, col_1[1], col_2[1]);
    int blue = map(i, 0, LED_COUNT, col_1[2], col_2[2]);
    strip.setPixelColor(i, red, green, blue);
  }
  strip.show();
}

void rainbow(unsigned int num_loop, int vel, float cycle_len)
{
  for (int i = 0; i < num_loop; i++)
  {
    for (int j = 0; j < LED_COUNT; j++)
    {
      strip.setPixelColor((LED_COUNT - j - 1), strip.ColorHSV(map(j, 0, LED_COUNT, 0, 65536.0 / cycle_len) + i*vel, 255, 255));
    }
    strip.show();
  }
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
    int r = random(255);
    randomSeed(analogRead(random(7)));
    int g = random(255);
    randomSeed(analogRead(random(7)));
    int b = random(255);
    colorWipe(strip.Color(r, g, b), waiting);
  }
}
