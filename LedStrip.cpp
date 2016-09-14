#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "CubicEase.h"

// LedStrip Class wraps Adafruit_NeoPixel class to add custom animations
class LedStrip {
  private:
    Adafruit_NeoPixel leds;
    CubicEase ease;
  
  public:
    LedStrip (int ledPin, int ledCount) {
      leds = Adafruit_NeoPixel(ledCount, ledPin, NEO_GRB + NEO_KHZ800);
    }

    // Sets all LEDs to off, but DOES NOT update the display;
    // call leds.show() to actually turn them off after this.
    void clear()
    {
      for (int i=0; i<leds.numPixels(); i++)
      {
        leds.setPixelColor(i, 0);
      }
    }

    void begin () {
      leds.begin();
    }

    void show () {
      leds.show();
    }

    uint32_t Color(int r, int g, int b){
      return leds.Color(r, g, b);
    }

    void setPixelColor (int pixelIndex, uint32_t color) {
      leds.setPixelColor(pixelIndex, color);
    }

    // easeIn until pixel number (not index), over duration (ms), in color
    void easeInUntil(int until, float duration, uint32_t color){
      until--; // subtract 1 to match LED index
      ease.setDuration(duration/1000);
      ease.setTotalChangeInPosition(until);
      
      double easedPosition,t=0;
      int rounded, diff;
      int nSteps = 100;
      int last = 0;
   
      for(int i=1;i<=nSteps;i++) {
        easedPosition = ease.easeInOut(t);
        rounded = round(easedPosition);
        diff = rounded - last;
        
        // light up leds from last to rounded
        // start from j=1 to skip led at index 0 with broken green channel
        for (int j=1;j<=diff;j++) {
          leds.setPixelColor(last + j, color);
        }
        leds.show();
        last = rounded;
        
        t += (duration/1000) / nSteps;
        delay(duration/nSteps);
      }
    }

    // easeOut from pixel number (not index), over duration (ms), in color
    void easeOutFrom(int from, float duration, uint32_t color){
      ease.setDuration(duration/1000);
      ease.setTotalChangeInPosition(from);
      
      double easedPosition,t=0;
      int rounded, diff, current;
      int nSteps = 100;
      int last = from;
   
      for(int i=0;i<=nSteps;i++) {
        easedPosition = ease.easeInOut(t);
        rounded = round(easedPosition);
        diff = rounded - last;
        current = from - rounded;
       
        // turn off leds from current to last
        for (int j=1;j<=diff;j++) {
          leds.setPixelColor(current + j, color);
        }
        leds.show();
        last = rounded;
        
        t += (duration/1000) / nSteps;
        delay(duration/nSteps);
      }
    }

    // Fill the dots one after the other with a color until specified number
    void colorWipeUntil(uint32_t c, int until, uint8_t wait) {
      for(uint16_t i=0; i<until; i++) {
        leds.setPixelColor(i, c);
        leds.show();
        delay(wait);
      }
    }
    
    void wipeOutFrom(int from, uint8_t wait) {
      for(int i=from; i>0; i--) {
        leds.setPixelColor(i, leds.Color(0,0,0));
        leds.show();
        delay(wait);
      }
      leds.clear();
      leds.show();
    }

    // Fill the dots one after the other with a color
    void colorWipe(uint32_t c, uint8_t wait) {
      for(uint16_t i=0; i<leds.numPixels(); i++) {
        leds.setPixelColor(i, c);
        leds.show();
        delay(wait);
      }
    }

    void colorRange(int from, int to, uint32_t c) {
      for (int i=from; i <= to; i++) {
        leds.setPixelColor(i, c);
      }
      leds.show();
    }

    void fadeOutRangeFromBrightness(int from, int to, int brightness, int duration) {
      int nSteps = 50;
      float dBrightness = 1.0*brightness/nSteps;
      int fadeDelay = round(1.0*duration/nSteps);
      int newBrightness;
      
      for (int j=1; j <= nSteps; j++) {
        newBrightness = round(brightness - (j * dBrightness));
        for (int i=from; i <= to; i++) {
          leds.setPixelColor(i, leds.Color(newBrightness,newBrightness,newBrightness));
        }
        leds.show();
        delay(fadeDelay);
      }

    }
};

