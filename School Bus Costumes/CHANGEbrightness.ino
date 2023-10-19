void CHANGEbrightness (int SWITCHvalue){
  switch (SWITCHvalue){ // increase brightness to 100 max incremment by 5
    case -28561:
    if(!(newBright == 200)){
      newBright = newBright +5;
      FastLED.setBrightness (newBright);
      FastLED.show();
    }
  }
  switch(SWITCHvalue){// decrease brightness to 0
    case -18361:
    if(!(newBright == 5)){
      newBright = newBright -5;
      FastLED.setBrightness (newBright);
      FastLED.show();
    }
  }
}
