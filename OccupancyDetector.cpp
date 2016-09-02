#include "Arduino.h"

class OccupancyDetector {
  // class member variables initialised at startup
  int in;
  int out;
  int delayMS;

  // sensor vars
  long duration;
  long distance;

  // constructor
  public: OccupancyDetector (int inPin, int outPin, int delayMilliSeconds) {
    
    in = inPin;
    out = outPin;
    pinMode(out,OUTPUT);
    pinMode(in,INPUT);
    delayMS = delayMilliSeconds;
  }

  void Update() {
    digitalWrite(out,LOW);
    delayMicroseconds(2);
    digitalWrite(out,HIGH);
    delayMicroseconds(10);
    digitalWrite(out,LOW);
    
    duration = pulseIn(in,HIGH);
    distance = (duration/2) / 29.1;

    delay(delayMS);
  }

  int GetDistance(){
    return distance;
  }

  bool isOccupied(){
    if(distance > 0 && distance < 100){
      return true;
    } else {
      return false;
    }
  }
};
