#include "Arduino.h"
#include <TransparentQueueArray.h>


class OccupancyDetector {
  private:
    // class member variables
    int inPin;
    int outPin;
    int delayMS;
    long duration;
    long distance;

    // keep this to powers of 2 {2,4,8,16} etc because of the way QueueArray grows
    int QUEUE_SIZE = 8;
    TransparentQueueArray <bool> occupationQueue;
  
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

    // return whether occupancy has been continuously detected 
    // for the duration of [delayMS]*[QUEUE_SIZE] ms
    bool detect(){
      // enqueue current occupation state
      occupationQueue.enqueue(isOccupied());
      if(occupationQueue.count() == QUEUE_SIZE){
        occupationQueue.dequeue();
      }

//      for (int i = 0; i <= occupationQueue.count(); i++){
//        Serial.print(occupationQueue.getContents()[i]);
//      }
//      Serial.println();
      

      // check if last n detections where occupied (queue is full of true)      
      bool detected = true;
      for (int i = 0; i < occupationQueue.count(); i++){
        if(occupationQueue.getContents()[i] == false){
          detected = false;
        }
      }
      return detected;
    }
};
