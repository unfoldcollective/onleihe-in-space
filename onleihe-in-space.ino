#include "OccupancyDetector.cpp"
#include "LedStrip.cpp"

OccupancyDetector detector = OccupancyDetector(12, 13, 100);
LedStrip leds = LedStrip(4, 120);

void setup() {
  Serial.begin(9600);
  
  leds.begin();  // Call this to start up the LED strip.
  leds.clear();  // turns all LEDs off...
  leds.show();   // ...but the LEDs don't actually update until you call this.
}

void loop() {
  detector.update();
  bool isOccupied = detector.isOccupied();
  bool hasDetected = detector.detect();
  
  Serial.println(isOccupied);
  Serial.println(hasDetected);
  Serial.println("***");

  if(hasDetected){
      // TODO: turn off detector
      // detector.turnOff();

      // animate leds up to level of amount
      leds.colorWipeUntil(leds.Color(50, 50, 50), 50, 60); // White
      
      // pause
      delay(3000);
      
      
      // TODO: reverse wipe back to default state
      // leds.colorWipeUntil(leds.Color(0, 100, 0), 50, 118);

      leds.clear();
      leds.show();
      // TODO: turn on detector
      // detector.turnOn();
  }  
}
