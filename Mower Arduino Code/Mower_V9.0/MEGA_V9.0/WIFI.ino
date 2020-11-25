// Blynk TX and RX functions to communicate with the MEGA and NODEMCU
// Each transmission has a label n or p or q or 

// USE V5 Blynk  12th Feb 2019

void Get_WIFI_Commands() {
  Receive_Data_From_NODEMCU(); 
  delay(5); 
  Transmit_All_To_NODEMCU(); 
  }

void Receive_Data_From_NODEMCU() {
  while(Serial2.available()>0){
      val_WIFI = Serial2.parseInt();
      if(Serial2.read()== '\p'){
        delay(1000);
        Execute_Blynk_Command_To_Mower();
        }
  }
 }

void Receive_WIFI_Manuel_Commands() {
  while(Serial2.available()>0){
      val_WIFI = Serial2.parseInt();
      if(Serial2.read()== '\p'){
        delay(5);
        Execute_Manuel_Blynk_Command_To_Mower();
        }
  }
 }

void Transmit_All_To_NODEMCU() {
  delay(5);
  Serial2.print(Volts);
  Serial2.println("\g");
  delay(5);
  Serial2.print(Loop_Cycle_Mowing);
  Serial2.println("\c");
  delay(5);
  Serial2.print(Mower_Docked);
  Serial2.println("\d");
  delay(5);
  Serial2.print(Mower_Running);
  Serial2.println("\z");
  delay(5);
  Serial2.print(Mower_Parked);
  Serial2.println("\y");
  delay(5);
  Serial2.println(Charging);
  Serial2.println("\o");
  delay(5);
  Serial2.println(Tracking_Wire);
  Serial2.println("\m");   
  delay(5);
  }


void Transmit_APP_Buttons_Status() {

  message_out.println(F(""));
  message_out.print(F("|Updating APP Buttons"));
  
  delay(200);
  Serial2.print(Compass_Activate);
  Serial2.println("\a");
  delay(200);
  Serial2.print(Compass_Heading_Hold_Enabled);
  Serial2.println("\b");
  delay(200);
  Serial2.print(GYRO_Enabled);
  Serial2.println("\c");
  delay(200);
  Serial2.print(Sonar_1_Activate);
  Serial2.println("\d");
  delay(200);
  Serial2.print(Sonar_2_Activate);
  Serial2.println("\e");
  delay(200);
  Serial2.print(Sonar_3_Activate);
  Serial2.println("\f");
  delay(200);
  Serial2.print(Bumper_Activate_Frnt);
  Serial2.println("\g");
  delay(200);

  message_out.println("");
  message_out.print(F("Compass_Activate :"));
  message_out.println(Compass_Activate);
  message_out.print(F("Heading Hold TX :"));
  message_out.println(Compass_Heading_Hold_Enabled);  
  message_out.print(F("GYRO TX :"));
  message_out.println(GYRO_Enabled);
  message_out.print(F("Sonar 1 ON :"));
  message_out.println(Sonar_1_Activate);
  message_out.print(F("Sonar 2 ON :"));
  message_out.println(Sonar_2_Activate);
  message_out.print(F("Sonar 3 ON :"));
  message_out.println(Sonar_3_Activate);
  message_out.print(F("Bumper ON:"));
  message_out.println(Bumper_Activate_Frnt);
  message_out.println("");
  }

void Execute_Blynk_Command_To_Mower() {

// Updates the Serial Monitor with the latest Blynk Commands and can be used to start
// functions on the mower when the command is recieved.
delay(30);


// Exit Dock to Zone 1
 if (val_WIFI == 14) {
       if (Mower_Docked == 1)   {  
    
       // Update the TFT Display
       message_out.println(F(""));
       message_out.println(F("Updating TFT: WIFI Exit dock"));
       Exiting_Dock = 1;
       Mower_Error_Value = 0;
       Send_Mower_Docked_Data();                                   // Send the Docked TX Data package to the mower.
         
       message_out.println(F(""));
       message_out.print(F("WIFI Command: ")); 
       message_out.print(val_WIFI);
       message_out.print(F("Exit Dock| "));
       message_out.println(F("Zone 1"));
       lcd.clear();
       lcd.print(F("WIFI Start"));
       lcd.setCursor(0,1);
       lcd.print(F("Exit Dock Z1"));
       delay(500);
       lcd.clear();
       Exit_Zone = 1;
       Track_Wire_Itterations = Track_Wire_Zone_1_Cycles;
       Manouver_Exit_To_Zone_X();
       }
   }

 // Quick Start Button in Blynk App
 if (val_WIFI == 13) {
   message_out.println(F(""));
   message_out.print(F("WIFI Command:")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Quick Start"));
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(F("WIFI Start"));
   message_out.println(F("Quick Start"));
   if (Mower_Docked == 0) { 
     Manouver_Start_Mower();
     lcd.clear();    
     if (TFT_Screen_Menu == 1) Send_Mower_Docked_Data();    // Send the Docked TX Data package to the mower.
     }    
   else message_out.println(F("Mower Docked - Quick Start not possible"));   
   }

// Go To Dock Button in Blynk App
 if (val_WIFI == 12) {
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Go To Dock"));
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(F("WIFI Go To Dock"));
   Menu_Mode_Selection = 0;                                      // Releases the loop in the membrane button section.
   Motor_Action_Stop_Spin_Blades();
   Motor_Action_Stop_Motors();
   delay(1000);
   lcd.clear();
   Manouver_Go_To_Charging_Station();      
   }

// STOP / Cancel Button in Blynk App
 if (val_WIFI == 11)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Pause/Stop"));
   Manouver_Park_The_Mower(); 
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   }

// Manuel Button in Blynk App
 if (val_WIFI == 15)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Manuel Mode"));
   Manouver_Park_The_Mower(); 
   delay(1000);
   Manouver_Manuel_Mode(); 
   Turn_On_Relay(); 
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   }
   
