#include <Adafruit_NeoPixel.h>
#include <DHT.h>

// Define pins and constants
#define PIN_NEOPIXEL 6
#define NUMPIXELS    8  // Number of LEDs on the strip
#define PIN_DHT      7  // Pin connected to the DHT sensor
#define DHTTYPE      DHT11  // DHT sensor type
#define PIN_PIR      2  // Pin connected to the PIR sensor
#define LDR_PIN      A0  // Pin connected to the LDR (Light Dependent Resistor)
#define MOTION_TIMEOUT 30000  // Timeout for motion detection (in milliseconds)
#define FADE_INTERVAL 20  // Interval for fading effect

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
DHT dht(PIN_DHT, DHTTYPE);
unsigned long lastMotionTime = 0;  // Timestamp of the last detected motion
bool isFading = false;  // Flag to check if fading effect is active

void setup() {
  pixels.begin();  // Initialize NeoPixel LEDs
  dht.begin();  // Initialize DHT sensor
  pinMode(PIN_PIR, INPUT);  // Set PIR sensor pin as input
  pinMode(LDR_PIN, INPUT);  // Initialize LDR pin
  Serial.begin(9600);  // Start serial communication
}

void loop() {
  float temperature = dht.readTemperature();  // Read temperature from DHT sensor
  int ldrValue = analogRead(LDR_PIN);  // Read the value from LDR

  // Check if temperature reading failed
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  int pirState = digitalRead(PIN_PIR);  // Read the state of PIR sensor
  if (pirState == HIGH) {
    // Motion detected
    lastMotionTime = millis();  // Update the last motion time
    isFading = false;
    // Map the LDR value to brightness (lower light -> higher brightness)
    int brightness = map(ldrValue, 0, 1023, 100, 10);
    brightness = constrain(brightness, 10, 100);  // Constrain brightness values
    setColorBasedOnTemperature(temperature, brightness);  // Set color based on temperature
  } else if (millis() - lastMotionTime > MOTION_TIMEOUT && !isFading) {
    // No motion detected for a specified time
    isFading = true;
    fadeToBrightness(10);  // Fade brightness to 10% after timeout
  }

  delay(1000);  // Delay to reduce the number of readings
}

