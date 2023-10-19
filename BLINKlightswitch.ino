void BLINKlightswitch (int SWITCHvalue){
  switch(SWITCHvalue){ // Blink left on
    case 14535:
    BLINKprevious = SWITCHvalue;
    LEFTturn();
    
  }
  switch(SWITCHvalue) {// Blink right on
    case -4081:
    BLINKprevious = SWITCHvalue;
    RIGHTturn();
 

  }
  switch(SWITCHvalue) {// turn off turn signal dark green
    case 10455:
    BLINKprevious = SWITCHvalue;
    previousTimes = millis();
    fill_solid(LEDSflb, NUMleds, CRGB::Yellow);
    fill_solid(LEDSblb, NUMleds, CRGB::Yellow);
    fill_solid(LEDSfrb, NUMleds, CRGB::Yellow);
    fill_solid(LEDSbrb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSfl, NUMleds, CRGB::White);
    LEDSbl[0] = CRGB(40,0,0);
    LEDSbr[0] = CRGB(40,0,0);
    LEDSbl[1] = CRGB(0,0,0);
    LEDSbr[1] = CRGB(0,0,0);
    LEDSbl[2] = CRGB(0,0,0);
    LEDSbr[2] = CRGB(0,0,0);
    FastLED.show();
    SERVOmotormove();
    //OUTPUTtemp = 150000;
    
  }
  
  switch(SWITCHvalue){
    case 150000: //turn off blinker
    fill_solid(LEDSflb, NUMleds, CRGB::Black);
    fill_solid(LEDSblb, NUMleds, CRGB::Black);
    fill_solid(LEDSfrb, NUMleds, CRGB::Black);
    fill_solid(LEDSbrb, NUMleds, CRGB::Black);
    FastLED.show();
    //OUTPUTvalue = BLINKprevious;
  }
}

void LEFTturn (){

    newTimes = millis();
    Serial.print("Previous Time is: ");
    Serial.println(newTimes - previousTimes);
    SERVOmotormove();
    if (newTimes - previousTimes >= 2000){
     for(int i = (NUMleds)-1; i >= 0; i--){
      fill_solid(LEDSfrb, NUMleds, CRGB::Black);
      fill_solid(LEDSbrb, NUMleds, CRGB::Black);
      fill_solid( LEDSfl, NUMleds, CRGB::White);
      LEDSbl[0] = CRGB(40,0,0);
      LEDSbr[0] = CRGB(40,0,0);
      LEDSbl[1] = CRGB(0,0,0);
      LEDSbr[1] = CRGB(0,0,0);
      LEDSbl[2] = CRGB(0,0,0);
      LEDSbr[2] = CRGB(0,0,0);
      LEDSflb[i] = CRGB :: Yellow;
      LEDSblb[i] = CRGB :: Yellow;
      FastLED.show();
      FastLED.delay(500);
     }

      previousTimes = newTimes;
     }else{
      fill_solid( LEDSfl, NUMleds, CRGB::White);
      LEDSbl[0] = CRGB(40,0,0);
      LEDSbr[0] = CRGB(40,0,0);
      LEDSbl[1] = CRGB(0,0,0);
      LEDSbr[1] = CRGB(0,0,0);
      LEDSbl[2] = CRGB(0,0,0);
      LEDSbr[2] = CRGB(0,0,0);
      fill_solid(LEDSflb, NUMleds, CRGB::Black);
      fill_solid(LEDSblb, NUMleds, CRGB::Black);
      fill_solid(LEDSfrb, NUMleds, CRGB::Black);
      fill_solid(LEDSbrb, NUMleds, CRGB::Black);

      FastLED.show();
      
     }
 }

 void RIGHTturn (){

    newTimes = millis();
    Serial.print("Previous Time is: ");
    Serial.println(newTimes - previousTimes);
    SERVOmotormove();
    if (newTimes - previousTimes >= 2000){
     for(int i = (NUMleds)-1; i >= 0; i--){
      fill_solid(LEDSflb, NUMleds, CRGB::Black);
      fill_solid(LEDSblb, NUMleds, CRGB::Black);
      fill_solid( LEDSfl, NUMleds, CRGB::White);
      LEDSbl[0] = CRGB(40,0,0);
      LEDSbr[0] = CRGB(40,0,0);
      LEDSbl[1] = CRGB(0,0,0);
      LEDSbr[1] = CRGB(0,0,0);
      LEDSbl[2] = CRGB(0,0,0);
      LEDSbr[2] = CRGB(0,0,0);
      LEDSfrb[i] = CRGB :: Yellow;
      LEDSbrb[i] = CRGB :: Yellow;
      FastLED.show();
      FastLED.delay(500);
     }

      previousTimes = newTimes;
     }else{
      fill_solid( LEDSfl, NUMleds, CRGB::White);
      LEDSbl[0] = CRGB(40,0,0);
      LEDSbr[0] = CRGB(40,0,0);
      LEDSbl[1] = CRGB(0,0,0);
      LEDSbr[1] = CRGB(0,0,0);
      LEDSbl[2] = CRGB(0,0,0);
      LEDSbr[2] = CRGB(0,0,0);
      fill_solid(LEDSflb, NUMleds, CRGB::Black);
      fill_solid(LEDSblb, NUMleds, CRGB::Black);
      fill_solid(LEDSfrb, NUMleds, CRGB::Black);
      fill_solid(LEDSbrb, NUMleds, CRGB::Black);

      FastLED.show();
      
     }
 }
