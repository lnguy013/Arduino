#include <FastLED.h> // include the FastLED libary into code

//Declare Spectrume Shield pin connections variable 
#define STROBE 4  // Set STROBE to PIN 4
#define RESET 5   // Set RESET to PIN 5
#define DC_One A0 // Set Signal one to Analog to A0
#define DC_Two A1 // Set Signal two to Analog to A1
#define Next_Board A2 // Set Signal out to pin 13

//Declare Variable for Arduino card and LED
#define LED_TYPE WS2812B // Define the type of LED chip we are using (WS2812B)
#define COLOR_ORDER GRB  // Define the type of color the LED will use (Green , Red, Blue)
#define LED_PIN_1 8      // Define first of the LED output signal (PIN 8)
#define LED_PIN_2 9      // Define second of the LED output signal (PIN 9)
#define LED_PIN_3 10     // Define third of the LED output signal (PIN 10)
#define LED_PIN_4 11
#define LED_PIN_5 12
#define NUM_LEDS_1 144     // Define the number of LED we using per strip (144 LEDs)
#define NUM_LEDS_2 110     // Define the number of LED we using on another string (144 LEDs)
#define NUM_LEDS_3 70
#define BRIGHTNESS 64    // Define the brightness of the LED we going to do (0-255)

#define NSAMPLES 64 // Define number of samples use for different function
#define UPDATE_PER_SECOND 100 
#define Rows  25 // Define number of rows to graph
#define Columns 7 // Define number of columns to graph
#define maxsteps 16 // max number of steps for cases check
//#define Graph Rows*Columns
char GraphArray[25];
#define NumRing 6
#define RING_MAX_PIXELS 26
#define RING_MIN_PIXELS 8

CRGB leds1[NUM_LEDS_1]; // define strip one name leds1
CRGB leds2[NUM_LEDS_1]; // define strip two name leds2
CRGB leds3[NUM_LEDS_2];
CRGB leds4[NUM_LEDS_2];
CRGB leds5[NUM_LEDS_3];

/*
 * Initialize integer veriable
 */
int freq_amp; // Define integer value to be used as indicator which frequency to target
int Frequencies_One_Average[Columns]; // Define array to store frequency value for analog 1 to be average
int Frequencies_Two_Average[Columns]; // Define array to store frequency value for analog 2 to be average 
int Frequencies_One [Columns]; // Define array to store frequency value for analog 1
int Frequencies_Two [Columns]; // Define array to store frequency value for analog 2
int Frq1 = 0; // Define where Frequency 1 is stored in array
int Frq2 = 1; // Define where Frequency 2 is stored in array
int Frq3 = 2; // Define where Frequency 3 is stored in array
int Frq4 = 3; // Define where Frequency 4 is stored in array
int Frq5 = 4; // Define where Frequency 5 is stored in array
int Frq6 = 5; // Define where Frequency 6 is stored in array
int Frq7 = 6; // Define where Frequency 7 is stored in array
int bufferValue = 120; // Define cut off noise value
int tempFreq = 0; // Define Temp Variable to check each frequncy
int tempBlank = 0; // Define Temp Variable that is counting blanks for graph
char tempChar = "" ; // Define Temp Veriable to store character
int wheel_speed = 2;
int NumberofMaxLED = 0 ;
int step = -1;
int maxSteps = 16;
int center = 0; // Define Variable to calculate center of the strip
int peakspersec = 0;
int peakcount = 0;
int decay = 0; // HOW MANY MS BEFORE ONE LIGHT DECAY
int decay_check = 0;
uint8_t colour;
uint8_t myfade = 255; // Define Variable for fading affect
unsigned int sample;
unsigned int samplearray[NSAMPLES];
unsigned long samplesum = 0;
unsigned int sampleavg = 0;
unsigned long oldtime = 0;
unsigned long newtime = 0;
int POT_PIN = 100;
int samplecount = 0;
int k = 255 ; // k constant for spiral color
long react = 0;
long old_react = 0;
long pre_react =0; // New spike conversion

byte RINGS[NumRing][RING_MAX_PIXELS] = {
  
  {104, 105, 106, 107, 108, 109,110, 103}, // 8
  {91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 89,90}, // 14
  {74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 71, 72,73}, // 18
  {54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69,70,51, 52,53},//20
  {31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,27,28,29,30},//24
  {6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,1,2,3,4,5}//26
};
byte RING_SIZES[NumRing] = {8, 14, 18, 20, 24, 26};

