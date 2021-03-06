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

    // easeIn from pixel until pixel (not index), over duration (ms), in color
    void easeInRange(int from, int until, float duration, uint32_t color){
      from--;  // subtract 1 to match LED index
      until--; 
      int distance = until-from;
      int direction = (distance > 0) - (distance < 0); // calculate sign
      ease.setDuration(duration/1000);
      ease.setTotalChangeInPosition(abs(distance));
      
      double easedPosition,t=0;
      int rounded, diff, ledIndex;
      int nSteps = 100;
      int last = -1;
   
      for(int i=0;i<=nSteps;i++) {
        easedPosition = ease.easeInOut(t);
        rounded = round(easedPosition);
        diff = rounded - last;
        
        // light up leds from last to rounded
        for (int j=1;j<=diff;j++) {
          ledIndex = from+(direction*last)+(direction*j);
          leds.setPixelColor(ledIndex, color);
        }
        leds.show();
        last = rounded;
        
        t += (duration/1000) / nSteps;
        delay(duration/nSteps);
      }
    }
    
    void fadeOutRangeFromBrightness(int from, int to, int brightness, int duration) {
      int nSteps = duration/25;
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

