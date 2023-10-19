void SERVOmotorinitial () {
    ServoMotor.attach(12); //Initialized the Signal for Servo to be On then. 
    ServoMotor.write(0); //Keep it zero on 10. This way the Motor won't power on 
}

void SERVOmotorstop () {
    ServoMotor.attach(11); // Initialize the Servo signal to PIN 9 to start up Motor only when needed
    //ServoMotor.write(100); // Pull Lever up to start flush

    for (pos = 110; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      ServoMotor.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
}

void SERVOmotormove (){
    ServoMotor.attach(11); // Initialize the Servo signal to PIN 9 to start up Motor only when needed
    //ServoMotor.write(10); // Pull Lever up to start flush

    for (pos = 180; pos >= 110; pos -= 1) { // goes from 180 degrees to 0 degrees
      ServoMotor.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    ServoMotor.attach(12);
}
