#include <Adafruit_NeoPixel.h>

// Define pins and LED count
#define LED_PIN     14   // Pin connected to the LED strip
#define BUTTON1_PIN 33   // Pin connected to Button 1
#define BUTTON2_PIN 25   // Pin connected to Button 2
#define NUM_LEDS    300  // Number of LEDs in the strip
#define MAX_CURRENT 3500 // Maximum current in mA
#define LED_CURRENT 60   // Approx. current per LED in mA at full brightness

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  strip.begin();
  

    // Set brightness to limit current
  int maxBrightness = calculateBrightnessLimit();
  strip.setBrightness(maxBrightness);

  strip.show(); // Initialize all LEDs to off
}

void loop() {
  // Check if Button 1 is pressed
  if (digitalRead(BUTTON1_PIN) == HIGH) {
    Serial.print("Strip test 1");
    Serial.println();
    lightUpStairsForward();
    delay(15000);
    fadeDownStrip(20);
  }

  // Check if Button 2 is pressed
  if (digitalRead(BUTTON2_PIN) == HIGH) {
    Serial.print("Strip test 2");
    Serial.println();
    lightUpStairsReverse();
    delay(15000);
    fadeDownStrip(20);
  }

}

void lightUpStairsForward() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(255, 100, 100)); // Red color for animation
    strip.show();
    delay(5); // Delay for animation speed
  }
}

void lightUpStairsReverse() {
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    strip.setPixelColor(i, strip.Color(255, 100, 100)); // Red color for reverse animation
    strip.show();
    delay(5); // Delay for animation speed
  }
}

void fadeDownStrip(int fadeDelay) {
  for (int brightness = 255; brightness >= 0; brightness--) {
    for (int i = 0; i < NUM_LEDS; i++) {
      // Get the current color of each pixel
      uint32_t color = strip.getPixelColor(i);

      // Extract RGB components from the current color
      uint8_t r = (color >> 16) & 0xFF;
      uint8_t g = (color >> 8) & 0xFF;
      uint8_t b = color & 0xFF;

      // Scale RGB components with a bias to reduce red prominence
      float redBias = 0.8; // Adjust bias for red (lower value reduces red intensity)
      //float blueBias = 0.6;
      uint8_t newR = r * brightness / 255 * redBias;
      uint8_t newG = g * brightness / 255;
      uint8_t newB = b * brightness / 255;

      // Set the new scaled color
      strip.setPixelColor(i, strip.Color(newR, newG, newB));
    }
    strip.show();
    delay(fadeDelay); // Adjust fade speed
  }
}


int calculateBrightnessLimit() {
  // Calculate maximum brightness to limit current to 1A
  int maxLEDsAtFullBrightness = MAX_CURRENT / LED_CURRENT; // LEDs that can be fully lit
  float brightnessFactor = (float)maxLEDsAtFullBrightness / NUM_LEDS;
  int maxBrightness = brightnessFactor * 255; // Scale brightness (0-255)
  return constrain(maxBrightness, 1, 255); // Ensure brightness is in valid range
}
