# Arduino
// Long Nguyen
// Home Made Auto Flusher, IR distance Sensor
// Aug 23 2018 

//Global Constant 
#include <LiquidCrystal.h> // Library import from Elegoo
#include <Servo.h>         // Library import from Arduino
#include <SharpIR.h>       // Library import from http://robojax.com/learn/arduino 
                           // This Library for IR sensor might not be needed
                           // Code update will convert the signal to distance value later.
#define ir A1
#define model 1080

Servo ServoMotor;


int CountN = 0; // Count how long the obeject remains in front of sensor
int countLCD = 0; // Count the ammount of time object trigger the sensor code
int HArray [25]={}; // Declare Array to compare sensor value
int dst = 0;

LiquidCrystal lcd (12, 11, 5, 4, 3, 2);
SharpIR SharpIR(ir,model);

void setup() {

  Serial.begin(9600); // start Serial communication: at 9600 baurate


  // inital PIN 10
  ServoMotor.attach(10); // initialize on PIN 10 so the servo don’t draw power
  ServoMotor.write(0);   // servo on cause false IR Sensor reading.
  delay(100);


}

void loop() {

 dst=SharpIR.distance();
 dst=(dst/2.54);
 HArray[0] = dst;
	
	// Due to inaccuracy of the Sharp IR sensor I have decided to use this logic
	/* Logic here is: We will take 24 samples sensor value and we will pick the
           highest value. 
	   Trial and error1: I have tried using Single samples and sometime We will get 
           a returns value that is too low and it would trigger the flusher event.
           Trial and error2: I have tried using 25 samples and average it out. However,
	   This will return a value that is lower than the limit I have set. Causing false
           trigger every 30-40min or so.
           Trial and error3: Taking 25 samples and picking the highest value have not
           Cause any miss fired in the flushing logic. When user is within the trigger
           Range the value had not gone high enough to not Trigger the flush. Thus this
           will be the logic I will use until there is an error. */

	for (int ArraySlot = 1; ArraySlot < 25; ArraySlot++){

  
  	dst = SharpIR.distance();
  	dst = (dst/2.54);
  	HArray[ArraySlot] = dst;


		// If Previous sensor value is lower then save current sensor value
		// to current slot 
		if (HArray[ArraySlot-1] <= HArray[ArraySlot]){

  			HArray[ArraySlot] = HArray[ArraySlot];
  
		}
		// If Previous sensor value is higher then save previous value
		// to current slot
		else{

  		HArray[ArraySlot] = HArray[ArraySlot-1];
   
		}

	}


 dst = HArray[24]; // Setting Distance to the last value, which should be the highest.
 
 // Lower for serial port to check the value. Keep code just in case need to debug.
 Serial.print(dst);
 Serial.print(", Distance");
 Serial.println();
 Serial.println();
 delay(100);
 

 
 // Trigger Event to wait if user is within 13 inches of the sensor
 // Guard from quick passing by
  

  if (dst >= 1 && dst <= 13){  //trigger wait event if object move in front of sensor
    
    CountN = CountN+1; // Count how many time we stay connected
    
  }
  else{
    
    // If link break after certain count we trigger next event
    // Flush will occur
    // Reset counter for next event
    // We will also guard against people walking by quickly. User "Cat" must be there for more than 8 count
    // If not more than 8 we clear counter and start at zero.
    // If counter is more than 8 then we wait about 10sec before flush. This way we won't scare the cat.
    
    
    if (CountN >=15 ){
      

      CountN = 0; // reset timer time
      countLCD = countLCD + 1; // Count the number of time sensor is triggered
      lcd.begin (16, 2); 
      lcd.print(countLCD);
      delay(30000); // 5min Delay Flush. Won’t scare pets if they are playing near toilet 
    
    // Initiate Flush. 
      ServoMotor.attach(9); // initialize on PIN 9 to power the servo motor
      ServoMotor.write(90); // Pull Lever up to start flush
      delay(5000);  // Wait time for water to flush. 
      ServoMotor.write(0); // Close Hole allow Water To fill back up
      ServoMotor.attach(10); // move Signal PIN back to 10 so the motor would turn off
      delay (10000); // wait to let water fill back up before allowing program to run again
    }
    else if (CountN > 0 && CountN <= 8){
      
      // Serial Port logger will keep. 
      Serial.print (CountN);
      Serial.print (", QuickMove");  // Trigger event when object move away from sensor
      Serial.println();
      
      CountN = 0; // Zero out count if the user only walk by
      delay(100);
    }
    }
  

 
    delay(100);
  }
  