// Automatic RANDOM Button in Blynk App
 if (val_WIFI == 16)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Automatic Mode RANDOM"));
   if (LCD_Screen_Keypad_Menu == 1) {
       lcd.clear();
       lcd.print("Auto Random");
       lcd.setCursor(0,1);
       lcd.print("Pattern");
       delay(200);
       lcd.clear();
       }
   if (Mower_Running == 0) {
    Manouver_Park_The_Mower(); 
    Turn_On_Relay(); 
    }
   Pattern_Mow = 0;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
  }

// Automatic SPIRAL Button in Blynk App
 if (val_WIFI == 21)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Automatic Mode SPIRAL"));
   
   if (LCD_Screen_Keypad_Menu == 1) {
         lcd.clear();
         lcd.print("Auto Spiral");
         lcd.setCursor(0,1);
         lcd.print("Pattern");
         delay(200);
         lcd.clear();
         }
   if (Mower_Running == 0) {
    Manouver_Park_The_Mower(); 
    Turn_On_Relay(); 
    }
   Pattern_Mow = 2;

   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
  }

// Automatic SPIRAL Button in Blynk App
 if (val_WIFI == 22)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Automatic Mode PARALLEL"));
   if (LCD_Screen_Keypad_Menu == 1) {
       lcd.clear();
       lcd.print("Auto Parallel");
       lcd.setCursor(0,1);
       lcd.print("Pattern");
       delay(200);
       lcd.clear();
       }
   if (Mower_Running == 0) {
    Manouver_Park_The_Mower(); 
    Turn_On_Relay(); 
    }
   Pattern_Mow = 1;

   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
  }

// SETTINGS MOWER

// Compass Setting Via WIFI.
 if (val_WIFI == 40)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Compass ON"));
   Compass_Activate = 1;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(19 , 1);
   EEPROM.write(20 , Compass_Activate);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }
 if (val_WIFI == 41)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Compass OFF"));
   Compass_Activate = 0;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(19 , 1);
   EEPROM.write(20 , Compass_Activate);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }

// Heading Hold
 if (val_WIFI == 42)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Heading Hold ON"));
   Compass_Heading_Hold_Enabled = 1;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(59 , 1);
   EEPROM.write(60 , Compass_Heading_Hold_Enabled);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }
  
 if (val_WIFI == 43)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Heading Hold OFF"));
   Compass_Heading_Hold_Enabled = 0;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(59 , 1);
   EEPROM.write(60 , Compass_Heading_Hold_Enabled);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }

// GYRO
 if (val_WIFI == 44)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|GYRO ON"));
   GYRO_Enabled = 1;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once      
   EEPROM.write(109 , 1);
   EEPROM.write(110, GYRO_Enabled);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }
  
 if (val_WIFI == 45)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|GYRO OFF"));
   GYRO_Enabled = 0;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(109 , 1);
   EEPROM.write(110, GYRO_Enabled);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }


// SONAR 1 Setting Via WIFI.
 if (val_WIFI == 47)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|SONAR 1 ON"));
   Sonar_1_Activate = 1;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(37, 1);
   EEPROM.write(38, Sonar_1_Activate);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }
   
 if (val_WIFI == 48)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|SONAR 1 OFF"));
   Sonar_1_Activate = 0;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(37, 1);
   EEPROM.write(38, Sonar_1_Activate);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }


// SONAR 2 Setting Via WIFI.
 if (val_WIFI == 49)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|SONAR 2 ON"));
   Sonar_2_Activate = 1;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(39, 1);
   EEPROM.write(40, Sonar_2_Activate);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }
  
 if (val_WIFI == 50)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|SONAR 2 OFF"));
   Sonar_2_Activate = 0;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(39, 1);
   EEPROM.write(40, Sonar_2_Activate);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }


