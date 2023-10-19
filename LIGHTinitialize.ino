void LIGHTinitialize (){
  FastLED.addLeds<LEDtype, FRONTleftblink, COLORorder>(LEDSflb, NUMleds).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LEDtype, FRONTrightblink, COLORorder>(LEDSfrb, NUMleds).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LEDtype, FRONTlight, COLORorder>(LEDSfl, NUMleds).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LEDtype, BACKleftblink, COLORorder>(LEDSblb, NUMleds).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LEDtype, BACKrightblink, COLORorder>(LEDSbrb, NUMleds).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LEDtype, BRAKEleft, COLORorder>(LEDSbl, NUMleds).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LEDtype, BRAKEright, COLORorder>(LEDSbr, NUMleds).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  fill_solid( LEDSflb, NUMleds, CRGB::Black);
  fill_solid( LEDSfrb, NUMleds, CRGB::Black);
  fill_solid( LEDSfl, NUMleds, CRGB::Black);
  fill_solid( LEDSblb, NUMleds, CRGB::Black);
  fill_solid( LEDSbrb, NUMleds, CRGB::Black);
  fill_solid( LEDSbl, NUMleds, CRGB::Black);
  fill_solid( LEDSbr, NUMleds, CRGB::Black);
  FastLED.show();
}
