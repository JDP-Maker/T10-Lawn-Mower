// GPS Module Code

// The ESP32 sends send 3.3V on the output pin when the mower is inside the GPS fence.
// when the mower leaves the GPS fence the pin is at 0 volts.
// The pin A7 is read by the adcman feature as analog.read cat be used anymore.

void Check_GPS_In_Out() {

// Run the ADCman to get the pin values as per the settings
ADCMan.run();
GPS_Fence_Signal = ADCMan.read(GPS_Fence_Signal_Pin);    // Read GPS in out status
GPS_Lock_Signal  = ADCMan.read(GPS_Lock_Pin);            // Read GPS Fixed status

// Print the value to the serial monitor
message_out.print("|GPS:");
message_out.print(GPS_Fence_Signal);
message_out.print("/");

if (GPS_Fence_Signal < 100) GPS_Inside_Fence = 0;   // Mower is Outside the GPS Fence
if (GPS_Fence_Signal > 100) GPS_Inside_Fence = 1;   // Mower is Inside the GPS Fence

    if (GPS_Inside_Fence == 0) message_out.print(":OUT");
    if (GPS_Inside_Fence == 1) message_out.print(":IN");

//message_out.print("|Lock:");
//message_out.print(GPS_Lock_Signal);
//message_out.print("/");

if (GPS_Lock_Signal < 100)  GPS_Lock_OK = 0;   // Mower is Outside the GPS Fence
if (GPS_Lock_Signal > 100)  GPS_Lock_OK = 1;   // Mower is Inside the GPS Fence
    
   if (GPS_Lock_OK == 0) message_out.print(":NoLOCK");
   if (GPS_Lock_OK == 1) message_out.print(":RTKFIX");
        
        // if there is no GPS Lock and the mower is running then keep within the whiole loop
        // until a GPS RTK lock is found.
        while ((GPS_Lock_OK == 0) && (Mower_Running == 1)) {          
          Motor_Action_Stop_Motors();                               // Stop Wheels
          Motor_Action_Stop_Spin_Blades();                          // Stop Blade
          message_out.println(F(""));
          message_out.print(F("- Checking for GPS Lock "));          
          message_out.print(F("| Lock:"));
          ADCMan.run();
          GPS_Lock_Signal = ADCMan.read(GPS_Lock_Pin);
          message_out.println(GPS_Lock_Signal); 
          delay(100);
          if (GPS_Lock_Signal < 50)  GPS_Lock_OK = 0;   // Mower is Outside the GPS Fence
          if (GPS_Lock_Signal > 50)  GPS_Lock_OK = 1;   // Mower is Inside the GPS Fence 
          Send_Mower_Running_Data();
          delay(1000);
          }
          
    
    message_out.print("|"); 
  
}
