
// Check the mower is inside (0) or outside (1) the perimeter wire
void Check_Wire_In_Out() {

  // If the perimeter wire sensor is de-activated
  if (Perimeter_Wire_Enabled == 0) {
      if (TFT_Screen_Menu == 1) {
        Outside_Wire = 0;
        //Data_Sent_Wire = 0;                                           // Resets the counter to send info to the TFT
        //Send_Mower_Running_Data();
        }    
      }


  // If the perimeter wire sensor is activated
  if (Perimeter_Wire_Enabled == 1) {
    UpdateWireSensor();                                               // Read the wire sensor and see of the mower is now  or outside the wire  
    ADCMan.run();
    PrintBoundaryWireStatus();        
    
    // OUTSIDE the wire
    if ( (perimeter.isInside(0)) == 0 )  {                            // Mower is OUTSIDE the wire
      Outside_Wire = 1;                                               // Outside wire variable is tuend on.
      if (Mower_Running == 1) Motor_Action_Stop_Motors();             // Stop immediatley the wheel motors
      if (LCD_Screen_Keypad_Menu == 1) Print_LCD_Wire();              // Update the LCD screem
      Outside_Wire_Count = Outside_Wire_Count + 1;                    // Count the number of times the mower is consecutiley outside the wire
                                                                      // If a certain number is reached its assumed thw mower is lost outside the wire.
      }
    
    // INSIDE the wire
    if ( (perimeter.isInside(0)) == 1 )   {
      Outside_Wire = 0;                                               // Outside wire variable is tuend off
      Outside_Wire_Count = 0;                                         // The number of outside wire counts is reset to 0
      Wire_Refind_Tries = 0;
    }
     
    }

  // If the mower consectivley detects its outside the wire a number of times
  // its assumed the mower is lost and a this search function is started to try and 
  // re-find the wire.  Otherwise the mower is hibernated.
  if (Outside_Wire_Count >= Outside_Wire_Count_Max) {
    if  (Action_On_Over_Wire_Count_Max == 1) Manouver_Hibernate_Mower();                  // Put the mower to sleep and wait
    if  (Action_On_Over_Wire_Count_Max == 2) Manouver_Outside_Wire_ReFind_Function();     // re-find Garden using Sonar 1 and wire detect
    
    if  (Action_On_Over_Wire_Count_Max == 3) {     // try to locate the wire using wire find function
      if (LCD_Screen_Keypad_Menu == 1) {
          lcd.clear();
          lcd.print("Wire Find");
          lcd.setCursor(0,1);
          lcd.print("Special Function");
          }
      Loop_Cycle_Mowing = 999;
      if ((WIFI_Enabled == 1) && (Manuel_Mode == 0)) Get_WIFI_Commands();                                   // TX and RX data from NodeMCU
      delay(2000);
      Outside_Wire_Count = 0;
      Specials_Find_Wire_Track();                  
      SetPins_ToGoBackwards();                                                              // Set the mower to back up
      Motor_Action_Go_Full_Speed(); 
      delay(1000);
      Motor_Action_Stop_Motors();  
      UpdateWireSensor();                                               // Read the wire sensor and see of the mower is now  or outside the wire  
      ADCMan.run();
      PrintBoundaryWireStatus(); 
      delay(1000);
      UpdateWireSensor();                                               // Read the wire sensor and see of the mower is now  or outside the wire  
      ADCMan.run();
      PrintBoundaryWireStatus(); 
      Wire_Refind_Tries = Wire_Refind_Tries + 1;
      Loop_Cycle_Mowing = 0;
      if ((WIFI_Enabled == 1) && (Manuel_Mode == 0)) Get_WIFI_Commands();                                   // TX and RX data from NodeMCU
      message_out.println(F(""));
      message_out.print(F("|Wire Refind Atempts:"));
      message_out.print(Wire_Refind_Tries);
      message_out.print("|");
      message_out.println(F(""));
      if (Wire_Refind_Tries > 4) {
        Motor_Action_Stop_Motors(); 
        lcd.clear();
        Mower_Error = 1;
        message_out.println(F(""));
        message_out.println("Max refind tries exceeded - Parking the Mower");
        delay(2000);
      
      }
      
    }
  }
    
  }



//Check that boundary wire is turned on
//************************************************************************************
void TestforBoundaryWire()  {
  ADCMan.run();
  UpdateWireSensor();
  
  if (Perimeter_Wire_Enabled == 1) {                                               // Perimeter use is ON - Perimter_USE can be turned on or off in the setup.

    // Checks the MAG field of the boundary wire
    MAG_Now = perimeter.getMagnitude(0);

   
    // if the MAG fiels is strong then the wire is on.
    if (   (MAG_Now < -50 ) || (MAG_Now > 50 )  ) {
      Wire_Detected = 1;                                            // Wire is detected  
      Wire_Off = 0;                                                 // Resets the counter
      if (LCD_Screen_Keypad_Menu == 1) Print_LCD_Wire_ON();  
      }

    // If the MAG field is very low between these values we can assume the wire is off
    if ( (MAG_Now > -20 ) && (MAG_Now < 20 )  ) {
      Wire_Detected = 0;
      if (LCD_Screen_Keypad_Menu == 1) Print_LCD_NO_Wire();
      Wire_Off = Wire_Off + 1;
      
      // If the mower is docked or Parked then the TFT screen just shows a wire off warning
      if ( (Wire_Off > 5) && (Mower_Docked == 0) && (Mower_Parked == 0) ) {
        message_out.println(F("Wire Test Failed - Hibernating Mower"));
        Manouver_Hibernate_Mower();      // Send the mower to sleep
        }
      } 

    message_out.print(F("|Wire"));
    message_out.print(F(":"));
    if (Wire_Detected == 0) message_out.print(F("OFF|"));
    if (Wire_Detected == 1) message_out.print(F("ON|"));
    }

  // If the wire is in test mode
  if (Perimeter_Wire_Enabled == 0) {   
    message_out.print(F("Wire"));
    message_out.print(F(":"));                                            
    message_out.print(F("DISABLED|"));
    Wire_Detected = 1;

  }
}


void UpdateWireSensor()   {
  if (millis() >= nextTime)  {
    nextTime = millis() + 50;
    if (perimeter.isInside(0) != inside) {
      inside = perimeter.isInside(0);
      counter++;
    }
  }
}


void PrintBoundaryWireStatus() {

  message_out.print(F("|IN/OUT:"));
  message_out.print((perimeter.isInside(0)));
  message_out.print(F("|Mag:"));
  message_out.print((int)perimeter.getMagnitude(0));
  message_out.print(F("|Smag:"));
  message_out.print((int)perimeter.getSmoothMagnitude(0));
  message_out.print(F("|Q:"));
  message_out.print((perimeter.getFilterQuality(0)));
  message_out.print(F("|"));
  }
