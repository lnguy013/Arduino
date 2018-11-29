#include <FastLED.h>

#define LED_PIN     8
#define NUM_LEDS    100
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define UPDATES_PER_SECOND 100
int count = 0;
int MainRandomIcicle[8];
int TargetLEDArray [8];
int RandomLEDBlue = random8(150,256);
int i;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    fill_solid( currentPalette, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    Serial.begin(9600);
}

void loop() {
    Serial.println("Start");
    Serial.println();
    MultiIcicleLED ();
    count++;
    Serial.println(count);
    Serial.println();
    delay(random(100,5000));
}


void singleIcicleLED (){
  int RandomLEDBlue = random8();

  if (RandomLEDBlue < 100){
    RandomLEDBlue = 150;
  }
  else
  {
    RandomLEDBlue = RandomLEDBlue;
  }
  for (int i = 0; i < NUM_LEDS; i++){
      if (i == 0){
        leds[i] = CRGB(100,100,RandomLEDBlue);
        delay(random8());
      }
      else if ( i > 0 && i < NUM_LEDS){
        leds[i-1] = CRGB (0,0,0);
        leds[i] = CRGB (100,100,RandomLEDBlue);
        delay(random8());
      }
      
      FastLED.show();
    }
     delay(500);
     leds[NUM_LEDS-1] = CRGB :: Black;
     FastLED.show();
     
}

