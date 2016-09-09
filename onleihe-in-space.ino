#include "OccupancyDetector.cpp"
#include "LedStrip.cpp"

#define TRIG_PIN 13
#define ECHO_PIN 12
#define DETECTOR_DELAY 100

#define LED_PIN 4
#define NO_LEDS 90

// LED strip animation settings
#define UP_TO 80
#define LED_DELAY 50
#define PAUSE_DELAY 3000

OccupancyDetector detector = OccupancyDetector(ECHO_PIN, TRIG_PIN, DETECTOR_DELAY);
LedStrip leds = LedStrip(LED_PIN, NO_LEDS);

const uint32_t WHITE = leds.Color(50, 50, 50);

bool isDetecting;
bool hasDetected;

void setup() {
  Serial.begin(9600);
  
  leds.begin();  // Call this to start up the LED strip.
  leds.clear();  // turns all LEDs off...
  leds.show();   // ...but the LEDs don't actually update until you call this.

  isDetecting = true;
}

void loop() {
  if (isDetecting) {
    detector.update();
    hasDetected = detector.detect();
    
    Serial.println(hasDetected);
    Serial.println("***");
  
    if(hasDetected){
        // turn off detector
         isDetecting = false;

        // animate leds up to level of amount
        leds.colorWipeUntil(WHITE, UP_TO, LED_DELAY); // White
        
        // pause
        delay(PAUSE_DELAY);
        
        // reverse wipe back to default state
        leds.wipeOutFrom(UP_TO, LED_DELAY);
        
        // turn on detector
        isDetecting = true;
    }  
  }
}