unsigned long startMillis = 0;


int PixelArray [NumRing] = {26,24,20,18,14,8};
int Ring1[26] = {6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,1,2,3,4,5};
int Ring2[24] = {31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,27,28,29,30};
int Ring3[20] = {54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69,70,51, 52,53};
int Ring4[18] = {74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 71, 72,73};
int Ring5[14] = {91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 89,90};
int Ring6[8] = {104, 105, 106, 107, 108, 109,110, 103};
int animation = 0;

CRGB Scroll(int pos) {
  CRGB color (0,0,0);
  if(pos < 85) {
    color.g = 0;
    color.r = ((float)pos / 85.0f) * 255.0f;
    color.b = 255 - color.r;
  } else if(pos < 170) {
    color.g = ((float)(pos - 85) / 85.0f) * 255.0f;
    color.r = 255 - color.g;
    color.b = 0;
  } else if(pos < 256) {
    color.b = ((float)(pos - 170) / 85.0f) * 255.0f;
    color.g = 255 - color.b;
    color.r = 1;
  }
  return color;
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Send data to 115200 serial port.
                        // Use Serial port to troubleshoot issues
  // Set spectrum Shield Pin Config. 
  // Initialization of Shield 
  pinMode(STROBE, OUTPUT); //Set this Pin to output on or off signal to spectrum shield card
  pinMode(RESET, OUTPUT); //Set this Pin to output
  pinMode(DC_One, INPUT); //This is Analog to Digital Signal One, This will be an input value coming from Audio Source
  pinMode(DC_Two, INPUT); //This is Analog to Digital  Signal two, this will be an input value coming from Audio Source
  pinMode(Next_Board, OUTPUT);
  digitalWrite(STROBE, HIGH); //initialize Strobe to HIGH, start fresh each time we plug in
  digitalWrite(RESET, HIGH); //initialize RESET pin to HIGH, start fresh each time we plug in

  /*
   *LED Strip Initialization
   *We will have a delay for power safety
   *Make sure all LED are turned off (BLACK)
   */
   delay(3000); // Power-up safety delay for 3000milisecond
   FastLED.addLeds<LED_TYPE, LED_PIN_1, COLOR_ORDER>(leds1, NUM_LEDS_1).setCorrection(TypicalLEDStrip); //Set Strip 1 to typical type
   FastLED.addLeds<LED_TYPE, LED_PIN_2, COLOR_ORDER>(leds2, NUM_LEDS_1).setCorrection(TypicalLEDStrip); //Set Strip 2 to typical type
   FastLED.addLeds<LED_TYPE, LED_PIN_3, COLOR_ORDER>(leds3, NUM_LEDS_2).setCorrection(TypicalLEDStrip); 
   FastLED.addLeds<LED_TYPE, LED_PIN_4, COLOR_ORDER>(leds4, NUM_LEDS_2).setCorrection(TypicalLEDStrip);
   FastLED.addLeds<LED_TYPE, LED_PIN_5, COLOR_ORDER>(leds5, NUM_LEDS_3).setCorrection(TypicalLEDStrip);  
   FastLED.setBrightness ( BRIGHTNESS); // Set LED Brightness to value set in define

   //Reset LED strip to black 
   for (int i = 0 ; i<NUM_LEDS_1; i++) // for loop start at 0 and increment by 1. from zero to make led number per strip
   {
    leds1 [i] = CRGB :: Black; // change the specific led in the leds1 array to black
    leds2 [i] = CRGB :: Black;

   }
   for ( int n = 0 ; n<NUM_LEDS_2;n++)
   {
    leds3 [n] = CRGB :: Black;
    leds4 [n] = CRGB :: Black;
   }
   fill_solid(leds5, NUM_LEDS_3, CRGB:: Black);
   // after all memory is set to black we then show it on the strip
   FastLED.show(); // show the result of the for loop above
   delay(50); // delay by 50 to let system settle down

   //Initialize Spectrum Analyzers
   digitalWrite(STROBE, LOW); // Pull down 
   delay(1);
   digitalWrite(RESET, HIGH); // Reset card
   delay(1);
   digitalWrite(STROBE, HIGH); // Pull up
   delay(1);
   digitalWrite(STROBE, LOW); // Pull down
   delay(1);
   digitalWrite(RESET, LOW); // Reset low make sure we start at zero
   
   
}

