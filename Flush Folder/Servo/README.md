# Auto Flush with Servo Motor

- First iteration of flusher - current toilet design had flapper. Current Arduino kit already had servo motor which is strong enough to pull up. 
- Did not need to spend more money to change motor type.

Concept: 
  1. Use Sharp IR sensor to detect range changes when object approaches. 
      * Using IR sensor instead of sonic sensor provided by the kit because we want to keep the sound from distrubing pets.
  2. When the sensor is detecting a specified range (range is less than 8 inches), we will trigger counter.
  3. If counter is less than specified time ( count is less than 8), we will not initiate flusher code.
  4. If counter is more than specified time ( count is greated than 8), we will start flusher code.
  5. program will initate power to the Servo PIN to pull flapper up.
  6. program will wait for a specified ammount of time to allow all water to draing from the bowl.
  7. program will delay for a specified ammount of time to allow water to refill and prevent flush with insufficient water in bowl. 
  8. program will turn off power to Servo motor and move to a different PIN to prevent Servo motor from draining power from power supply.
    * power drain causes IR sensor to constainly ranging lower value. Turning off power prevent false trigger.
  9. Output number of usuage to LCD so we will have a sense of weather the flusher is working or not.

  
  Difficulties: Servo Motor was constantly triggering without any object infront.
  Cause: The Servo motor when left on would draw too much power from the IR sensor and causing false reading and triggering ghost flushes.
  Solution: move signal pin output to different pin after count is trigger. change signal pin back before we trigger servo.
  
  Need improvement - Allow mode change without having to take out arduino card to reprogram code. 
         - This was later added into the Stepper Motor function.
