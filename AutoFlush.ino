/* Long Nguyen
   Home Made Auto Flusher, IR distance Sensor
   Aug 23 2018
  */

//Global Constant 
#include <LiquidCrystal.h> // Library import from Elegoo. Import LCD library so we can use LCD feature. Not needed.
#include <Servo.h>         // Library import from Arduino. Import Servo Library so we can use Serve feature.
#include <SharpIR.h>       // Library import from http://robojax.com/learn/arduino 
                           // This Library for IR sensor might not be needed
                           // Code update will convert the signal to distance value later.

#define ir A1              // According to SharpIR.h library we must define the type of IR sensor we are using. A1 = 
#define model 1080

Servo ServoMotor;          // Define ServoMotor variable as Type Servo. 


int CountN = 0;            // Count how long the obeject remains in front of sensor. Variable use to determine whether 
                           // or Not the user triggered the sensor on purpose or just walking by. Prevent False trigger.

int countLCD = 0;          // Count the ammount of time object trigger the sensor code. Variable use to determine how many
						   // time the Flush was triggered. Not needed if use don't intend to keep track using LCD.

int HArray [25]={};        // Declare Array to compare sensor value. Array, of 25 memory slots, 
                           // used to store a sample of 25 values. 

int dst = 0;               // Declare integer dst for distance. Variable used to store current IR measured distance.

int s = 0;
int s2 = 0;
int m = 0;
int m2 =0;


LiquidCrystal lcd (12, 11, 5, 4, 3, 2);  // Initializing the LCD. Indicating PIN on the Arduino board we 
										 // are using. Not Needed.

SharpIR SharpIR(ir,model);               // Initializing IR sensor. Indicating Model and sample rate we are using.



//This code in setup will only run once.
void setup() {

  Serial.begin(9600);       // start Serial communication: at 9600 baurate. This is for Debuging. 
  							// Initialize a console for user to see. Not Needed.
  
  // inital PIN 10
  ServoMotor.attach(10);    // initialize on PIN 10 so the servo don’t draw power.
                            // servo on cause false IR Sensor reading.
  
  ServoMotor.write(0);      // Turn Server motor off by inputing 0 in to the value
  delay(100);               // wait about 100 milsec before going on to start the next line of code.
	
  // LCD display setup
  lcd.begin (16, 2); //
  lcd.setCursor(0,0);      // pointer to start LCD print at row 1 column 1
  lcd.print("Used: ");     // print Usded: to LCD screen (using column 0-5)


}

void loop() {

 dst=SharpIR.distance();    // Start the Sharp IR sensor. Equation is provided in the IR library. The value is equal to dst.
 dst=(dst/2.54);            // Conversion from cm to inches
 HArray[0] = dst;           // Store dst value into slot 1 of the HArray Array for comparison later.
	
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
 
 // Setup LCD to show current IR measurement 
 lcd.setCursor(9,0);
 lcd.print("Dst:");
 if (dst >= 10){
 lcd.setCursor(13,0);
 lcd.print(dst);
 lcd.print(15,0);
 lcd.print(" ");
 }
 else{
 lcd.setCursor(13,0);
 lcd.print("0");
 lcd.setCursor(14,0);
 lcd.print(dst);
 lcd.setCursor(15,0);
 lcd.print(" ");
 }
	
	
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
      
      s = 0;
      s2 = 0;
      m = 0;
      m2 =0;
      CountN = 0; // reset timer time
      countLCD = countLCD + 1; // Count the number of time sensor is triggered. Not Needed
      
      // LCD setup for number of usages
      lcd.setCursor(6,0);
      lcd.print(countLCD);   
	    
      // LCD setup to indicated we are in flushing mode. Replace IR distances with "fsh"
      lcd.setCursor(13,0);
      lcd.print("fsh");
	    
      // clear row 2 for display
      lcd.setCursor(0,1);
      lcd.print("");
      
	    
      // For loop to replay delay. created time counter to know how long until flush will happen.
     for (long n = 1500000L ; n >=0L ; n--) // n will be the timer count => roughly 1 minute and 5 second replace n value to get longer timer
      {
        if (n%23077 == 0){ // roughly every 23077 is a second, count up 1 second on LCD display
          s++;
          if (s == 10){ // if second is more than 10 count second tenth place up once and reduce s to 0
            s = 0;
            s2++;
            if(s2 == 6){ // convert 60 second to 1 minute
              m++;
              s2=0;
              if(m == 10){
                m2++;
                m=0;
              }
            }}
            ///Serial.println("Check for Loop");
            lcd.setCursor(0,1);
            lcd.print(m2); // Print tenth place of minute
            lcd.setCursor(1,1);
            lcd.print(m); // print minute
            lcd.setCursor(2,1);
            lcd.print(":");
            lcd.setCursor(3,1);
            lcd.print(s2); // print tenth place of second
            lcd.setCursor(4,1);
            lcd.print(s); // print second
            lcd.setCursor(0,1);
        }
      }/**/
     /*  Remove this code replacing with a for loop 
      lcd.begin (16, 2);       // Tell where to use on LCD. Not Needed
      lcd.print(countLCD);     // Display value of countLCD on the LCD screen. Not Needed
      delay(30000); // 5min Delay Flush. Won’t scare pets if they are playing near toilet 
     /**/
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
  
