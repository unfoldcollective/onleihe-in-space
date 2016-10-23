#include "OccupancyDetector.cpp"
#include "LedStrip.cpp"

#define TRIG_PIN 13
#define ECHO_PIN 12
#define DETECTOR_DELAY 60
#define DISTANCE_RANGE 200

#define LED_PIN 4
#define NO_LEDS 90

// LED strip animation settings
#define UP_TO 55
#define TEXT_START  80
#define TEXT_END    89
#define LED_DELAY 50
#define PAUSE_DELAY 10000

OccupancyDetector detector = OccupancyDetector(ECHO_PIN, TRIG_PIN, DISTANCE_RANGE, DETECTOR_DELAY);
LedStrip leds = LedStrip(LED_PIN, NO_LEDS);

const int      BNS        = 60; // BRIGHTNESS
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
//  leds.colorRange(  0,89, WHITE);
}

void loop() { 
  if (isDetecting) {
    detector.update();
    hasDetected = detector.detect();
    
    Serial.println(detector.getDistance());
    Serial.println(detector.isOccupied());  
    Serial.println(hasDetected);
    Serial.println("***");
    
    if (detector.isOccupied()) {
      leds.setPixelColor(1, GOETHE);
    } else {
      leds.setPixelColor(1, BLACK);
    }
    leds.show();    
  
    if(hasDetected){
        // turn off detector
        isDetecting = false;

        // animate leds until level of UP_TO
        leds.easeInRange(1, UP_TO, 3000, GOETHE);

        // light up text area
        leds.colorRange(TEXT_START, TEXT_END, GOETHE);
        
        // pause
        delay(PAUSE_DELAY);
        
        // fade out text area
        leds.fadeOutRangeFromBrightness(TEXT_START, TEXT_END, BNS, 1000);

        // animate leds down from UP_TO
        leds.easeInRange(UP_TO, 1, 6000, BLACK);
        
        // turn on detector
        isDetecting = true;
    }  
  }
}
