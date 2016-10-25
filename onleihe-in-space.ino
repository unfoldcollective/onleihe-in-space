#include "OccupancyDetector.cpp"
#include "LedStrip.cpp"

#define TRIG_PIN 13
#define ECHO_PIN 12
#define DETECTOR_DELAY 60
#define DISTANCE_RANGE 200

#define LED_PIN 4
#define NO_LEDS 35

// LED strip animation settings
#define UP_TO 55
#define TEXT_START  80
#define TEXT_END    89
#define LED_DELAY 50

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
}

void loop() {
  unsigned long currentMillis = millis();

  leds.blinkRange(currentMillis, 0, 2, 1000, WHITE, GOETHE);
  
}

