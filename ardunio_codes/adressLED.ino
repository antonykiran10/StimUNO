/// @file    Blink.ino
/// @brief   Blink the first LED of an LED strip
/// @example Blink.ino

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 72
int x;

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 2
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
    Serial.begin(115200);
    Serial.setTimeout(1);
    pinMode(12, OUTPUT);
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    FastLED.setBrightness(60); // Adjust brightness level as needed
}

void loop() { 
  // Turn the LED on, then pause
  digitalWrite(12, LOW);
  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  while (Serial.available()){
    digitalWrite(12, HIGH);
    x = Serial.readString().toInt();
    Serial.print(1);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    while (!Serial.available());
    x = Serial.readString().toInt();
    Serial.print(1);
  }
  // delay(500);
  // // Now turn the LED off, then pause
  // fill_solid(leds, NUM_LEDS, CRGB::Black);
  // FastLED.show();
  // delay(500);
}
