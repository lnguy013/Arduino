# Automatic Toilet Flusher

Purpose: Create an system that uses a sensor to detect motion and activate a motor to flush a toilet.

  - Must be pets friendly - will not scare pets or interfere with their senses.
  - Must not trigger when user only pass by - keep count of how long the sensor is interupted. Short count == just pass by. Longer count == trigger flush.
  - Integrate LCD for debugging - Output useful information on LCD screen for debugging issues.

1. Servo - will use servo motor to to pull toilet with levers. Use for toilet system with flappers. 
2. Stepper - will user Stepper motor to push down on toilet with button. Use for toilet with 2 button water saver options
  - Stepper motor is user for button version because we can get more torque from stepper motor compared to the servo motor. 
