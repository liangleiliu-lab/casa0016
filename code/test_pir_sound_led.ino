#include <Adafruit_NeoPixel.h>

// Define pins for PIR sensor, sound sensor, and NeoPixel strip
#define PIR_PIN 2
#define SOUND_SENSOR_PIN A0
#define PIN_NEOPIXEL 6
#define NUMPIXELS 16  // Number of LEDs on the strip

// Create NeoPixel object
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set PIR sensor pin as input
  pinMode(PIR_PIN, INPUT);

  // Initialize the NeoPixel strip
  pixels.begin();

  Serial.println("PIR, Sound Sensor and NeoPixel Test Started");
}

void loop() {
  // Read the value from the PIR sensor
  int pirValue = digitalRead(PIR_PIN);

  // Read the analog value from the sound sensor
  int soundValue = analogRead(SOUND_SENSOR_PIN);

  // Check if the PIR sensor has detected motion
  if (pirValue) {
    Serial.println("Motion detected!");
    // If motion is detected, set the strip to red
    setAllPixelsColor(255, 0, 0);
  } else {
    Serial.println("No motion");
    // If no motion is detected, turn off the strip
    setAllPixelsColor(0, 0, 0);
  }

  // Print the sound sensor reading
  Serial.print("Sound Level: ");
  Serial.println(soundValue);

  // Delay slightly to reduce the amount of output
  delay(1000);
}

void setAllPixelsColor(uint8_t red, uint8_t green, uint8_t blue) {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }
  pixels.show();
}
