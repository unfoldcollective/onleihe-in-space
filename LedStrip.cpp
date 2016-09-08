#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

// LedStrip Class wraps Adafruit_NeoPixel class to add custom animations

class LedStrip {
  Adafruit_NeoPixel leds;
  
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
    
    // Fill the dots one after the other with a color
    void colorWipe(uint32_t c, uint8_t wait) {
      for(uint16_t i=0; i<leds.numPixels(); i++) {
        leds.setPixelColor(i, c);
        leds.show();
        delay(wait);
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

    
    
};