void loop() {
  // put your main code here, to run repeatedly:
  Read_Frequencies_7(); // Pull and store analog values sample 7 signal of each input avaerage it out
  //Read_Frequencies_14(); // Pull and store analog vlues sample 14 signals. Must change Columns value to handle  14
  Serial_TroubleShoot (); // Function to be enabled to troubleshoot
 // analogWrite (Next_Board, 100);
  /*fill_solid(leds5, NUM_LEDS_3, CRGB :: Purple);
  FastLED.show();
  delay(50);
  fill_solid(leds5, NUM_LEDS_3, CRGB :: Black);
  FastLED.show();
  delay(1);
  /**/
  if((Frequencies_One[0]+Frequencies_One[1]+Frequencies_One[2]+Frequencies_One[3]+Frequencies_One[4]+Frequencies_One[5]+Frequencies_One[6])/7>=2){
  Main_LED_Show(Frequencies_One[0],Frequencies_One[1], Frequencies_One[2], Frequencies_One[3], Frequencies_One[4],Frequencies_One[5],Frequencies_One[6]);
  }
  else{
   for (int i = 0 ; i<NUM_LEDS_1; i++) // for loop start at 0 and increment by 1. from zero to make led number per strip
   {
    leds1 [i] = CRGB :: Black; // change the specific led in the leds1 array to black
    leds2 [i] = CRGB :: Black; // change the specific led to black

   }
   for (int n = 0; n <NUM_LEDS_2; n++)
   {
    leds3 [n] = CRGB :: Black; 
    leds4 [n] = CRGB :: Black;
   }
   fill_solid(leds5, NUM_LEDS_3, CRGB:: Black);
   // after all memory is set to black we then show it on the strip
   FastLED.show(); // show the result of the for loop above
   delay(50); // delay by 50 to let system settle down
  }
  /**/

}


/*************Pull frquencies from Spectrum Shield****************/
void Read_Frequencies_7(){
 /*
  * initialize for loop from 1 to 7 to pull analog signal from both analog 1 and 2
  * Store the value into an array to be call upon later
  * 
  */
 for (int n = 0; n <Columns; n++) 
 {
  digitalWrite(STROBE, HIGH);
  digitalWrite(STROBE, LOW);
  delayMicroseconds (1000);
  Frequencies_One[n] = analogRead(DC_One); // Read and store signal 1 to n position of array
  Frequencies_Two[n] =  analogRead(DC_Two);
  /*Serial.print("Analog 1: ");
  Serial.println(Frequencies_One[n]);
  Serial.print("Analog 2: ");
  Serial.println(Frequencies_Two[n]);/**/
  
  if(Frequencies_One[n] < bufferValue) Frequencies_One[n] = 0; // any signal less than bufferValue consider noise and set to zero
  if(Frequencies_Two[n] < bufferValue) Frequencies_Two[n] = 0; // any signal less than bufferValue consider noise and set to zero

  Frequencies_One[n] = constrain(Frequencies_One[n], 0, 1023); // constrain the value from going to low or too high. 
  Frequencies_One[n] = map(Frequencies_One [n] , 0, 1023, 0 , Rows); // mapping the fr
  
   
  Frequencies_Two[n] = constrain(Frequencies_Two[n], 0, 1023); // constrain the value from going to low or too high. 
  Frequencies_Two[n] = map(Frequencies_Two [n] , 0, 1023, 0 , Rows); // mapping the fr

  Frequencies_One [n] = ((Frequencies_One [n] + Frequencies_Two [n] ));
  
  //Serial.println(Frequencies_One[n]);
 }
}


/*************Pull frquencies from Spectrum Shield****************/
void Read_Frequencies_14(){
 /*
  * initialize for loop from 1 to 14 to pull analog signal from both analog 1 and 2
  * Store the value into an array to be call upon later
  * 
  */
 for (int n = 0; n <Columns; n++) 
 {
  digitalWrite(STROBE, HIGH);
  digitalWrite(STROBE, LOW);
  delayMicroseconds (1000);
  Frequencies_One[n] = analogRead(DC_One); // Read and store signal 1 to n position of array
  if(Frequencies_One[n] < bufferValue) Frequencies_One[n] = 0; // any signal less than bufferValue consider noise and set to zero
  Frequencies_One[n] = constrain(Frequencies_One[n], 0, 1023); // constrain the value from going to low or too high. 
  Frequencies_One[n] = map(Frequencies_One [n] , 0, 1023, 0 , Rows); // mapping the fr
  n++;
  Frequencies_One[n] =  analogRead(DC_Two);
  if(Frequencies_One[n] < bufferValue) Frequencies_One[n] = 0; // any signal less than bufferValue consider noise and set to zero
  Frequencies_One[n] = constrain(Frequencies_One[n], 0, 1023); // constrain the value from going to low or too high. 
  Frequencies_One[n] = map(Frequencies_One [n] , 0, 1023, 0 , Rows); // mapping the fr
  
  //Serial.println(Frequencies_One[n]);
 }
}

