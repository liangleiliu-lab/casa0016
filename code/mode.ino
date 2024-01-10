#include <Adafruit_NeoPixel.h>
#include <DHT.h>

// Define connected pins and constants
#define PIN_NEOPIXEL 6  // NeoPixel LED strip pin
#define NUMPIXELS    8  // Number of LEDs on the strip
#define PIN_DHT      7  // DHT sensor pin
#define DHTTYPE      DHT11  // Type of DHT sensor
#define PIN_PIR      2  // PIR motion sensor pin
#define LDR_PIN      A0  // Light-dependent resistor pin
#define MOTION_TIMEOUT 30000  // Timeout for motion detection (milliseconds)
#define FADE_INTERVAL 20  // Interval for fading effect (milliseconds)

// Create instances for NeoPixel and DHT
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
DHT dht(PIN_DHT, DHTTYPE);
unsigned long lastMotionTime = 0;  // Stores last time motion was detected
bool isFading = false;  // Flag to indicate if fading effect is active

void setup() {
  pixels.begin();  // Initialize NeoPixel strip
  dht.begin();  // Initialize DHT sensor
  pinMode(PIN_PIR, INPUT);  // Set PIR sensor pin as input
  pinMode(LDR_PIN, INPUT);  // Initialize LDR pin
  Serial.begin(9600);  // Start serial communication
}

void loop() {
  float temperature = dht.readTemperature();  // Read temperature
  int ldrValue = analogRead(LDR_PIN);  // Read light level from LDR

  // Check for successful temperature reading
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  int pirState = digitalRead(PIN_PIR);  // Read motion state from PIR sensor
  // Adjust LED settings based on motion and light level
  if (ldrValue < SOME_LIGHT_THRESHOLD) {  // Check if the ambient light is low
    if (pirState == HIGH) {
      // Motion detected
      lastMotionTime = millis();  // Update last motion time
      isFading = false;
      setColorBasedOnTemperature(temperature);  // Set color based on temperature
    } else if (millis() - lastMotionTime > MOTION_TIMEOUT && !isFading) {
      // No motion for defined timeout
      isFading = true;
      fadeToBrightness(10);  // Fade lights to 10%
    }
  } else {
    // Ambient light is high, turn off the lights
    setAllPixelsColor(0, 0, 0);
  }

  delay(1000);  // Delay to reduce sensor reading frequency
}

// Function to set color based on temperature
void setColorBasedOnTemperature(float temperature) {
  // Logic to set color based on temperature
  // ...
}

// Function to fade lights to a specific brightness
void setColorBasedOnTemperature(float temperature) {
  uint32_t color;

  // Adjust color based on temperature
  if (temperature < 20) {  // Cold
    color = pixels.Color(0, 0, 255);  // Blue
  } else if (temperature >= 20 && temperature <= 25) {  // Moderate
    color = pixels.Color(255, 255, 0);  // Yellow
  } else {  // Hot
    color = pixels.Color(255, 0, 0);  // Red
  }

  setAllPixelsColor(color);
}

// Function to fade lights to a specific brightness
void fadeToBrightness(int targetBrightness) {
  // Get the current color of the first pixel
  uint32_t currentColor = pixels.getPixelColor(0);
  int currentBrightness = getAverageBrightness(currentColor);

  while (currentBrightness != targetBrightness) {
    int red = (currentColor >> 16) & 0xFF;
    int green = (currentColor >> 8) & 0xFF;
    int blue = currentColor & 0xFF;

    // Scale RGB values based on currentBrightness
    red = (red * currentBrightness) / 255;
    green = (green * currentBrightness) / 255;
    blue = (blue * currentBrightness) / 255;

    setAllPixelsColor(red, green, blue);
    pixels.show();

    // Increment or decrement brightness
    currentBrightness += (currentBrightness < targetBrightness) ? 1 : -1;
    delay(FADE_INTERVAL);
  }
}
