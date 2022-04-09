
#include <Arduino.h>
#include <FastLED.h>
#include "BluetoothSerial.h"

#include "marquee.h"
#include "comet.h"
#include "fire.h"
#include "bounce.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define numLeds 50
#define ledPin 22
#define brightness 225

BluetoothSerial SerialBT;

String message = "";
char incomingChar;

CRGB LEDs[numLeds] = {0};

int hue = 0;

void setup() {

  Serial.begin(115200);

  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  FastLED.addLeds<WS2812B, ledPin, GRB>(LEDs, numLeds);
  //FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(LEDs, NUM_LEDS);


}

BouncingBallEffect balls(numLeds, 5, 128, false);
ClassicFireEffect fire(numLeds, 5, 50, 3, 4, true, false); //int size, int cooling = 80, int sparking = 50, int sparks = 3, int sparkHeight = 4, bool breversed = true, bool bmirrored = true

CRGB color;

bool rainbowState = false;
bool ballState = false;
bool fireState = false;
bool cometState = false;
bool rCometState = false;
bool marqueeState = false;
bool rMarqueeState = false;

void clearAllStates()
{
    FastLED.clear();
    rainbowState = false;
    ballState = false;
    fireState = false;
    cometState = false;
    rCometState = false;
    marqueeState = false;
    rMarqueeState = false;
}

void loop() 
{
 //set message variable to string recieved by bluetooth 
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);
  }
// check what message is and set the corresponding state to true
  if (message == "off")
  {
    color = CRGB:: Black;
    clearAllStates();
  }

  else if (message == "Comet")
  {
    cometState = true; //DrawComet(LEDs, numLeds, CRGB::Blue);
  }

  else if (message == "rainbowComet")
  {
    rCometState = true; //DrawCometRainbow(LEDs, numLeds);
  }

  else if (message == "Marquee")
  {
    marqueeState = true; //DrawMarquee(LEDs, numLeds, CRGB::Blue);
  }

  else if (message == "rainbowMarquee")
  {
    rMarqueeState = true; //DrawMarqueeRainbow(LEDs, numLeds);
  }

  else if (message == "fire")
  {
    fireState = true; //fire.DrawFire(LEDs);
  }

  else if (message == "balls")
  {
    ballState = true; //balls.Draw(LEDs);
  }

  else if (message == "Blue")
  {
    color = CRGB:: Blue;//fill_solid(LEDs, numLeds, CRGB:: Blue);
  }

  else if (message == "Red")
  {
    color = CRGB:: Red;//fill_solid(LEDs, numLeds, CRGB:: Red);
    clearAllStates();
  }

  else if (message == "White")
  {
    color = CRGB:: White;//fill_solid(LEDs, numLeds, CRGB:: White);
    clearAllStates();
  }

  else if (message == "Gold")
  {
    color = CRGB:: Gold;//fill_solid(LEDs, numLeds, CRGB:: Gold);
    clearAllStates();
  }

  else if (message == "Rainbow")
  {
    rainbowState = true;//EVERY_N_MILLISECONDS(30) {fill_rainbow(LEDs, numLeds, hue++);}
  }
// check which state is true, then draw the coressponding LED effect
  if (fireState == true) 
  {
    fire.DrawFire(LEDs);
  }

  else if (ballState == true)
  {
    balls.Draw(LEDs);
  }

  else if (cometState == true)
  {
    DrawComet(LEDs, numLeds, color);
  }

  else if (rCometState == true)
  {
    DrawCometRainbow(LEDs, numLeds);
  }

  else if (marqueeState == true)
  {
    DrawMarquee(LEDs, numLeds, color);
  }

  else if (rMarqueeState == true)
  {
    DrawMarqueeRainbow(LEDs, numLeds);
  }

  else if (rainbowState == true)
  {
    EVERY_N_MILLISECONDS(30) {fill_rainbow(LEDs, numLeds, hue++);}
  }
 
  else if (color)
  {
    fill_solid(LEDs, numLeds, color);
  }

  else
  {
    FastLED.clear();
    clearAllStates();
  }

    FastLED.setBrightness(225);
    FastLED.delay(50);  
}


