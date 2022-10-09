
#include <Arduino.h>
#include <FastLED.h>
#include "BluetoothSerial.h"

#include "marquee.h"
#include "comet.h"
#include "fire.h"
#include "bounce.h"
#include "Pacifica.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define numLeds 300
#define ledPin 22
int8_t brightness = 50;


BluetoothSerial SerialBT;

String message = "";
char incomingChar;

CRGB LEDs[numLeds] = {0};

int hue = 0;
int ghue = 0;

void setup() {

  Serial.begin(115200);

  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  FastLED.addLeds<WS2812B, ledPin, GRB>(LEDs, numLeds);
  //FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(LEDs, NUM_LEDS);

}

BouncingBallEffect balls(numLeds, 5, 128, true);
ClassicFireEffect fire(numLeds, 10, 50, 3, 4, true, true); //int size, int cooling = 80, int sparking = 50, int sparks = 3, int sparkHeight = 4, bool breversed = true, bool bmirrored = true

CRGB color;

bool rainbowState = false;
bool ballState = false;
bool fireState = false;
bool cometState = false;
bool rCometState = false;
bool marqueeState = false;
bool rMarqueeState = false;
bool pacificaState = false;
bool gradientState0 = false;
bool gradientState1 = false;
bool gradientState2 = false;
bool gradientState3 = false;
bool gradientState4 = false;
bool gradientState5 = false;
bool movementState = false;


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
    pacificaState = false;
    gradientState0 = false;
    gradientState1 = false;
    gradientState2 = false;
    gradientState3 = false;
    gradientState4 = false;
    gradientState5 = false;
    movementState = false;
}

DEFINE_GRADIENT_PALETTE( Gummy_Kids_gp ) {
    0,   8, 47,  5,
   31,  77,122,  6,
   63, 249,237,  7,
   95, 232, 51,  1,
  127, 215,  0,  1,
  159,  47,  1,  3,
  191,   1,  7, 16,
  223,  52, 22,  6,
  255, 239, 45,  1};

DEFINE_GRADIENT_PALETTE( Grand_Boucle_gp ) {
    0, 237,121,  1,
   51, 237,121,  1,
   51, 222,178,  1,
  102, 222,178,  1,
  102, 255,255,255,
  153, 255,255,255,
  153, 137,135,125,
  204, 137,135,125,
  204,  42, 38, 34,
  255,  42, 38, 34};


DEFINE_GRADIENT_PALETTE (twoColorPallete) {
  0, 255, 0, 0, // Red
  127, 255, 0, 255, // Purple
  255, 255, 0, 0, //Red
};


// Gradient palette "cool_warm_d05_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/km/tn/cool-warm-d05.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

// Gradient palette "cool_warm_d05_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/km/tn/cool-warm-d05.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

DEFINE_GRADIENT_PALETTE( cool_warm_d05_gp ) {
    0,   8, 38,180,
   51,   8, 38,180,
  102, 225,0,0,
  204, 50,  2,  6,
  255, 232,  50,  50};

DEFINE_GRADIENT_PALETTE( red_to_blue ) {
    0, 255, 0, 0,
    25, 225, 0, 0,
    100, 225, 0, 50,
    128, 50, 0, 50,
    128, 0, 0, 128,
    175, 50, 0, 106,
    255, 0, 0, 255};



DEFINE_GRADIENT_PALETTE( patriot_gp ) {
    0, 255,  0,  0,
  122, 255,  0,  0,
  132,   0, 16,255,
  255,   0, 16,255};

DEFINE_GRADIENT_PALETTE( parrot_gp ) {
    0, 126,  0,  1,
  114, 197,168, 16,
  140, 197,168, 16,
  216,   0,  2, 32,
  255,   0,  2, 32};

DEFINE_GRADIENT_PALETTE( otis_gp ) {
    0,  26,  1, 89,
  127,  17,193,  0,
  216,   0, 34, 98,
  255,   0, 34, 98};