void Serial_TroubleShoot (){
  /*
   * Function is used to output signal value to serial monitor
   * Tester can use this for troubleshooting
   */

 Serial.println("----New Graph-------"); // Start new section to be easily identify for troubleshooting
 Serial.println("--------------------"); 
 for (int n = 0;n<Columns; n++){ // For loop start from 0 to Columns value 
  tempFreq = Frequencies_One[n];
  Serial.print(n); // print the value of the columns
  Serial.print("|");
  Serial.println(tempFreq); // print value of the frequencies
 }
 Serial.println("--------------------");
 Serial.println("----End Graph-------"); // To identify end of the graph section
 Serial.println("");
 Serial.println(""); // Spacing to make easier to see to identify start of new section
}

void Main_LED_Show (int f1, int f2, int f3,int f4,  int f5, int f6, int f7){
  int Red = random8();
  int Blue = random8();
  int Green = random8 ();
  int LedUse = constrain(f3, 0, 20); // Constrain the value of Number of LED between 0 to 20
  int TempBright = map(f4, 0, 20, f5, 155);
  int tempDelay = map(f2, 0, 20, 10, 50);
  FastLED.setBrightness(TempBright);
  
  NumberofMaxLED = NUM_LEDS_1/10;
  NumberofMaxLED = constrain(NumberofMaxLED, 0, 15);
  LedUse = map(f3, 0, 20, 0, NumberofMaxLED); // map number of LED can be used to from 0 to NumberofMaxLED LEDs per call

  EVERY_N_MILLISECONDS(1000){
    peakspersec = peakcount;
    peakcount = 0;
  }
  soundmems (f5);
  EVERY_N_MILLISECONDS (20){
    rippled();
  }

//if (f5 >= 0) {
  Serial.print("Check LEDS 5 :");
  Serial.println(f5);
      convertDouble(f2, NUM_LEDS_3);
      if (react > old_react ) { Flash_1(react, NUM_LEDS_3);}
      /*doubleRainbow(NUM_LEDS_3);
      k = k - wheel_speed; // SPEED OF COLOR WHEEL
       if (k < 0) // RESET COLOR WHEEL
       {k = 255;}

       // REMOVE LEDs
        decay_check++;
        if (decay_check > decay)
        {
          decay_check = 0;
            if (react > 0)
                react--;
         }/**/
      //}   /**/
  if (f6 > 10){Sparkles_tube(f6, NUM_LEDS_1);}
  
  
  if(f3 >= 1 ){Sparkles_dome(f7,NUM_LEDS_2 );}
  //else if (f1 >= 7) { VuMeter_RainBow (f1);}
  //else if (f1 >= 7&& f1 <10) {Flash (f1, NUM_LEDS_2);}
  //else {Sparkles_dome(f1,NUM_LEDS_2);}
  

  FastLED.show();
  delay(tempDelay);
  
}

void Flash_1 (int Reaction, int NumLED){
  Serial.print("Led Strip use: ");
  Serial.println(NumLED);
   if (NumLED == NUM_LEDS_3){
      fill_solid(leds5,NumLED, CRGB::Aquamarine);
      FastLED.show();
      delay(Reaction);
      fill_solid(leds5, NumLED, CRGB :: Black);
   }
   else if (NumLED == NUM_LEDS_2) {
      fill_solid(leds3,NumLED, CRGB::Aquamarine);
      fill_solid(leds4,NumLED, CRGB::Aquamarine);
      FastLED.show();
      delay(Reaction);
      fill_solid(leds3, NumLED, CRGB :: Black);
      fill_solid(leds4, NumLED, CRGB :: Black);
   }
      else if (NumLED == NUM_LEDS_1) {
      fill_solid(leds3,NumLED, CRGB::Pink);
      fill_solid(leds4,NumLED, CRGB::Pink);
      FastLED.show();
      delay(Reaction);
      fill_solid(leds3, NumLED, CRGB :: Black);
      fill_solid(leds4, NumLED, CRGB :: Black);
   }
}

