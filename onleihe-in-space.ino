#include "OccupancyDetector.cpp"
#include "LedStrip.cpp"

OccupancyDetector detector = OccupancyDetector(12, 13, 1000);
LedStrip leds = LedStrip(4, 119);

void setup() {
  Serial.begin(9600);
  
  leds.begin();  // Call this to start up the LED strip.
  leds.clear();  // turns all LEDs off...
  leds.show();   // ...but the LEDs don't actually update until you call this.
}

void loop() {
  detector.Update();
  bool isOccupied = detector.isOccupied();
  
  Serial.println(String(isOccupied));
  
  // TODO: trigger LED animation based on occupancy detected

  leds.colorWipeUntil(leds.Color(255, 255, 255), 50, 60); // White
  leds.colorWipeUntil(leds.Color(0, 255, 0), 50, 100); // Green
  
}
