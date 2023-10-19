void BRAKElight (int SWITCHvalue){
  switch(SWITCHvalue){ // Press the brake Blue button
    case -30601:
    //newBright = BRIGHTNESS;
    //FastLED.setBrightness(  newBright );
    LIGHTprevious = SWITCHvalue;
    previousTimes = millis();
    fill_solid( LEDSflb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSfrb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSfl, NUMleds, CRGB::White);
    fill_solid( LEDSblb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSbrb, NUMleds, CRGB::Yellow);
    fill_solid(LEDSbl, NUMleds, CRGB(200, 0, 0));
    fill_solid(LEDSbr, NUMleds, CRGB(200, 0, 0));
    //analogWrite(CENTERmotor, 0);
    FastLED.show();
    SERVOmotormove();
  }

   switch(SWITCHvalue){ // Release the brake Green button
    case -10201:
    //newBright = BRIGHTNESS;
    //FastLED.setBrightness(  newBright );
    LIGHTprevious = SWITCHvalue;
    previousTimes = millis();
    fill_solid( LEDSflb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSfrb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSfl, NUMleds, CRGB::White);
    fill_solid( LEDSblb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSbrb, NUMleds, CRGB::Yellow);
    LEDSbl[0] = CRGB(40,0,0);
    LEDSbr[0] = CRGB(40,0,0);
    LEDSbl[1] = CRGB(0,0,0);
    LEDSbr[1] = CRGB(0,0,0);
    LEDSbl[2] = CRGB(0,0,0);
    LEDSbr[2] = CRGB(0,0,0);
    //analogWrite(CENTERmotor, 20);
    FastLED.show();
    SERVOmotormove();
  }

  switch(SWITCHvalue){//slow down use strobe button
    case 255:
    fill_solid( LEDSflb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSfrb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSfl, NUMleds, CRGB::White);
    fill_solid( LEDSblb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSbrb, NUMleds, CRGB::Yellow);
    SERVOmotormove();
    //analogWrite(CENTERmotor, 10);

    newTimes = millis();
    Serial.print("Previous Time is: ");
    Serial.println(newTimes - previousTimes);
    if (newTimes - previousTimes >= 300){

      LEDSbl[0] = CRGB :: Black;
      LEDSbr[0] = CRGB :: Black;
      LEDSbl[1] = CRGB :: OrangeRed ;
      LEDSbr[1] = CRGB :: Black;
      LEDSbl[2] = CRGB :: OrangeRed ;
      LEDSbr[2] = CRGB :: Black;
      FastLED.show();
      FastLED.delay(100);
     

      previousTimes = newTimes;
     }else{
      LEDSbl[0] = CRGB :: Black;
      LEDSbr[0] = CRGB :: Black;
      LEDSbl[1] = CRGB :: Black;
      LEDSbr[1] = CRGB :: OrangeRed ;
      LEDSbl[2] = CRGB :: Black;
      LEDSbr[2] = CRGB :: OrangeRed ;
      FastLED.show();
      FastLED.delay(100);
      
     }
  }

switch(SWITCHvalue){//Stop use Red button
    case -26521:
    fill_solid( LEDSflb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSfrb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSfl, NUMleds, CRGB::White);
    fill_solid( LEDSblb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSbrb, NUMleds, CRGB::Yellow);
    SERVOmotorstop();
    //analogWrite(CENTERmotor,0);

    newTimes = millis();
    Serial.print("Previous Time is: ");
    Serial.println(newTimes - previousTimes);
    if (newTimes - previousTimes >= 300){

      LEDSbl[0] = CRGB :: Red;
      LEDSbr[0] = CRGB :: Black;
      LEDSbl[1] = CRGB :: Red ;
      LEDSbr[1] = CRGB :: Black;
      LEDSbl[2] = CRGB :: Black ;
      LEDSbr[2] = CRGB :: Black;
      FastLED.show();
      FastLED.delay(100);
     

      previousTimes = newTimes;
     }else{
      LEDSbl[0] = CRGB :: Black;
      LEDSbr[0] = CRGB :: Red;
      LEDSbl[1] = CRGB :: Black;
      LEDSbr[1] = CRGB :: Red ;
      LEDSbl[2] = CRGB :: Black;
      LEDSbr[2] = CRGB :: Black ;
      FastLED.show();
      FastLED.delay(100);
      
     }
  }
  
}
