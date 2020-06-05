
//Global Constant 
#include <LiquidCrystal.h>
//#include <Servo.h>
#include <SharpIR.h>

#define ir A1
#define model 1080

//Servo ServoMotor;

//int TrgPin = A1; // Initiate Analog Signal
//int SensorValue = 0; // Convert Analog Signal to Digital
int wait = 9;
int changeMode = 0;
int Reset = 0;
int Mode = 0;
int CountN = 0; // Count how long the obeject remains in front of sensor
int countLCD = 0; // Count the ammount of time object trigger the sensor code
int HArray [25]={};
int dst = 0;
int Pin1 = 9; 
int Pin2 = 8; 
int Pin3 = 7; 
int Pin4 = 6; 
int _step = 0; 
boolean dir = false;// false=clockwise, true=counter clockwise
int count=0;
char dis ;


LiquidCrystal lcd (12, 11, 5, 4, 3, 2);
SharpIR SharpIR(ir,model);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // start Serial communication: at 9600 baurate
 // pinMode (6, OUTPUT); // set output for LED
  pinMode(Pin1, OUTPUT);  
  pinMode(Pin2, OUTPUT);  
  pinMode(Pin3, OUTPUT);  
  pinMode(Pin4, OUTPUT);  
  // inital PIN 10
  //ServoMotor.attach(10); //Initialized the Signal for Servo to be On then. 
  //ServoMotor.write(0); //Keep it zero on 10. This way the Motor won't power on 
  //delay(100);          //Servo Motor being on draws too much power from the board
                       //Will cause IR sensor measurement to drop by 80-40 inches
                       //Keep Signal Pin on 10 to start prevent the draw in power from servo

   lcd.begin (16, 2); //
   lcd.setCursor(0,0);
   lcd.print("Used: ");
   lcd.setCursor(14,1);
   lcd.print("M");
   lcd.setCursor(15,1);
   lcd.print(wait);
  /*Serial.print(CountN);
  Serial.print(", CheckA");
  Serial.println();
  delay(100);*/
}

