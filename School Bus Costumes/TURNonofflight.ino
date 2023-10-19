void TURNonofflight (int SWITCHvalue){
    switch(SWITCHvalue) {// Trun off  light
    case -2041:
    LIGHTprevious = SWITCHvalue;
    previousTimes = millis();
    fill_solid( LEDSflb, NUMleds, CRGB::Black);
    fill_solid( LEDSfrb, NUMleds, CRGB::Black);
    fill_solid( LEDSfl, NUMleds, CRGB::Black);
    fill_solid( LEDSblb, NUMleds, CRGB::Black);
    fill_solid( LEDSbrb, NUMleds, CRGB::Black);
    fill_solid( LEDSbl, NUMleds, CRGB::Black);
    fill_solid( LEDSbr, NUMleds, CRGB::Black);
    FastLED.show();
  }

   switch(SWITCHvalue) {// Trun off  light
    case -20401:
    LIGHTprevious = SWITCHvalue;
    previousTimes = millis();
    fill_solid( LEDSflb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSfrb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSfl, NUMleds, CRGB::White);
    fill_solid( LEDSblb, NUMleds, CRGB::Yellow);
    fill_solid( LEDSbrb, NUMleds, CRGB::Yellow);
    LEDSbl[0] = CRGB(40,0,0);
    LEDSbr[0] = CRGB(40,0,0);
    FastLED.show();
  }
  
}
