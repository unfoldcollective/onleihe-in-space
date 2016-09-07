#include "Arduino.h"

class OccupancyDetector {
  private:
    // class member variables
    int inPin;
    int outPin;
    int delayMS;
    long duration;
    long distance;

  
  public: 
    // constructor
    OccupancyDetector (int echoPin, int trigPin, int delayMilliSeconds) {
      inPin = echoPin;
      outPin = trigPin;
      pinMode(outPin,OUTPUT);
      pinMode(inPin,INPUT);
      delayMS = delayMilliSeconds;
    }
  
    void update() {
      digitalWrite(outPin,LOW);
      delayMicroseconds(2);
      digitalWrite(outPin,HIGH);
      delayMicroseconds(10);
      digitalWrite(outPin,LOW);
      
      duration = pulseIn(inPin,HIGH);
      distance = (duration/2) / 29.1;
  
      delay(delayMS);
    }
  
    int getDistance(){
      return distance;
    }
  
    bool isOccupied(){
      return distance > 0 && distance < 100;
    }
};
