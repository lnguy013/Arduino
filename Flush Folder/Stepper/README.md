# Auto Flush with Stepper Motor

- This is an upgraded version from servo motor. Upgraded toilet and it did not come with flanger

Concept: 
  1. Use Sharp IR sensor to detect range changes when object approaches. 
      * Using IR sensor instead of sonic sensor provided by the kit because we want to keep the sound from distrubing pets.
  2. When the sensor is detecting a specified range (range is less than 8 inches), we will trigger counter.
  3. If counter is less than specified time ( count is less than 8), we will not initiate flusher code.
  4. If counter is more than specified time ( count is greated than 8), we will start flusher code.
  5. program will initate power to the Stepper PIN and drive the gear downward to push the button. 
  6. program will after we reach the max steps we will drive gear back upward to release button allow water to refill the bowl.
  7. program will turn off power to Stepper motor and move to a different PIN to prevent Stepper motor from draining power from power supply.
  8. Output number of usuage to LCD so we will have a sense of weather the flusher is working or not.
  9. LCD will indicate which mode we are on.
  10. LCD will also show current IR range - for debugging
  11. LCD will indicate each step of the process - for debugging
  12. We will have 3 mode, each mode is for testing purposes. 0 wait , 5 minute wait and 9 minutes wait.
       * 5 minutes and 9 minutes is to prevent from scaring pet if they accidentally trigger it.
  13. To change mode without adding button add code that after 3 quick passes we will cycle through mode.
  
  
  Mechanical Difficulties: Stepper motor alone was not strong enough to push the button all the way down.
  
  Solution: Used 2 tiers of planetary gears to increase torque downward. (found 3d printed design on thingverse.com)
  
  
  Need improvement - counter to reset the mode changer count needs to work more accurately.
          - Train of thought - we could add another counter after change mode is triggered initially. If counter reached zero before mode is change we can reset change mode counter.
          
          
  
