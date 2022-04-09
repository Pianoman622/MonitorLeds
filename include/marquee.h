#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#include "SmoothMotion.h"

void DrawMarqueeRainbow(struct CRGB * jStrip, const int numLeds)
{
  fill_solid(jStrip, numLeds, CRGB::Black);

  static float scroll = 0.0f;
  scroll += 0.1f;
  if (scroll > 5.0)
    scroll -= 5.0;

  static byte j = 0;
  j+=4;
  byte k = j;
  CRGB c;

  for (float i = scroll; i < numLeds; i+= 5)
  {
    
    DrawPixelsNew(i, 3, c.setHue(k+=8), jStrip);
    
  }
}

void DrawMarquee(struct CRGB * jStrip, const int numLeds, CRGB color)
{
  fill_solid(jStrip, numLeds, CRGB::Black);

  static float scroll = 0.0f;
  scroll += 0.1f;
  if (scroll > 5.0)
    scroll -= 5.0;

  CRGB c;

  for (float i = scroll; i < numLeds; i+= 5)
  {
    
    DrawPixelsNew(i, 3, color, jStrip);
    
  }
}