void MultiIcicleLED (){
  int RandomNumberOfIcicle = random8(1,8);
  int RandomIcicle0[8] = {12,22,35,40,53,67,82,8};
  int RandomIcicle1[8] = {18,32,37,53,65,79,88,7};
  int RandomIcicle2[8] = {12,32,35,53,53,79,82,7};
  int RandomIcicle3[8] = {18,22,37,40,65,67,88,8};
  int RandomStart = random8(4);


  // Randomly load MainRandomIcicle Array with 4 preloaded Arrays. 0-3.
  for (int n = 0 ; n < 8; n++)
  {
    if (RandomStart == 0){MainRandomIcicle[n] = RandomIcicle0[n];}
    if (RandomStart == 1){MainRandomIcicle[n] = RandomIcicle1[n];}
    if (RandomStart == 2){MainRandomIcicle[n] = RandomIcicle2[n];}
    if (RandomStart == 3){MainRandomIcicle[n] = RandomIcicle3[n];}
  }

  // set which location in the MainRandomIcicle Array to target
  // 0 to 8
  // MainRandomIcicle[TargetLEDArray[i]]
 for (int i = 0; i < RandomNumberOfIcicle; i++)
 {
    if (i == 0)
    {
     TargetLEDArray [i] = random(7);
    }
    else
    {
      TargetLEDArray[i] = random(7);
      for (int n = i; n = 0; n--)
      {
        if (TargetLEDArray[i] == TargetLEDArray [n-1])
        {
          TargetLEDArray[i] = random(7);
          n = i;
        }
      }
    }
 Serial.print(TargetLEDArray[i]);
 Serial.print(" Value of Array at ");
 Serial.println(i);
 Serial.println();
 }
 

//show LED
//show single Icicle

    Serial.print(RandomNumberOfIcicle);
    Serial.print(" Number of Icicle");
    Serial.println();

    //Pull value out of target Array Base on number of icicle
  if (RandomNumberOfIcicle == 1) {Icicle();}
  if (RandomNumberOfIcicle == 2) 
  {
    leds[MainRandomIcicle[TargetLEDArray[0]]] = CRGB (100,100,250);
    leds[MainRandomIcicle[TargetLEDArray[1]]] = CRGB (100,100,250);
  }

  for (int i = 0; i < RandomNumberOfIcicle; i++)
  {    
    Serial.print(i);
    Serial.println(" Number of cycle");
    int TempArrayValue = TargetLEDArray[i];
    Serial.print(TempArrayValue);
    Serial.println(" Location of Target Array");
    int TempValue = MainRandomIcicle[TempArrayValue];
    Serial.print(TempValue);
    Serial.println(" Value of StartingLight");
    
    if (MainRandomIcicle[TargetLEDArray[i]] == 12 ){IcicleShowUp(TempValue, 4, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 22 ){IcicleShowUp(TempValue, 6, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 35 ){IcicleShowUp(TempValue, 2, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 40 ){IcicleShowUp(TempValue, 8, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 55 ){IcicleShowUp(TempValue, 6, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 67 ){IcicleShowUp(TempValue, 7, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 82 ){IcicleShowUp(TempValue, 4, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 18) {IcicleShowDown(TempValue, 4, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 32) {IcicleShowDown(TempValue, 6, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 37) {IcicleShowDown(TempValue, 2, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 53) {IcicleShowDown(TempValue, 7, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 65) {IcicleShowDown(TempValue, 6, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 79) {IcicleShowDown(TempValue, 7, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 88) {IcicleShowDown(TempValue, 4, RandomLEDBlue);} 
    
  }

  

  
     
}

void IcicleShowUp (int startLight, int numLight, int RandomLED){
  Serial.println("IcicleShowUp");
for (int i = startLight; i < startLight+ numLight; i++){
  Serial.print(i);
  Serial.println(" Current LED Location");
      if (i == startLight){
        leds[i] = CRGB(100,100,RandomLED);
        delay(random(100,600));
      }
      else if ( i > startLight && i < startLight+ numLight){
        leds[i-1] = CRGB (0,0,0);
        leds[i] = CRGB (100,100,RandomLED);
        delay(random(100,600));
      }
      
      FastLED.show();
    }
     delay(random(100,500));
     leds[(startLight+ numLight)-1] = CRGB :: Black;
     FastLED.show();
}

void IcicleShowDown (int startLight, int numLight, int RandomLED){
   Serial.println("IcicleShowDown");
   Serial.print(startLight);
    Serial.println(" Value of StartingLight");
for (int i = startLight; i <=startLight-numLight; i--){
  Serial.print(i);
  Serial.println(" Current LED Location");
      if (i == startLight){
        leds[i] = CRGB(100,100,RandomLED);
        delay(random(100,600));
      }
      else if ( i > startLight-numLight && i < startLight){
        leds[i-1] = CRGB (0,0,0);
        leds[i] = CRGB (100,100,RandomLED);
        delay(random(100,600));
      }
      
      FastLED.show();
    }
     delay(random(100,500));
     leds[(startLight - numLight)+1] = CRGB :: Black;
     FastLED.show();
}

void MultipleIce (int NumIce)
{
  for (int n = 0 ,n > NumIce, i++)
  {
    leds[
  }
}

void Icicle ()
{
    if (MainRandomIcicle[TargetLEDArray[i]] == 12 ){IcicleShowUp(MainRandomIcicle[TargetLEDArray[i]], 4, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 22 ){IcicleShowUp(MainRandomIcicle[TargetLEDArray[i]], 6, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 35 ){IcicleShowUp(MainRandomIcicle[TargetLEDArray[i]], 2, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 40 ){IcicleShowUp(MainRandomIcicle[TargetLEDArray[i]], 8, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 55 ){IcicleShowUp(MainRandomIcicle[TargetLEDArray[i]], 6, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 67 ){IcicleShowUp(MainRandomIcicle[TargetLEDArray[i]], 7, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 82 ){IcicleShowUp(MainRandomIcicle[TargetLEDArray[i]], 4, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 18) {IcicleShowDown(MainRandomIcicle[TargetLEDArray[i]], 4, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 32) {IcicleShowDown(MainRandomIcicle[TargetLEDArray[i]], 6, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 37) {IcicleShowDown(MainRandomIcicle[TargetLEDArray[i]], 2, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 53) {IcicleShowDown(MainRandomIcicle[TargetLEDArray[i]], 7, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 65) {IcicleShowDown(MainRandomIcicle[TargetLEDArray[i]], 6, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 79) {IcicleShowDown(MainRandomIcicle[TargetLEDArray[i]], 7, RandomLEDBlue);}
    if (MainRandomIcicle[TargetLEDArray[i]] == 88) {IcicleShowDown(MainRandomIcicle[TargetLEDArray[i]], 4, RandomLEDBlue);}
}