void Flash_2 (int Reaction, int NumLED){
  fill_solid(leds3, NumLED, CRGB:: Black);
  fill_solid(leds4, NumLED, CRGB:: Black);
  FastLED.show();
  delay(50);
  fill_solid(leds3, NumLED, Scroll((Reaction*256/50+k)%256));
  fill_solid(leds4, NumLED, Scroll((Reaction*256/50+k)%256));
}

void Sparkles_tube (int HiFreq, int NumLED){
  int TempRed = random8();
  int TempGreen = random8();

  
  for (int i = 0; i <= (HiFreq%2)+2; i++)
  {
    //leds1[random16(NUM_LEDS_1+i)] += CRGB(TempRed,TempGreen,255);
    leds1[constrain(random16(NumLED+i),0,NumLED)] += Scroll(((i+HiFreq)*256/(50)+k)%256);;
    leds2[constrain(random16(NumLED+i),0,NumLED)] += Scroll(((i+HiFreq)*256/(50)+k)%256);;
  } 
}

void Sparkles_dome (int HiFreq, int NumLED){
  int TempRed = random8();
  int TempGreen = random8();

  if (NumLED == NUM_LEDS_2){
  for (int i = 0; i <= (HiFreq%2)+2; i++)
  {
    //leds1[random16(NUM_LEDS_1+i)] += CRGB(TempRed,TempGreen,255);
    leds3[constrain(random16(NumLED+i),0,NumLED)] += CRGB(TempRed,TempGreen,255);
    leds4[constrain(random16(NumLED+i),0,NumLED)] += CRGB(TempRed,TempGreen,255);
  } 
  }
  else if (NumLED == NUM_LEDS_3){
    for (int i = 0; i <= (HiFreq%2)+2; i++)
  {
    //leds1[random16(NUM_LEDS_1+i)] += CRGB(TempRed,TempGreen,255);
    leds5[constrain(random16(NumLED+i),0,NumLED)] += CRGB(TempGreen,TempRed,255);
    //leds4[constrain(random16(NumLED+i),0,NumLED)] += CRGB(TempRed,TempGreen,255);
  } 
  }
  else if (NumLED == NUM_LEDS_1){
    for (int i = 0; i <= (HiFreq%2)+2; i++)
  {
    //leds1[random16(NUM_LEDS_1+i)] += CRGB(TempRed,TempGreen,255);
    leds1[constrain(random16(NumLED+i),0,NumLED)] += CRGB(TempGreen,TempRed,255);
    leds2[constrain(random16(NumLED+i),0,NumLED)] += CRGB(TempRed,TempGreen,255);
  } 
  }
}
void rippled() {

  fadeToBlackBy(leds1, NUM_LEDS_1, 64);                          // 8 bit, 1 = slow, 255 = fast
  fadeToBlackBy(leds2, NUM_LEDS_1, 64);
  fadeToBlackBy(leds3, NUM_LEDS_2, 64);
  fadeToBlackBy(leds4, NUM_LEDS_2, 64);
  fadeToBlackBy(leds5, NUM_LEDS_3, 64);
  switch (step) {

    case -1:                                                  // Initialize ripple variables.
      center = random(NUM_LEDS_1);
      colour = (peakspersec*10) % 255;                        // More peaks/s = higher the hue colour.
      step = 0;
      break;

    case 0:
      leds1[center] = CHSV(colour, 255, 255);                  // Display the first pixel of the ripple.
      leds2[center] = CHSV(colour, 255, 255); 
      step ++;
      break;

    case maxsteps:                                            // At the end of the ripples.
      // step = -1;
      break;

    default:                                                  // Middle of the ripples.
      leds1[(center + step + NUM_LEDS_1) % NUM_LEDS_1] += CHSV(colour, 255, myfade/step*2);       // Simple wrap from Marc Miller.
      leds1[(center - step + NUM_LEDS_1) % NUM_LEDS_1] += CHSV(colour, 255, myfade/step*2);
      leds2[(center + step + NUM_LEDS_1) % NUM_LEDS_1] += CHSV(colour, 255, myfade/step*2);       // Simple wrap from Marc Miller.
      leds2[(center - step + NUM_LEDS_1) % NUM_LEDS_1] += CHSV(colour, 255, myfade/step*2);

      step ++;                                                // Next step.
      break;  
  } // switch step
  
} // ripple()

