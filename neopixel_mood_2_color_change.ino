#include <Adafruit_NeoPixel.h>

#define LED_PIN 3
#define LED_COUNT 25
#define BRIGHTNESS 255

#define DELAY 5000

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int start_color, end_color;
int start_color_prev, end_color_prev;

int red[3] = {255, 0, 0};
int green[3] = {0, 255, 0};
int blue[3] = {0, 0, 255};
int yellow[3] = {255, 255, 0};
int cyan[3] = {0, 255, 255};
int magenta[3] = {255, 0, 255};

int colors[6] =
{
  red,
  green,
  blue,
  yellow,
  cyan,
  magenta
};

void setup() {
  strip.begin();
  strip.setBrightness(255);
  strip.clear();
  strip.show();
  start_color_prev = 0;
  end_color_prev = 2;
  colorGradientOn(colors[start_color_prev], colors[end_color_prev], 2);
  delay(DELAY);
}

void loop() {
  randomSeed(analogRead(random(7)));
  for (int i = 0; i < 15; i++)
  {
    start_color = random(6);
    end_color = random(6);

    while (start_color == end_color)
    {
      start_color = random(6);
      end_color = random(6);
    }
    
    delay(DELAY);
    colorGradientChange(colors[start_color_prev], colors[end_color_prev], colors[start_color], colors[end_color], 1);
    start_color_prev = start_color;
    end_color_prev = end_color;
  }
  delay(DELAY);
  colorGradientOff(colors[start_color], colors[end_color], 2);
  delay(1000);

  rainbow(20000, 20, 2.5);
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

void colorGradientOn(int col_1[], int col_2[], int del)
{
  for (int j = 0; j <= 255; j++)
  {
    for (int i = 0; i < LED_COUNT; i++)
    {
      int red = map(i, 0, LED_COUNT, col_1[0], col_2[0]);
      int green = map(i, 0, LED_COUNT, col_1[1], col_2[1]);
      int blue = map(i, 0, LED_COUNT, col_1[2], col_2[2]);
      
      int b_red = map(j, 0, 255, 0, red);
      int b_green = map(j, 0, 255, 0, green);
      int b_blue = map(j, 0, 255, 0, blue);
      
      strip.setPixelColor(i, b_red, b_green, b_blue);
    }
    strip.show();
  }
  delay(del);
}

void colorGradientOff(int col_1[], int col_2[], int del)
{
  for (int j = 255; j >= 0; j--)
  {
    for (int i = 0; i < LED_COUNT; i++)
    {
      int red = map(i, 0, LED_COUNT, col_1[0], col_2[0]);
      int green = map(i, 0, LED_COUNT, col_1[1], col_2[1]);
      int blue = map(i, 0, LED_COUNT, col_1[2], col_2[2]);
      
      int b_red = map(j, 0, 255, 0, red);
      int b_green = map(j, 0, 255, 0, green);
      int b_blue = map(j, 0, 255, 0, blue);
      
      strip.setPixelColor(i, b_red, b_green, b_blue);
    }
    strip.show();
  }
  delay(del);
}

void colorGradientChange(int col_1[], int col_2[], int col_3[], int col_4[], int del)
{
  for (int j = 0; j <= 255; j++)
  {
    for (int i = 0; i < LED_COUNT; i++)
    {
      int red1 = map(i, 0, LED_COUNT, col_1[0], col_2[0]);
      int green1 = map(i, 0, LED_COUNT, col_1[1], col_2[1]);
      int blue1 = map(i, 0, LED_COUNT, col_1[2], col_2[2]);
      
      int red2 = map(i, 0, LED_COUNT, col_3[0], col_4[0]);
      int green2 = map(i, 0, LED_COUNT, col_3[1], col_4[1]);
      int blue2 = map(i, 0, LED_COUNT, col_3[2], col_4[2]);

      int b_red = map(j, 0, 255, red1, red2);
      int b_green = map(j, 0, 255, green1, green2);
      int b_blue = map(j, 0, 255, blue1, blue2);
      
      strip.setPixelColor(i, b_red, b_green, b_blue);
    }
    strip.show();
  }
  delay(del);
}
