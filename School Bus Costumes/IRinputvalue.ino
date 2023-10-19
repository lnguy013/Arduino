void IRinputvalue (){
  if (irrecv.decode(&results)){// Returns 0 if no data ready, 1 if data ready.     
      
    IRvalue = results.value  ;// Results of decoding are stored in result.value     
    Serial.println(" ");     
    Serial.print("Code: ");     
    Serial.println(IRvalue); //prints the value a a button press     
    Serial.println(" ");     

    if ((IRvalue != -1)) {OUTPUTvalue = IRvalue;}

    irrecv.resume(); 
    //Serial.print("Check Log 1: ");
    //Serial.println(IRvalue); //prints the value a a button press     
    //Serial.println(" ");   
  }
}
