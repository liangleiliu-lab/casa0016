#include <Adafruit_NeoPixel.h>

// Define connected pins and constants
#define PIN_NEOPIXEL 6
#define NUMPIXELS    8  // Number of LEDs on the strip
#define SOUND_SENSOR_PIN A0  // Pin connected to the sound sensor
#define SOUND_SAMPLES 10  // Number of sound samples for averaging
#define FADE_INTERVAL 20  // Interval for fading effect (milliseconds)

// Create NeoPixel object
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();  // Initialize NeoPixel strip
  pinMode(SOUND_SENSOR_PIN, INPUT);  // Initialize sound sensor pin
  Serial.begin(9600);  // Start serial communication
}

void loop() {
  int soundValue = analogRead(SOUND_SENSOR_PIN);  // Read sound level
  int brightness = map(soundValue, 0, 1023, 0, 255);  // Map sound level to brightness
  brightness = constrain(brightness, 0, 255);  // Constrain brightness values

  setAllPixelsBrightness(brightness);  // Set brightness of all pixels

  // Output sound sensor reading for debugging
  Serial.print("Sound Level: ");
  Serial.println(soundValue);

  delay(1000);  // Delay to reduce sensor reading frequency
}

// Function to set brightness of all pixels
void setAllPixelsBrightness(int brightness) {
  uint32_t color = pixels.Color(brightness, brightness, brightness);
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}
