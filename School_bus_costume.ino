#include <IRremote.h>
#include <FastLED.h>
#include <Servo.h>

//left side will be even pin
//right side will be odd pin
#define FRONTleftblink 2 //digital output d2 
#define FRONTrightblink 3 //digital output d3
#define BACKleftblink 4 //digital output d4
#define BACKrightblink 7 //digital output d5
#define FRONTlight 8 //digital output d8
const int buzzer = 9; //digital output d9
int CENTERmotor = 11; //digital output 11
#define IRrevpin 10 //digial input 10
#define BRAKEleft 6 // digital input 6
#define BRAKEright 5 //digital input 7

#define NUMleds 3
#define BRIGHTNESS 64
#define LEDtype WS2812B
#define COLORorder GRB
#define FRAMESpersecond 20
#define OFFtime 3

CRGB LEDSflb[NUMleds];
CRGB LEDSfrb[NUMleds];
CRGB LEDSfl[NUMleds];
CRGB LEDSblb[NUMleds];
CRGB LEDSbrb[NUMleds];
CRGB LEDSbl [NUMleds];
CRGB LEDSbr [NUMleds];
IRrecv irrecv(IRrevpin);
decode_results results;
Servo ServoMotor;

int OUTPUTvalue =0;
int OUTPUTtemp =0;
int LIGHTprevious;
int BLINKprevious;
int BRAKEprevious;
int IRvalue;
int newBright = 65;
int Red = 50;
int Green = 50;
int Blue = 60;
int pos = 0;

unsigned long previousTimes = 0;
unsigned long newTimes = 0;
unsigned long compareTimes = 0;


void setup() {
  delay( 100 ); // power-up safety delay
  //pinMode(CENTERmotor, OUTPUT);
  pinMode(buzzer, OUTPUT);
  LIGHTinitialize();
  SERVOmotorinitial();
  delay(50);   
  Serial.begin(9600);
  //while(!Serial);     
  irrecv.enableIRIn();   
  previousTimes = millis();  
}

void loop() {
  Serial.println("Main Loops Check Log");
  
  //analogWrite(CENTERmotor, 150);
  
  IRinputvalue ();

  OUTPUTtemp = OUTPUTvalue;
  CHANGEbrightness(OUTPUTtemp);
  TURNonofflight(OUTPUTtemp);
  FRONTlightswitch(OUTPUTtemp);
  BLINKlightswitch(OUTPUTtemp); 
  BRAKElight(OUTPUTtemp);
  digitalWrite(buzzer, HIGH);
  
  Serial.println();
  Serial.print("Current output value ");
  Serial.println(OUTPUTtemp);
  Serial.println();
}