void loop() {
  // put your main code here, to run repeatedly:
 //unsigned long startTime=millis();
 dst=SharpIR.distance();
 dst=(dst/2.54);
/* Serial.print(dst);
 Serial.print(", CheckPoint1");
 Serial.println();
 delay(100);*/
 HArray[0] = dst;


for (int ArraySlot = 1; ArraySlot < 25; ArraySlot++){
 /*Serial.print(HArray[ArraySlot-1]);
 Serial.print(", CheckPoint2");
 Serial.println();
 delay(100);*/
  
  dst = SharpIR.distance();
  dst = (dst/2.54);
 /*Serial.print(HArray[ArraySlot]);
 Serial.print(", CheckPoint2-a");
 Serial.println();
 Serial.println();
 delay(100);*/

 HArray[ArraySlot] = dst;

 /*Serial.print(HArray[ArraySlot]);
 Serial.print(", CheckPoint2-b");
 Serial.println();
 delay(100);
 Serial.print(HArray[ArraySlot-1]);
 Serial.print(", CheckPoint2-c");
 Serial.println();
 delay(100);*/
 
if (HArray[ArraySlot-1] <= HArray[ArraySlot]){
 /*Serial.print(HArray[ArraySlot]);
 Serial.print(", Current3-a");
 Serial.println();
 delay(100);
 Serial.print(HArray[ArraySlot-1]);
 Serial.print(", Previous3-b");
 Serial.println();
 delay(100);
  /*HArray[ArraySlot] = dst;*/
  HArray[ArraySlot] = HArray[ArraySlot];
  /*Serial.print(HArray[ArraySlot-1]);
 Serial.print(", CheckPoint3-c");
 Serial.println();
 delay(100);
 Serial.print(HArray[ArraySlot]);
 Serial.print(", StoreCurrent3-d");
 Serial.println();
 delay(100);*/
}
else{
 /*Serial.print(HArray[ArraySlot]);
   Serial.print(", Current4-a");
   Serial.println();
   delay(100);
   Serial.print(HArray[ArraySlot-1]);
   Serial.print(", Previous-b");
   Serial.println();
   delay(100);*/
  HArray[ArraySlot] = HArray[ArraySlot-1];
   /*Serial.print(HArray[ArraySlot]);
   Serial.print(", StorePrevious4-c");
   Serial.println();
   delay(100);
   Serial.print(HArray[ArraySlot-1]);
   Serial.print(", CheckPoint4-d");
   Serial.println();
   delay(100);*/

}

/*Serial.print(ArraySlot);
 Serial.print(", Array Number");
 Serial.println();
Serial.println();
 delay(100);*/
}

 //unsigned long calcTime=millis()-startTime;
 //long SensorValue = analogRead(A1);
 dst = HArray[24];


 
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
 Serial.print(dst);
 Serial.print(", Distance");
 Serial.println();
 Serial.print("Change Value: ");
 Serial.println(changeMode);
 Serial.print("Time: ");
 Reset = millis()%2000;
 Serial.print(Reset);
    // after inactivity clear change mode to prevent switching to new mode over time
   if (Reset >= 0 && Reset <= 10)
   {
    if (changeMode >= 1){
     Serial.println("**********Mode Change Cleared********");
     
     changeMode = 0;
    }
   }
 //Serial.print(SensorValue);*/
 Serial.println();
 Serial.println();
 delay(100);
 //SensorValue = 0;
 //CountN = 0;
 /*Serial.print(CountN);
 Serial.print(", CheckPoint-5");
 Serial.println();*/

 
 // Trigger Event to wait if user is within 13 inches of the sensor
 // Guard from quick passing by
  

  if (dst >= 1 && dst <= 20){  //trigger wait event if object move in front of sensor
    //digitalWrite (6, HIGH);
    CountN = CountN+1; // Count how many time we stay connected
    Serial.print(CountN);
    Serial.print(", CheckPoint-6");
    Serial.println();
    delay(100);/**/
  }
  else{
    //digitalWrite (6, LOW); // Light for Visual during checking
    /*Serial.print(CountN);
    Serial.print(", CheckPoint-7");
    Serial.println();
    delay(100);*/
    // If link break after certain count we trigger next event
    // Flush will occur
    // Reset counter for next event
    // We will also guard against people walking by quickly. User "Cat" must be there for more than 8 count
    // If not more than 8 we clear counter and start at zero.
    // If counter is more than 8 then we wait about 10sec before flush. This way we won't scare the cat.
    
    
    if (CountN >=12 ){
      Serial.print (CountN);   // Loger to see count
      Serial.print (", Flush");  // Trigger event when object move away from sensor
      Serial.println();

      CountN = 0; // reset timer time
      countLCD = countLCD + 1; // Count the number of time sensor is triggered
      
      /*for (int i = 100000; i < 100000; i++){
        lcd.begin (16, 2);
        lcd.print(i);
      }*/

      lcd.setCursor(13,0);
      lcd.print("WaT");
      lcd.setCursor(6,0);
      lcd.print(countLCD);
      // Delay counter for LCD display
      int s = 0;
      int s2 = 0;
      int m = 0;
      int m2 =0;
      lcd.setCursor(0,1);
      lcd.print("");
       lcd.setCursor(14,1);
       lcd.print("M");
       lcd.setCursor(15,1);
       lcd.print(wait);
      for (long n = 1384615L*wait ; n >=0L ; n--)
      {
        if (n%23077 == 0){
          s++;
          if (s == 10){
            s = 0;
            s2++;
            if(s2 == 6){
              m++;
              s2=0;
              if(m == 10){
                m2++;
                m=0;
              }
            }}
            //Serial.println("Check for Loop");
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
      

      //delay(300000L); // Delay Flush so won't scare Cat
    
    // Initiate Flush. 
      //ServoMotor.attach(9); // Initialize the Servo signal to PIN 9 to start up Motor only when needed
      //ServoMotor.write(120); // Pull Lever up to start flush
      lcd.setCursor(13,0);
      lcd.print("Pus");
      Serial.println("Begin");
      Step_motor1(50000L,true);
       delay(2000);  // Wait time for water to flush. 
      //ServoMotor.write(0); // Close Hole allow Water To fill back up
      lcd.setCursor(13,0);
      lcd.print("RLE");
      Step_motor1(50000L, false);
      Clear_motor();
      delay (2000); // wait to let water fill back up before allowing program to run again
      //ServoMotor.attach(10); // Move signal back to 10 so Motor is not power on. 
      lcd.setCursor(0,1);
      lcd.print("00:00");
      changeMode = 0;
    }
    else if (CountN > 0 && CountN <= 8){
      Serial.print (CountN);
      Serial.print (", QuickMove");  // Trigger event when object move away from sensor
      Serial.println();
      CountN = 0;

      // add mode change for debugging mechanical issues
      // wave over the ir sensor fast 3 times in a row within 20second trigger mode switch
      // cycle throught 1 minute, 5 minute, and 9 minute mode
      // M 9 is the default function
      // added LCD screen display for Mode to allow user to know which mode we are in.
      // prevent us from having to open up and reprograming to the time we need for mechanical debugging
      changeMode++;
      if (changeMode == 3)
     {
      Mode++;
      switch (Mode){
       case 1:
       wait = 0;
       changeMode = 0;
       Serial.println("TEST MODE Activate");
       lcd.setCursor(14,1);
       lcd.print("M");
       lcd.setCursor(15,1);
       lcd.print(wait);
       break;
       case 2:
       wait = 5;
       changeMode =0;
       Serial.println("5 Min Mode");
       lcd.setCursor(14,1);
       lcd.print("M");
       lcd.setCursor(15,1);
       lcd.print(wait);
       break;
       case 3:
       wait = 9;
       changeMode = 0;
       Serial.println("9 Min Mode");
       Mode = 0;
       lcd.setCursor(14,1);
       lcd.print("M");
       lcd.setCursor(15,1);
       lcd.print(wait);
       break;
     }}
      delay(100);
    }
    }
  

    delay(100);
  }



void Step_motor1 (long numRotation, bool Direction){
for (long n = numRotation; n >= 0; n--){    
  Serial.print("Step: ");
  Serial.println(_step);
 switch(_step){ 
   case 0: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, HIGH); 
   break;  
   case 1: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, HIGH); 
     digitalWrite(Pin4, HIGH); 
   break;  
   case 2: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, HIGH); 
     digitalWrite(Pin4, LOW); 
   break;  
   case 3: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, HIGH); 
     digitalWrite(Pin4, LOW); 
   break;  
   case 4: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, LOW); 
   break;  
   case 5: 
     digitalWrite(Pin1, HIGH);  
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, LOW); 
   break;  
     case 6: 
     digitalWrite(Pin1, HIGH);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, LOW); 
   break;  
   case 7: 
     digitalWrite(Pin1, HIGH);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, HIGH); 
   break;  
   default: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, LOW); 
   break;  
 } 
 if(Direction){ 
   _step++; 
 }else{ 
   _step--; 
 } 
 if(_step>7){ 
   _step=0; 
 } 
 if(_step<0){ 
   _step=7; 
 } 
 delay(1); 
}
}

void Clear_motor()
{
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, LOW);
}
