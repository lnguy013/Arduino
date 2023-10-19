void FRONTlightswitch (int SWITCHvalue){
 /*Serial.println("Front Light Check ");
  Serial.print("Case Value ");
  Serial.println(SWITCHvalue);
  Serial.println(" ");/**/
   switch(SWITCHvalue){ // Turn on front light
    case -22441:
    //newBright = BRIGHTNESS;
    //FastLED.setBrightness(  newBright );
    LIGHTprevious = SWITCHvalue;
    previousTimes = millis();
    fill_solid(LEDSfl, NUMleds, CRGB(Red, Green, Blue));
    FastLED.show();
  }
  
  switch(SWITCHvalue) { //High Beam
    case -19891:
    newTimes = millis();
    fill_solid(LEDSfl, NUMleds, CRGB(250, 250, 250));
    FastLED.show();
    /*if (newTimes - previousTimes >= 3000){
       switch(LIGHTprevious){
        case -2041:
        fill_solid( LEDSfl, NUMleds, CRGB::Black);
        FastLED.show();
        previousTimes = millis();
       }
       switch(LIGHTprevious){
        case -22441:
        fill_solid(LEDSfl, NUMleds, CRGB(Red, Green, Blue));
        FastLED.show();
        previousTimes = millis();
       }
       Serial.println("if Check log flash");
    }
    Serial.println("out if Check log flash");
    //delay (3000);/**/

    
  }
}
