#include "OccupancyDetector.cpp"
#include "LedStrip.cpp"

#define TRIG_PIN 13
#define ECHO_PIN 12
#define DETECTOR_DELAY 60
#define DISTANCE_RANGE 200

#define LED_PIN 8
#define NO_LEDS 50

// LED strip animation settings
#define UP_TO        25
#define SENSOR_INDEX 25
#define TEXT_START   80
#define TEXT_END     89
#define LED_DELAY    50

LedStrip leds = LedStrip(LED_PIN, NO_LEDS);

const int      BNS        = 30; // BRIGHTNESS
const uint32_t WHITE      = leds.Color(BNS, BNS, BNS);
const uint32_t FULLWHITE  = leds.Color(150, 150, 150);
const uint32_t BLACK      = leds.Color(0  , 0  , 0  );
const uint32_t GOETHE     = leds.Color(160, 200, 20 );

bool isDetecting;
bool hasDetected;

void setup() {
  Serial.begin(9600);
  
  leds.begin();
  leds.clear();
  leds.show();

  isDetecting = true;
//  leds.colorRange(3,6, WHITE);
}

void loop() {
  unsigned long currentMillis = millis();
  leds.blinkRange(currentMillis, 1, 3, 1000, WHITE, GOETHE);
  leds.fadeOutRangeFromBrightnessMillis(currentMillis, 5, 10, BNS, 2000);
//  leds.easeInRangeMillis(currentMillis, 11, 25, 2000, WHITE);
  leds.easeInRangeMillis(currentMillis, 25, 11, 2000, WHITE);
}