DEFINE_GRADIENT_PALETTE( tashangel_gp ) {
    0, 133, 68,197,
   51,   2,  1, 33,
  101,  50, 35,130,
  153, 199,225,237,
  204,  41,187,228,
  255, 133, 68,197};

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

  if (message == "100%") 
  {
    brightness = 225;
  }

  if (message == "75%") 
  {
    brightness = 168;
  }

  if (message == "50%") 
  {
    brightness = 112.5;
  }

    if (message == "25%") 
  {
    brightness = 56.25;
  }

  if (message == "10") 
  {
    brightness = 22.5;
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

  else if (message == "Ocean")
  {
    pacificaState = true;
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

  else if (message == "SeaGreen")
  {
    color = CRGB:: SeaGreen;//fill_solid(LEDs, numLeds, CRGB:: Gold);
    clearAllStates();
  }

  else if (message == "Teal")
  {
    color = CRGB:: Teal;//fill_solid(LEDs, numLeds, CRGB:: Gold);
    clearAllStates();
  }

    else if (message == "Navy")
  {
    color = CRGB:: Navy;//fill_solid(LEDs, numLeds, CRGB:: Gold);
    clearAllStates();
  }

    else if (message == "Purple")
  {
    color = CRGB:: Purple;//fill_solid(LEDs, numLeds, CRGB:: Gold);
    clearAllStates();
  }

      else if (message == "Green")
  {
    color = CRGB:: Green;//fill_solid(LEDs, numLeds, CRGB:: Gold);
    clearAllStates();
  }

      else if (message == "Gradient0")
  {
    gradientState0 = true;
  }

    else if (message == "Gradient1")
  {
    gradientState1 = true;
  }

    else if (message == "Gradient2")
  {
    gradientState2 = true;
  }

    else if (message == "Gradient3")
  {
    gradientState3 = true;
  }

    else if (message == "Gradient4")
  {
    gradientState4 = true;
  }

    else if (message == "Gradient5")
  {
    gradientState5 = true;
  }

  else if (message == "Rainbow")
  {
    rainbowState = true;//EVERY_N_MILLISECONDS(30) {fill_rainbow(LEDs, numLeds, hue++);}
  }

  else if (message == "Movement on")
  {
    movementState = true;
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
    EVERY_N_MILLISECONDS(15){ DrawCometRainbow(LEDs, numLeds); }
  }

  else if (marqueeState == true)
  {
    DrawMarquee(LEDs, numLeds, color);
  }

  else if (rMarqueeState == true)
  {
    EVERY_N_MILLISECONDS(55){ DrawMarqueeRainbow(LEDs, numLeds);}
  }

  else if (rainbowState == true)
  {
    EVERY_N_MILLISECONDS(15) {fill_rainbow(LEDs, numLeds, hue++);}
  }

  else if (pacificaState == true)
  {
      EVERY_N_MILLISECONDS( 20) {
    pacifica_loop(numLeds, LEDs);
    FastLED.show();}
  }
 
  else if (color)
  {
    fill_solid(LEDs, numLeds, color);
  }

  else if (gradientState0 == true)
    {
      CRGBPalette16 myPal = Gummy_Kids_gp;
      fill_palette(LEDs+89, 211, ghue, 255/211, myPal, 255, LINEARBLEND);
      if (movementState == true) {EVERY_N_MILLISECONDS(30) {ghue++;}}
    }

  else if (gradientState1 == true)
  {
    CRGBPalette16 myPal = Grand_Boucle_gp; 
    fill_palette(LEDs+89, 211, ghue, 255/211, myPal, 255, LINEARBLEND);
    if (movementState == true) {EVERY_N_MILLISECONDS(30) {ghue++;}}
  }

  else if (gradientState2 == true)
  {
    CRGBPalette16 myPal = cool_warm_d05_gp; 
    fill_palette(LEDs+89, 211, ghue, 255/211, myPal, 255, LINEARBLEND);
    if (movementState == true) {EVERY_N_MILLISECONDS(30) {ghue++;}}
  }

  else if (gradientState3 == true)
  { 
    CRGBPalette16 myPal = parrot_gp; 
    fill_palette(LEDs+89, 211, ghue, 255/211, myPal, 255, LINEARBLEND);
    if (movementState == true) {EVERY_N_MILLISECONDS(30) {ghue++;}}
  }

  else if (gradientState4 == true)
  {
    CRGBPalette16 myPal = red_to_blue; 
    fill_palette(LEDs+89, 211, ghue, 255/211, myPal, 255, LINEARBLEND);
    if (movementState == true) {EVERY_N_MILLISECONDS(30) {ghue++;}}
  }

  else if (gradientState5 == true)
  {
    CRGBPalette16 myPal = PartyColors_p; 
    fill_palette(LEDs+89, 211, ghue, 255/211, myPal, 255, LINEARBLEND);
    if (movementState == true) {EVERY_N_MILLISECONDS(30) {ghue++;}}
  }

  else
  {
    FastLED.clear();
    clearAllStates();
  }

    FastLED.setBrightness(brightness);
    FastLED.delay(10);  

}