void soundmems(int ValueTemp) {                                                  // Rolling average counter - means we don't have to go through an array each time.
  newtime = millis();
  
  int tmp = 0;
  tmp= ValueTemp - 512;
 
  sample = abs(tmp);

  int potin = map(POT_PIN, 0, 1023, 0, 60);

  samplesum = samplesum + sample - samplearray[samplecount];        // Add the new sample and remove the oldest sample in the array 
  sampleavg = samplesum / NSAMPLES;                                 // Get an average
  samplearray[samplecount] = sample;                                // Update oldest sample in the array with new sample
  samplecount = (samplecount + 1) % NSAMPLES;                       // Update the counter for the array

  if (newtime > (oldtime + 200)) 
  {
    fill_solid(leds1, NUM_LEDS_1, CRGB :: Black);
    fill_solid(leds2, NUM_LEDS_1, CRGB :: Black);
    fill_solid(leds3, NUM_LEDS_2, CRGB :: Black);
    fill_solid(leds4, NUM_LEDS_2, CRGB :: Black);
    fill_solid(leds5, NUM_LEDS_3, CRGB :: Black);
    FastLED.show();             // Turn the LED off 200ms after the last peak.
  }

  if ((sample > (sampleavg + potin)) && (newtime > (oldtime + 60)) ) { // Check for a peak, which is 30 > the average, but wait at least 60ms for another.
    step = -1;
    peakcount++;
    FastLED.show();
    oldtime = newtime;
  }
}


void RingAnimation_both (int RedC,int GreenC, int BlueC, int animation){
  int ArrayNumber = 0;
  int Column = 0;
  int Reaction = 50;

  for (int m = 1; m <= NumRing; m++){
   ArrayNumber = PixelArray[m-1];
   Serial.print("Pixel Up: ");
   Serial.println(ArrayNumber);
   for (int n = Column; n < ArrayNumber+Column; n++){
    //Serial.println("for loop");
    leds3 [n] = CRGB (RedC,GreenC,BlueC);
   }
   FastLED.show();
   delay(Reaction);
   for (int i = Column; i < ArrayNumber+Column; i++){
    leds3 [i] = CRGB :: Black;
   }
   Column +=ArrayNumber;
   FastLED.show();
   delay(10);
 }
 Serial.print("Current Column Value: ");
 Serial.println(Column);
 for (int m = NumRing; m >= 0 ; m --){
  ArrayNumber = PixelArray[m-1];
  Serial.print("Pixel Down: ");
  Serial.println(ArrayNumber); 
  for (int n = Column-1; n >= abs(ArrayNumber-Column); n--){
    leds3 [n] = CRGB (RedC,GreenC,BlueC);
  }
   FastLED.show();
   delay(Reaction);
   for (int i = Column; i >= abs(ArrayNumber-Column); i--){
    leds3 [i] = CRGB :: Black;
  }
  Column -=ArrayNumber;
  FastLED.show();
  delay(10);
 }
 return animation;
}

void RingAnimation_up (int RedC, int GreenC, int BlueC, int animation){
  int ArrayNumber = 0;
  int Column = 0;
  int Reaction = 50;
  for (int m = 1; m <= NumRing; m++){
   ArrayNumber = PixelArray[m-1];
   Serial.print("Pixel Up: ");
   Serial.println(ArrayNumber);
   for (int n = Column; n < ArrayNumber+Column; n++){
    //Serial.println("for loop");
    leds3 [n] = CRGB (RedC, GreenC, BlueC);
   }
   FastLED.show();
   delay(Reaction);
   for (int i = Column; i < ArrayNumber+Column; i++){
    leds3 [i] = CRGB :: Black;
   }
   Column +=ArrayNumber;
   FastLED.show();
   delay(10);
 }
return animation;
}

