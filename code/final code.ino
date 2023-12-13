#include <Adafruit_NeoPixel.h>
#include <DHT.h>

#define PIN_NEOPIXEL 6
#define NUMPIXELS    16
#define PIN_DHT      7
#define DHTTYPE      DHT22
#define PIN_PIR      2
#define LDR_PIN      A0
#define SOUND_SENSOR_PIN A1
#define BUTTON_PIN   3
#define DARK_THRESHOLD 600
#define SOUND_SAMPLES 10
#define MOTION_TIMEOUT 30000000
#define FADE_INTERVAL 100

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
DHT dht(PIN_DHT, DHTTYPE);
bool soundMode = false;
unsigned long lastMotionTime = 0;
int soundReadings[SOUND_SAMPLES];
int soundIndex = 0;
bool isFading = false;

void setup() {
  pixels.begin();
  dht.begin();
  pinMode(PIN_PIR, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(SOUND_SENSOR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Setup completed.");
}

void loop() {
  float temperature = dht.readTemperature();
  int ldrValue = analogRead(LDR_PIN);
  int pirState = digitalRead(PIN_PIR);

  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  Serial.print("PIR State: ");
  Serial.println(pirState);

  if (digitalRead(BUTTON_PIN) == LOW) {
    soundMode = !soundMode;
    isFading = false;
    Serial.print("Sound Mode: ");
    Serial.println(soundMode ? "ON" : "OFF");
    delay(200); // Anti-shake delay
  }

  uint32_t currentColor = temperatureToColor(temperature);

  if (soundMode) {
    int soundValue = analogRead(SOUND_SENSOR_PIN);
    soundReadings[soundIndex++] = soundValue;
    if (soundIndex >= SOUND_SAMPLES) soundIndex = 0;

    int averageSound = 0;
    for (int i = 0; i < SOUND_SAMPLES; i++) {
      averageSound += soundReadings[i];
    }
    averageSound /= SOUND_SAMPLES;

    int brightness = map(averageSound, 0, 1023, 0, 255);
    brightness = constrain(brightness, 0, 255);
    setPixelColorWithBrightness(currentColor, brightness);
  } else {
    if (ldrValue > DARK_THRESHOLD) {
      if (pirState == HIGH) {
        lastMotionTime = millis();
        setPixelColorWithBrightness(currentColor, 100);
        isFading = false;
        Serial.println("Motion detected - Lights ON");
      } else if (millis() - lastMotionTime > MOTION_TIMEOUT) {
        if (!isFading) {
          fadeToBrightness(10, currentColor);
          isFading = true;
          Serial.println("No motion detected - Fading to 10%");
        }
      }
    } 
    if (ldrValue <= DARK_THRESHOLD && isFading) {
      // Turning off the light when the brightness has decreased and the light intensity has increased
      pixels.clear();
      pixels.show();
      isFading = false;
      Serial.println("Light intensity increased - Turning OFF LEDs");
    } else if (ldrValue <= DARK_THRESHOLD && !isFading) {
      // High light intensity, turn off lights
      pixels.clear();
      pixels.show();
      Serial.println("High light intensity - Turning OFF LEDs");
    }
  }

  delay(1000);
}

void setColorBasedOnTemperature(float temperature, int brightness) {
  uint32_t color = temperatureToColor(temperature);
  setPixelColorWithBrightness(color, brightness);
}

void fadeToBrightness(int targetBrightness, uint32_t color) {
  int currentBrightness = getAverageBrightness();
  while (currentBrightness != targetBrightness) {
    setPixelColorWithBrightness(color, currentBrightness);
    pixels.show();
    currentBrightness += (currentBrightness < targetBrightness) ? 1 : -1;
    delay(FADE_INTERVAL);
  }
  setPixelColorWithBrightness(color, targetBrightness);
  pixels.show();
  isFading = false;
}

void setPixelColorWithBrightness(uint32_t color, int brightness) {
  uint8_t r = (uint8_t)(brightness * ((color >> 16) & 0xFF) / 100);
  uint8_t g = (uint8_t)(brightness * ((color >> 8) & 0xFF) / 100);
  uint8_t b = (uint8_t)(brightness * (color & 0xFF) / 100);

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, r, g, b);
  }
  pixels.show();
}

int getAverageBrightness() {
  uint32_t color = pixels.getPixelColor(0);
  return (int)(((color >> 16) & 0xFF) + ((color >> 8) & 0xFF) + (color & 0xFF)) / 3;
}

uint32_t temperatureToColor(float temperature) {
  const float minTemp = 10.0;
  const float maxTemp = 30.0;

  float t = (temperature - minTemp) / (maxTemp - minTemp);
  t = constrain(t, 0.0, 1.0);

  int lowR = 255, lowG = 140, lowB = 0;
  int highR = 0, highG = 191, highB = 255;

  int r = lowR + (highR - lowR) * t;
  int g = lowG + (highG - lowG) * t;
  int b = lowB + (highB - lowB) * t;

  return pixels.Color(r, g, b);
}
