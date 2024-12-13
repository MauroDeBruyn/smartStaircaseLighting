#include <FastLED.h>

// Define pins and LED count
#define LED_PIN     14   // Pin connected to the LED strip
#define BUTTON1_PIN 33   // Pin connected to Button 1
#define BUTTON2_PIN 25   // Pin connected to Button 2
#define NUM_LEDS    300  // Number of LEDs in the strip

CRGB leds[NUM_LEDS]; // Create an array to hold the LED colors

void setup() {
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS); // Initialize the LED strip
  FastLED.setBrightness(7); // Set the brightness level (0-255)

  FastLED.show(); // Initialize all LEDs to off
}

void loop() {
  // Check if Button 1 is pressed
  if (digitalRead(BUTTON1_PIN) == HIGH) {
    lightUpStairsForward();
    delay(20000);
    fadeDownStrip(5);
  }

  // Check if Button 2 is pressed
  if (digitalRead(BUTTON2_PIN) == HIGH) {
    lightUpStairsReverse();
    delay(20000);
    fadeDownStrip(5);
  }
}

// Function to light up LEDs in a "staircase" fashion forward
void lightUpStairsForward() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 100, 100); // Red color for animation
    FastLED.show();
    delay(5); // Delay for animation speed
  }
}

// Function to light up LEDs in a "staircase" fashion reverse
void lightUpStairsReverse() {
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = CRGB(255, 100, 100); // Red color for reverse animation
    FastLED.show();
    delay(5); // Delay for animation speed
  }
}

// Function to fade down the LED strip
void fadeDownStrip(int fadeDelay) {
  for (int brightness = 255; brightness >= 0; brightness--) {
    for (int i = 0; i < NUM_LEDS; i++) {
      // Get the current color of each LED
      CRGB currentColor = leds[i];

      // Scale RGB components with a bias to reduce red prominence
      float redBias = 0.95; // Adjust bias for red (lower value reduces red intensity)
      uint8_t newR = currentColor.r * brightness / 255 * redBias;
      uint8_t newG = currentColor.g * brightness / 255;
      uint8_t newB = currentColor.b * brightness / 255;

      // Set the new scaled color
      leds[i] = CRGB(newR, newG, newB);
    }
    FastLED.show();
    delay(fadeDelay); // Adjust fade speed
  }
}