void RingAnimation_Half (int RedC, int GreenC, int BlueC, int animation){
  int ArrayNumberUp = 0;
  int ArrayNumberDown = 0;
  int ColumnUp = 0;
  int ColumnDown = 0;
  int Reaction = 100; 
  int HalfRing = 0;
  int RemainderRing = 0;

  RemainderRing = NumRing % 2;
  HalfRing = (NumRing / 2) + RemainderRing;
  for (int l = 0; l <= HalfRing; l++){
    ArrayNumberUp = PixelArray[l+HalfRing+1];
    ArrayNumberDown = PixelArray[(HalfRing)-l];
    ColumnUp +=ArrayNumberDown;
    ColumnDown +=ArrayNumberDown;
  }
  ColumnUp = ColumnUp - (PixelArray[HalfRing]);
  ColumnDown = ColumnDown - ((PixelArray[HalfRing]*2)+2);
  
  for (int m = 1 ; m <=HalfRing; m++){
    ArrayNumberUp = PixelArray[m+HalfRing-1];
    ArrayNumberDown = PixelArray[(HalfRing)-m];
    for (int up = 0 ; up < ArrayNumberUp; up++){
      leds3[ColumnUp+up] = CRGB(RedC,GreenC,BlueC);
    }
    for (int down = 0; down < ArrayNumberDown ;  down++){
      leds3[ColumnDown+down] = CRGB(RedC,GreenC,BlueC);
    }
    FastLED.show();
    delay(Reaction);
    for (int up = 0 ; up < ArrayNumberUp; up++){
      leds3[ColumnUp+up] = CRGB :: Black;
    }
    for (int down = 0; down < ArrayNumberDown ;  down++){
      leds3[ColumnDown+down] = CRGB :: Black;
    }
    ArrayNumberDown = PixelArray[(HalfRing)-(m+1)];
    ColumnUp += ArrayNumberUp;
    ColumnDown -=ArrayNumberDown;
    
    FastLED.show();
    delay(10);
  }
    ColumnDown = 0;
    ArrayNumberDown = PixelArray[ColumnDown];
    ColumnUp = ColumnUp - ArrayNumberUp;
    ColumnDown = ColumnDown + ArrayNumberDown;
  for (int m = 1 ; m <HalfRing-1; m++){
    for (int n = 1 ; n <=PixelArray[m] ; n++){
      leds3[(ColumnDown)+(n-1)] = CRGB(RedC,GreenC,BlueC);
    }
    for (int i = PixelArray[(NumRing-1)-m]; i > 0; i--){
      leds3[(ColumnUp)-i] = CRGB(RedC,GreenC,BlueC);
    }
    FastLED.show();
    delay(Reaction);
    for (int n = 1 ; n <=PixelArray[m] ; n++){
      leds3[(ColumnDown)+(n-1)] = CRGB:: Black;
    }
    for (int i = PixelArray[(NumRing-1)-m]; i > 0; i--){
      leds3[(ColumnUp)-i] = CRGB :: Black;
    }
    FastLED.show();
    delay(10);/**/   
  }
return animation;
}

void DomeAnimation_spin (int RedC,int GreenC, int BlueC, int animation){
  Serial.print("Enter Animation: ");
  Serial.println(animation);
  byte pixel;
  int pixelIndex;
  int pixelIndex2;
  int Reaction = animation;
  int index ;
   

for (int m = 0 ; m < RING_MAX_PIXELS; m++){
  Serial.print("Current Animation: ");
  Serial.println(animation);
   animation = animation;
    index = (((float)m/(float) NumRing)+(0.35*m));
    if (index > 12) {index = 12;}
    Serial.print("Current Index: ");
    Serial.println(index);
  for(int i = 0 ; i <NumRing ; i++){
    pixelIndex = round((float) RING_SIZES[i] / (float) RING_MAX_PIXELS *index );
    pixelIndex2 = round((float) RING_SIZES[i] / (float) RING_MAX_PIXELS *(index+13) );
    pixel = RINGS[i][pixelIndex];
    leds3 [RINGS[i][pixelIndex]] = CRGB (RedC,GreenC,BlueC);
    leds3 [RINGS[i][pixelIndex2]] = CRGB (RedC,GreenC,BlueC);
  }
    FastLED.show();
    delay(Reaction);
  for(int i = 0 ; i <NumRing ; i++){
    pixelIndex = round((float) RING_SIZES[i] / (float) RING_MAX_PIXELS * index);
    pixelIndex2 = round((float) RING_SIZES[i] / (float) RING_MAX_PIXELS *(index+13) );
    leds3 [RINGS[i][pixelIndex]] = CRGB :: Black;
    leds3 [RINGS[i][pixelIndex2]] = CRGB :: Black;
    }
    FastLED.show();
    delay(Reaction);
  }

return animation;
}

