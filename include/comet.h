#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#include "SmoothMotion.h"

void DrawCometRainbow(CRGB* jStrip, int NUM_LEDS)
{
    const byte fadeAmt = 128;
    const int cometSize = 1;
    const int deltaHue  = 4;
    
    static byte hue = HUE_RED;
    static int iDirection = 1;
    static int iPos = 0;

    hue += deltaHue;
    CRGB c;

    iPos += iDirection;
    if (iPos == (NUM_LEDS - cometSize) || iPos == 0)
        iDirection *= -1;
    
    for (int i = 0; i < cometSize; i++)
        // g_LEDs[iPos + i].setHue(hue);
        DrawPixelsNew(iPos + i, 3, c.setHue(hue), jStrip);
    
    // Randomly fade the LEDs
    for (int j = 0; j < NUM_LEDS; j++)
        if (random(10) > 5)
            jStrip[j] = jStrip[j].fadeToBlackBy(fadeAmt);  

    //delay(30);
}

void DrawComet(CRGB* jStrip, int NUM_LEDS, CRGB color)
{
    const byte fadeAmt = 128;
    const int cometSize = 1;

    static int iDirection = 1;
    static int iPos = 0;

    iPos += iDirection;
    if (iPos == (NUM_LEDS - cometSize) || iPos == 0)
        iDirection *= -1;
    
    for (int i = 0; i < cometSize; i++)
        // g_LEDs[iPos + i].setHue(hue);
        DrawPixelsNew(iPos + i, 3, color, jStrip);
            
    // Randomly fade the LEDs
    for (int j = 0; j < NUM_LEDS; j++)
        if (random(10) > 5)
            jStrip[j] = jStrip[j].fadeToBlackBy(fadeAmt);  

    //delay(30);
}