// SONAR 3 Setting Via WIFI.
 if (val_WIFI == 51)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|SONAR 3 ON"));
   Sonar_3_Activate = 1;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(41, 1);
   EEPROM.write(42, Sonar_3_Activate);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }

  
 if (val_WIFI == 52)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|SONAR 3 OFF"));
   Sonar_3_Activate = 0;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(41, 1);
   EEPROM.write(42, Sonar_3_Activate);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }


// Bumper Setting Via WIFI.
 if (val_WIFI == 53)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Bumper ON"));
   Bumper_Activate_Frnt = 1;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(90 , 1);
   EEPROM.write(91 , Bumper_Activate_Frnt);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }

  
 if (val_WIFI == 54)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Bumper OFF"));
   Bumper_Activate_Frnt = 0;
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   EEPROM.write(90 , 1);
   EEPROM.write(91 , Bumper_Activate_Frnt);
   message_out.println(F("Saved to EEPROM"));
   message_out.println(F(" "));
   }


// UPDATE THE WIFI APP WITH THE BUTTON STATUS
// This is a 2 step process.  First the MEGA receives a code from the App/NodeMCU board
// That it should stop the loop and get ready to transmit the data
// On the secnd command the data is sent.
// This ensures the MEGA is synced to the NodeMCU
 
 if (val_WIFI == 46)  {    
   message_out.println(F(""));
   message_out.println(F("Val 46 received"));
   
   // only go into the wait mode if the mower is parked or docked.
   if ( (Mower_Docked == 1) || (Mower_Parked == 1)) {   
    message_out.println(F("Waiting..."));
    Menu_NodeMCU_Complete = false;
    
    while (Menu_NodeMCU_Complete == false) {                      
         while(Serial2.available()>0){
         val_WIFI = Serial2.parseInt();
         if(Serial2.read()== '\p'){
         delay(200);         
          // Receive_Data_From_NODEMCU();                  // Look for the transmission signal
          if (val_WIFI == 55)  {                        // If the signal arrived send the data
            message_out.println(F(""));
            message_out.println(F("Updating WIFI Buttons"));
            message_out.println(F(""));
            Transmit_APP_Buttons_Status();              // Send the button status data
            Menu_NodeMCU_Complete = true;               // break the while loop
            }
         }
      }
               
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
   }
  }
}


}


void Execute_Manuel_Blynk_Command_To_Mower() {
// insert wheel motions here.

 if (val_WIFI == 16)  {    
   message_out.println(F(""));
   message_out.print(F("WIFI Command: ")); 
   message_out.print(val_WIFI);
   message_out.println(F("|Automatic Mode"));
   Manouver_Park_The_Mower(); 
   Turn_On_Relay(); 
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
  }

 if (val_WIFI == 17)  {    
   message_out.print(F("WIFI")); 
   message_out.print(val_WIFI);
   message_out.print(F("|Wheel Forward"));
   SetPins_ToGoForwards(); 
   Motor_Action_Go_Full_Speed();
   delay(300);
   Motor_Action_Stop_Motors();
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
  }

 if (val_WIFI == 18)  {    
   message_out.print(F("WIFI:")); 
   message_out.print(val_WIFI);
   message_out.print(F("|Wheel Reverse"));
   SetPins_ToGoBackwards(); 
   Motor_Action_Go_Full_Speed();
   delay(300);
   Motor_Action_Stop_Motors();
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
  }

 if (val_WIFI == 19)  {    
   message_out.print(F("WIFI:")); 
   message_out.print(val_WIFI);
   message_out.print(F("|Wheel Left"));
   SetPins_ToTurnLeft();
   Motor_Action_Go_Full_Speed();
   delay(200);
   Motor_Action_Stop_Motors();
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
  }

 if (val_WIFI == 20)  {    
   message_out.print(F("WIFI:")); 
   message_out.print(val_WIFI);
   message_out.print(F("|Wheel Right"));
   SetPins_ToTurnRight();
   Motor_Action_Go_Full_Speed();
   delay(200);
   Motor_Action_Stop_Motors();
   val_WIFI = 0;   // restes val2 to zero so the command is only executed once
  }
  

}


void Update_Blynk_Start_Conditions() {

  Serial2.print(Compass_Activate);
  Serial2.println("\a");
  delay(5);
  Serial2.print(Loop_Cycle_Mowing);
  Serial2.println("\b");
  delay(5);
  Serial2.print(Mower_Docked);
  Serial2.println("\c");
  delay(5);
  Serial2.print(Mower_Running);
  Serial2.println("\d");
  delay(5);
  Serial2.print(Mower_Parked);
  Serial2.println("\e");
  delay(5);
  Serial2.println(Charging);
  Serial2.println("\f");
  delay(5);
  Serial2.println(Tracking_Wire);
  Serial2.println("\g"); 
  } 
