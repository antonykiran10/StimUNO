#include <FastLED.h>

#define NUM_LEDS 60
#define DATA_PIN 2
#define CLOCK_PIN 13
#define LED_GROUP_SIZE 8

CRGB leds[NUM_LEDS];

// Time for one LED to move one position (in milliseconds)
const unsigned long LED_MOVE_TIME = 40; // 1 second
const unsigned long DIRECTION_CHANGE_INTERVAL = 30000; // 30 seconds

unsigned long previousMillis = 0; // Stores the previous time when the direction was changed
bool moveRight = true; // Initially, move the LEDs to the right

void setup() {
    Serial.begin(115200);
    pinMode(12, OUTPUT);
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    FastLED.setBrightness(200); // Adjust brightness level as needed
}

void loop() {
    // Check if it's time to change the direction
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= DIRECTION_CHANGE_INTERVAL) {
        // Change the direction
        moveRight = !moveRight;
        previousMillis = currentMillis;
    }

    // Define the positions of the first LED in each group of eight
    static int positions[LED_GROUP_SIZE] = {0, 8, 16, 24, 32, 40, 48, 56};
    static int prevPositions[LED_GROUP_SIZE];

    // Turn off all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    // Set all LEDs in each group of eight to white
    for (int i = 0; i < LED_GROUP_SIZE; i++) {
        leds[positions[i]] = CRGB::White;
    }

    // Show the LEDs
    FastLED.show();

    // Clear the previous LED positions
    for (int i = 0; i < LED_GROUP_SIZE; i++) {
        leds[prevPositions[i]] = CRGB::Black;
    }

    // Move each group of eight LEDs to the next position
    if (moveRight) {
        for (int i = 0; i < LED_GROUP_SIZE; i++) {
            prevPositions[i] = positions[i];
            positions[i] = (positions[i] + 1) % NUM_LEDS;
        }
    } else {
        for (int i = 0; i < LED_GROUP_SIZE; i++) {
            prevPositions[i] = positions[i];
            positions[i] = (positions[i] == 0) ? (NUM_LEDS - 1) : (positions[i] - 1);
        }
    }

    // Delay to control animation speed
    delay(LED_MOVE_TIME); // Adjust delay based on LED move time
}