void DomeAnimation_quarter (int RedC,int GreenC, int BlueC, int animation){
  byte pixel;
  int pixelIndex;
  int pixelIndex2;
  int Reaction = 5;
  int index ;
  animation = animation;

for (int m = 0 ; m < RING_MAX_PIXELS; m++){
    index = (((float)m/(float) NumRing)+(0.35*m));
    if (index > 12) {index = 12;}
  for(int n = 0 ; n <NumRing ; n++){
    pixelIndex = round((float) RING_SIZES[n] / (float) RING_MAX_PIXELS *index );
    pixelIndex2 = round((float) RING_SIZES[n] / (float) RING_MAX_PIXELS *abs(index-13) );
    pixel = RINGS[n][pixelIndex];
    leds3 [RINGS[n][pixelIndex]] = CRGB (RedC,GreenC,BlueC);
    leds3 [RINGS[n][pixelIndex2]] = CRGB (RedC,GreenC,BlueC);
  }
    FastLED.show();
    delay(Reaction);
  for(int n = 0 ; n <NumRing ; n++){
    pixelIndex = round((float) RING_SIZES[n] / (float) RING_MAX_PIXELS * index);
    pixelIndex2 = round((float) RING_SIZES[n] / (float) RING_MAX_PIXELS *abs(index-13) );
    leds3 [RINGS[n][pixelIndex]] = CRGB :: Black;
    leds3 [RINGS[n][pixelIndex2]] = CRGB :: Black;
    }
    FastLED.show();
    delay(Reaction);
  }
  return animation;
}

void fullDomeAnimation_rainbow (int RedC, int GreenC,int BlueC, int color){
  int index;
  int pixel;
  int pixelIndex;
  int Reaction = 1;
  for (int r = 0 ; r <= RING_MAX_PIXELS; r++){
     for (int x = 0; x < NumRing; x++){
      pixelIndex = round((float) RING_SIZES[x] / (float) RING_MAX_PIXELS *r );
      pixel = RINGS[x][pixelIndex];
      //if (pixel == 0) {continue;} // skip condition
      leds3 [RINGS[x][pixelIndex]] = Scroll(((r+color)*256/50+k)%256);

     }
      FastLED.show();
      delay(Reaction);
  }
}

void VuMeter_RainBow (int Reaction){
  //int Reaction = 10;
  for (int m = 0; m <map(Reaction*2, 0,Rows,0,  NumRing-1); m++){
    for (int n = 0; n <PixelArray[m]; n ++){
      /*Serial.print("Current Array: ");
      Serial.println(n);
      Serial.print("Number of Pixel: ");
      Serial.println(PixelArray[m]);
      Serial.print("Current Pixel is: ");
      Serial.println(RINGS[5-m][n]);
      /**/
    leds3[RINGS[5-m][n]] = Scroll((n*256/50+k)%256);
   }
  }
}

void doubleRainbow(int NUM_LEDS)
{
  Serial.println("Check Double");

  int midway = NUM_LEDS/2;
  Serial.print("Midway :");
  Serial.println(midway);
  Serial.print("React :");
  Serial.println(react);
  Serial.print("React + Midway :");
  Serial.println(react+midway);
  
  
  for(int i = NUM_LEDS - 1; i >= midway; i--) {
    if (i < react + midway) {
      leds5[i] = Scroll((i * 256 / 50 + k) % 256);
      leds5[(midway - i) + midway] = Scroll((i * 256 / 50 + k) % 256);
      //leds[(i*3)]  = Scroll((i * 256/ 50 + k) % 256);
      //leds[((midway*3) - i)+ midway*3] = Scroll((i * 256/ 50 + k) % 256);
    }
    else
      leds5[i] = CRGB(0, 0, 0);
      leds5[midway - react] = CRGB(0, 0, 0);
      //leds[i*3] = CRGB (0,0,0);
      //leds[(midway*3)-react] = CRGB (0,0,0);
  }
  FastLED.show();
  
}

void convertDouble(int Freq, int NUM_LEDS)

{
  int midway = NUM_LEDS/2;
 


    pre_react = ((long)NUM_LEDS * (long)Freq) / 500L; // TRANSLATE AUDIO LEVEL TO NUMBER OF LEDs

    if (pre_react > react) // ONLY ADJUST LEVEL OF LED IF LEVEL HIGHER THAN CURRENT LEVEL
      {old_react = react;}
      react = pre_react;

    Serial.print(Freq);
    Serial.print(" -> ");
    Serial.println(pre_react);
    Serial.print("Old React: ");
    Serial.println(old_react);
  
}
