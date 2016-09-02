#include "OccupancyDetector.cpp"

OccupancyDetector detector(12, 13, 1000);

void setup() {
  Serial.begin(9600);
}

void loop() {
  detector.Update();
  int dis = detector.GetDistance();
  bool isOccupied = detector.isOccupied();
  Serial.println(String(dis));
  Serial.println(String(isOccupied));
}
