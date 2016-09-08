#include "OccupancyDetector.cpp"
#include "LedStrip.cpp"

OccupancyDetector detector = OccupancyDetector(12, 13, 100);
LedStrip leds = LedStrip(4, 120);
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
        leds.colorWipeUntil(leds.Color(50, 50, 50), 50, 60); // White
        
        // pause
        delay(3000);
        
        
        // TODO: reverse wipe back to default state
        // leds.colorWipeUntil(leds.Color(0, 100, 0), 50, 118);
  
        leds.clear();
        leds.show();
        
        // turn on detector
        isDetecting = true;
    }  
  }
}
