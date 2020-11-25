void Check_if_Raining_From_Nano() {

  if (Rain_Sensor_Installed == 1) {
      
      if ((Rain_Detected == 1) || (Rain_Detected == 0)){                            // If the value recieved is equal to 1 or 0 as expected then print the value to the serial monitor
        message_out.print(F("Rain:"));
        message_out.print(Rain_Detected);
        message_out.print("|");
        Print_Raining_LCD();
        if (Rain_Detected == 1) Rain_Hit_Detected = Rain_Hit_Detected + 1;
        if (Rain_Detected == 0) Rain_Hit_Detected = Rain_Hit_Detected - 1;
        if (Rain_Hit_Detected < 0) Rain_Hit_Detected = 0;
        }
      if ((Rain_Detected != 1) && (Rain_Detected !=0)) {
        message_out.print(F("Rain:"));
        message_out.print(Rain_Detected);
        message_out.print("|");
        Print_Raining_LCD();
        Rain_Detected = 0;
        Rain_Hit_Detected = Rain_Hit_Detected + 1; 
        }
      
    
  else {
    message_out.print(F("Rain:"));
    message_out.print("_|");  
    Print_Raining_LCD();
    Rain_Detected = 0;
    }
  
  message_out.print("RHit:");
  message_out.print(Rain_Hit_Detected);
  message_out.print("|");
  

if ( (Mower_Running == 1) && (Rain_Hit_Detected == Rain_Total_Hits_Go_Home) ) {
  Motor_Action_Stop_Motors();
  message_out.println(F(""));
  message_out.println(F("Rain detected"));
  message_out.println(F(""));
  Print_Raining_LCD();
  delay(2000);
  Manouver_Go_To_Charging_Station();            // If the Mower is running then go to the charge station. 
  }
  }
}
