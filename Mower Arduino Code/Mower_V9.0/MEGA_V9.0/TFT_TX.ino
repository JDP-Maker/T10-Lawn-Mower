
// Transmits 7 Data Values to the TFT MEGA on Serial3 Com Port.
// The data values are declared below for the different Menu
// Commands.  This standardises the data transfer method for all
// functions.
//
// Values are transfered from the Mower MEGA to the TFT MEGA for editing in
// the TFT GUI.  The values are then sent back and stored to EEPROM on the MOWER
// MEGA so the mower can carry out the instructions according to the user settings


void TX_7_Data_Values() {
      message_out.println("Sending Data Sets");
      delay(200); 
      Serial3.print(Data1);
      Serial3.println("\a");
      delay(200);  
      Serial3.print(Data2);
      Serial3.println("\b");
      delay(200);  
      Serial3.print(Data3);
      Serial3.println("\c");
      delay(200);  
      Serial3.print(Data4);
      Serial3.println("\d");
      delay(200);
      Serial3.print(Data5);
      Serial3.println("\e");
      delay(200);
      Serial3.print(Data6);
      Serial3.println("\f");
      delay(200);
      Serial3.print(Data7);
      Serial3.println("\g");
      delay(200);
      
      message_out.print(F("Data1:"));
      message_out.println(Data1);
      message_out.print(F("Data2:"));
      message_out.println(Data2);
      message_out.print(F("Data3:"));
      message_out.println(Data3);  
      message_out.print(F("Data4:"));
      message_out.println(Data4);
      message_out.print(F("Data5:"));
      message_out.println(Data5);
      message_out.print(F("Data6:"));
      message_out.println(Data6);
      message_out.print(F("Data7:"));
      message_out.println(Data7);    
      }


void Send_Data_To_TFT() {
    // Depending on the code received the following data set is sent through the Serial 3 port.
    
    // Menu Sonar
    if (TFT_Menu_Command == 10) {
      message_out.println("TX Sonar to TFT");
      Data1 = Sonar_1_Activate;
      Data2 = Sonar_2_Activate;
      Data3 = Sonar_3_Activate;
      Data4 = maxdistancesonar;
      Data5 = Max_Sonar_Hit;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();

      message_out.print(F("S1 ON = "));
      message_out.println(Sonar_1_Activate);
      message_out.print(F("S2 ON = "));
      message_out.println(Sonar_2_Activate);
      message_out.print(F("S3 ON = "));
      message_out.println(Sonar_3_Activate);
      message_out.print(F("Sonar Max Distance = "));
      message_out.println(maxdistancesonar);
      message_out.print(F("Sonar Sensitivity = "));
      message_out.println(Max_Sonar_Hit);
      message_out.println(F(" "));
      }

    
// 11 is sometimes read if a serial port miscommunication occurs therefore this
// number is not used to start communication from the MEGA:
    if (TFT_Menu_Command == 11) {
      message_out.println("False Command");      
      }


// Navigation Menu is selected on the TFT
    if (TFT_Menu_Command == 9) {
      message_out.println("TX Nav to TFT");
      
      Serial3.print(GPS_Enabled);
      Serial3.println("\a");
      delay(200);  

      message_out.print(F("GPS Enabled = "));
      message_out.println(GPS_Enabled);   
      }


// Battery Menu is selected on the TFT
    if (TFT_Menu_Command == 26) {
      message_out.println("TX Battery to TFT");
      float Temp = Battery_Min * 10;          // Create Temp float value to transfer the decimal to the int
      int Temp2 = Temp;
      Data1 = Temp2;
      Data2 = Low_Battery_Instances_Chg;
      Data3 = 0;
      Data4 = 0;
      Data5 = 0;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();
      message_out.print(F("Battery Min = "));
      message_out.println(Battery_Min);
      message_out.print(F("Battery Sensitivity = "));
      message_out.println(Low_Battery_Instances_Chg);
      message_out.println(" ");
      }

// Setup Other Menu is selected on the TFT
    if (TFT_Menu_Command == 30) {
      message_out.println("TX Setup Other");
      
      Serial3.print(PCB);
      Serial3.println("\a");
      delay(300);  

      message_out.print(F("PCB = "));
      if (PCB == 1) message_out.println(F("Enabled"));
      if (PCB == 0) message_out.println(F("Disabled"));
      message_out.println(" ");
      }


// Perimeter Wire Menu is selected on the TFT
    if (TFT_Menu_Command == 6) {
      message_out.println("TX Perimeter to TFT");
      Data1 = Perimeter_Wire_Enabled;
      Data2 = WIFI_Enabled;
      Data3 = Bumper_Activate_Frnt;
      Data4 = 0;
      Data5 = 0;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();
      message_out.print(F("Wire Sensor ON = "));
      message_out.println(Perimeter_Wire_Enabled);
      message_out.print(F("WIFI Enabled = "));
      message_out.println(WIFI_Enabled);
      message_out.print(F("Bumper ON = "));
      message_out.println(Bumper_Activate_Frnt);
      message_out.println(F(" "));
      }


// Rain Sensor Menu is selected on the TFT
    if (TFT_Menu_Command == 12) {
      message_out.println("TX Rain to TFT");
      Data1 = Rain_Sensor_Installed;
      Data2 = Rain_Total_Hits_Go_Home;
      Data3 = 0;
      Data4 = 0;
      Data5 = 0;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();

      message_out.print(F("Rain Sensor ON = "));
      message_out.println(Rain_Sensor_Installed);
      message_out.print(F("Rain Sensitivity = "));
      message_out.println(Rain_Total_Hits_Go_Home);
      message_out.println(F(" "));
      }


// Wheel Motor Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 14) {
      message_out.println("TX Wheel PWM to TFT");
      Data1 = PWM_MaxSpeed_LH;
      Data2 = PWM_MaxSpeed_RH;
      Data3 = PWM_Slow_Speed_LH;
      Data4 = PWM_Slow_Speed_RH;
      Data5 = Slow_Speed_MAG / 10;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();

      message_out.print(F("PWM LH = "));
      message_out.println(PWM_MaxSpeed_LH);
      message_out.print(F("PWM RH = "));
      message_out.println(PWM_MaxSpeed_RH);
      message_out.print(F("PWM S LH = "));
      message_out.println(PWM_Slow_Speed_LH);
      message_out.print(F("PWM S RH = "));
      message_out.println(PWM_Slow_Speed_RH);
      message_out.print(F("Slow MAG = "));
      message_out.println(Slow_Speed_MAG);
      message_out.println(F(" ")); 
      }
      
      

// Blade Motor Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 15) {

      message_out.println("TX Blade Data to TFT");
      Data1 = PWM_Blade_Speed;
      Data2 = Cutting_Blades_Activate;
      Data3 = 0;
      Data4 = 0;
      Data5 = 0;
      Data6 = 0;
      Data6 = 0;
      TX_7_Data_Values();
     
      message_out.print(F("Blade Motor PWM = "));
      message_out.println(PWM_Blade_Speed);
      message_out.print(F("Cutting Blade Activated = "));
      message_out.println(Cutting_Blades_Activate);
      message_out.println(F(" "));
      }


// Motion Turns Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 16) {

      message_out.println("TX Turns Data to TFT");
      Data1 = Max_Cycles_Straight / 10 ;
      Data2 = Mower_Turn_Delay_Min / 100;
      Data3 = Mower_Turn_Delay_Max / 100;
      Data4 = Mower_Reverse_Delay / 100;
      Data5 = 0;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();
      
      message_out.print(F("Max Mow L = "));
      message_out.println(Max_Cycles_Straight);
      message_out.print(F("Turn Min = "));
      message_out.println(Mower_Turn_Delay_Min);
      message_out.print(F("Turn Max = "));
      message_out.println(Mower_Turn_Delay_Max);
      message_out.print(F("Reverse = "));
      message_out.println(Mower_Reverse_Delay);
      message_out.println(F(" "));

}


// Tracking to Exit Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 17) {
      message_out.println("TX Exit to TFT");

      Data1 = Track_Wire_Zone_1_Cycles / 100 ;
      Data2 = Track_Wire_Zone_2_Cycles / 100;
      Data3 = CCW_Tracking_To_Start;
      Data4 = 0;
      Data5 = 0;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();
      message_out.print(F("Track Wire Zone 1 = "));
      message_out.println(Track_Wire_Zone_1_Cycles);    
      message_out.print(F("Track Wire Zone 2 = "));
      message_out.println(Track_Wire_Zone_2_Cycles);      
      if (CCW_Tracking_To_Start == 0) {
        CW_Tracking_To_Start = 1;
        CCW_Tracking_To_Charge = 1;
        CW_Tracking_To_Charge = 0;
        message_out.println(F("Tracking to Charge = CCW"));
        message_out.println(F("Tracking to Start = CW"));
        }        
      if (CCW_Tracking_To_Start == 1) {
        CW_Tracking_To_Start = 0;
        CCW_Tracking_To_Charge = 0;
        CW_Tracking_To_Charge = 1;        
        message_out.println(F("Tracking to Charge = CW"));
        message_out.println(F("Tracking to Start = CCW"));       
        }
    }


// Charging Options Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 8) {
      message_out.println("TX Tracking to TFT");
    
      Serial3.print(Use_Charging_Station);
      Serial3.println("\a");
      delay(300); 

      message_out.print(F("Use Charging Station = "));
      message_out.println(Use_Charging_Station); 
      } 


// Find Wire Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 18) {
      message_out.println("TX Find Wire to TFT");
      Data1 = Max_Cycle_Wire_Find / 100 ;
      Data2 = Max_Cycle_Wire_Find_Back / 10;
      Data3 = Home_Wire_Compass_Heading;
      Data4 = 0;
      Data5 = 0;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();
      message_out.print(F("Wire Find Forwards / cylces = "));
      message_out.println(Max_Cycle_Wire_Find);      
      message_out.print(F("Wire Find Backwards / cylces = "));
      message_out.println(Max_Cycle_Wire_Find_Back);
      message_out.print(F("Home Compass Heading / degrees "));
      message_out.println(Home_Wire_Compass_Heading);      
      }

// Tracking PID Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 19) {
      message_out.println("TX Find Wire to TFT");
      
      Serial3.print(Max_Tracking_Turn_Left / 10);
      Serial3.println("\a");
      delay(300);  

      Serial3.print(Max_Tracking_Turn_Right / 10);
      Serial3.println("\b");
      delay(200);  

      P = P * 100;
      
      Serial3.print(P);
      Serial3.println("\c");
      delay(200);  

      message_out.print(F("Max Cycles Left Wheel = "));
      message_out.println(Max_Tracking_Turn_Left);
      message_out.print(F("Max Cycles Right Wheel = "));
      message_out.println(Max_Tracking_Turn_Right);         
      message_out.print(F("PID P = "));
      message_out.println(P/100);
      message_out.println(F(" "));     
      }


// Compass Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 27) {
      message_out.println("TX Compass to TFT");
      
      Serial3.print(Compass_Activate);
      Serial3.println("\a");
      delay(300);  

      Serial3.print(Compass_Heading_Hold_Enabled);
      Serial3.println("\b");
      delay(300);  

      Serial3.print(CPower * 10);
      Serial3.println("\c");
      delay(300);  
      
      Serial3.print(Compass_Setup_Mode);
      Serial3.println("\d");
      delay(200);  

      message_out.print(F("Compass Activated = "));
      message_out.println(Compass_Activate);
      message_out.print(F("Heading Hold Enabled = "));
      message_out.println(Compass_Heading_Hold_Enabled);          
      message_out.print(F("Compass Power = "));
      message_out.println(CPower);    
      message_out.print(F("Compass Setup Mode = "));
      message_out.println(Compass_Setup_Mode); 
      }


// GYRO Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 28) {

      Serial3.print(GYRO_Enabled);
      Serial3.println("\a");
      delay(300);  

      Serial3.print(GPower * 10);
      Serial3.println("\b");
      delay(300);

      message_out.print(F("GYRO Enabled= "));
      message_out.println(GYRO_Enabled); 
      message_out.print(F("GYRO Power = "));
      message_out.println(GPower);     
    }


// Wheel Blockage Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 29) {

      message_out.println("TX Wheel Block to TFT");
      Data1 = Wheel_Amp_Sensor_ON;
      float Temp = Max_Wheel_Amps * 10;
      int Temp2 = Temp;
      Data2 = Temp2;
      Data3 = 0;
      Data4 = 0;
      Data5 = 0;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();

    message_out.print(F("Wheel Amp ON: "));
        if (Wheel_Amp_Sensor_ON == 1) message_out.println("ON");
        if (Wheel_Amp_Sensor_ON == 0) message_out.println("OFF");   
    message_out.print(F("Wheel Amps Max: "));
    message_out.print(Max_Wheel_Amps);     
    }

// Alarm 1 Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 20) {
      message_out.println("TX Alarm1 TFT");

      Data1 = Alarm_1_ON;
      Data2 = Alarm_1_Hour;
      Data3 = Alarm_1_Minute;
      Data4 = Alarm_1_Repeat;
      Data5 = Alarm_1_Action;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();

      message_out.print(F("Alarm 1 ON = "));
      message_out.println(Alarm_1_ON);
      message_out.print(F("Alarm 1 Time = "));
      message_out.print(Alarm_1_Hour);
      message_out.print(F(":"));
      message_out.println(Alarm_1_Minute);
      message_out.print(F("Alarm 1 Repeat = "));
      message_out.println(Alarm_1_Repeat);
      message_out.print(F("Alarm 1 Action = "));
      message_out.println(Alarm_1_Action);    
      }


// Alarm 2 Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 21) {
      message_out.println("TX Alarm2 TFT");
      
      Data1 = Alarm_2_ON;
      Data2 = Alarm_2_Hour;
      Data3 = Alarm_2_Minute;
      Data4 = Alarm_2_Repeat;
      Data5 = Alarm_2_Action;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();

      message_out.print(F("Alarm 2 ON = "));
      message_out.println(Alarm_2_ON);
      message_out.print(F("Alarm 2 Time = "));
      message_out.print(Alarm_2_Hour);
      message_out.print(F(":"));
      message_out.println(Alarm_2_Minute);
      message_out.print(F("Alarm 2 Repeat = "));
      message_out.println(Alarm_2_Repeat);
      message_out.print(F("Alarm 2 Action = "));
      message_out.println(Alarm_2_Action);    
      }


// Alarm 3 Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 22) {
      message_out.println("TX Alarm3 TFT");
      
      Data1 = Alarm_3_ON;
      Data2 = Alarm_3_Hour;
      Data3 = Alarm_3_Minute;
      Data4 = Alarm_3_Repeat;
      Data5 = Alarm_3_Action;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();

      message_out.print(F("Alarm 3 ON = "));
      message_out.println(Alarm_3_ON);
      message_out.print(F("Alarm 3 Time = "));
      message_out.print(Alarm_3_Hour);
      message_out.print(F(":"));
      message_out.println(Alarm_3_Minute);
      message_out.print(F("Alarm 3 Repeat = "));
      message_out.println(Alarm_3_Repeat);
      message_out.print(F("Alarm 3 Action = "));
      message_out.println(Alarm_3_Action);    
      }


// Set Time Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 23) {
      message_out.println("Set Time TFT");
      if (PCB == 0) {
        Time t = rtc.time();
        Time_Hour = t.hr;
        Time_Minute = t.min;  
        }
      if (PCB == 1) {
        byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
        Read_DS3231_Time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
                 &year);
        Time_Hour = hour;
        Time_Minute = minute;
        Time_Second = second;
        }
 
      Serial3.print(Time_Hour);
      Serial3.println("\a");
      delay(300);  

      Serial3.print(Time_Minute);
      Serial3.println("\b");
      delay(200);  

      message_out.print(F("Time Now = "));
      message_out.print(Time_Hour);
      message_out.print(F(":"));
      message_out.println(Time_Minute);
      }



// Tip Sensor Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 24) {

      message_out.println("TX Tip Sensor to TFT");
      float Temp = Battery_Min * 10;          // Create Temp float value to transfer the decimal to the int
      Data1 = Angle_Sensor_Enabled;
      Data2 = Tip_Over_Sensor_Enabled;
      Data3 = 0;
      Data4 = 0;
      Data5 = 0;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();
      message_out.print(F("Angle ON = "));
      message_out.println(Angle_Sensor_Enabled);
      message_out.print(F("Tip ON = "));
      message_out.println(Tip_Over_Sensor_Enabled);
      message_out.println(" ");
}


// Pattern Mow Menu is selected on the TFT Screen
    if (TFT_Menu_Command == 25) {
      message_out.println("TX Pattern to TFT");
      float Temp = Battery_Min * 10;          // Create Temp float value to transfer the decimal to the int
      Data1 = Pattern_Mow;
      Data2 = Turn_90_Delay_LH / 10;
      Data3 = Turn_90_Delay_RH / 10;
      Data4 = Move_to_next_line_delay / 10;
      Data5 = Line_Length_Cycles;
      Data6 = 0;
      Data7 = 0;
      TX_7_Data_Values();
      if (Pattern_Mow == 0) message_out.println("OFF");
      if (Pattern_Mow == 1) message_out.println("Parallel");  
      if (Pattern_Mow == 3) message_out.println("Spiral"); 
      message_out.print(F("Turn 90° LH= "));
      message_out.println(Turn_90_Delay_LH);  
      message_out.print(F("Turn 90° RH= "));
      message_out.println(Turn_90_Delay_RH);      
      message_out.print(F("Distance to next row= "));
      message_out.println(Move_to_next_line_delay);      
      message_out.print(F("Row Length = "));
      message_out.println(Line_Length_Cycles);  
      message_out.println(" "); 
}



// Initial Start Up Values requested from the TFT
// The TFT first sends a request for the MEGA to 
    if (TFT_Menu_Command == 55) {
      message_out.println("TX Start Up Values TFT");

      if (PCB == 0) {
        Time t = rtc.time();
        message_out.println("PCB = 0 Time ");
        message_out.print(t.hr);
        message_out.print(":");
        message_out.println(t.min);
        Data4 = t.hr;
        Data5 = t.min;
        }
      if (PCB == 1) {        
        byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
        Read_DS3231_Time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
        Data4 = hour;
        Data5 = minute;
        Time_Second = second;
        }

      Data1 = Alarm_1_ON;
      Data2 = Alarm_2_ON;
      Data3 = Alarm_3_ON;
      //Data4 = see above times hr;
      //Data5 = see above times min;
      Data6 = GPS_Enabled;
      Data7 = Perimeter_Wire_Enabled;
      TX_7_Data_Values();

      message_out.print(F("Alarm 1 ON = "));
      message_out.println(Alarm_1_ON);
      message_out.print(F("Alarm 2 ON = "));
      message_out.println(Alarm_2_ON);
      message_out.print(F("Alarm 3 ON = "));
      message_out.println(Alarm_3_ON);
      message_out.print(F("|Time:"));
      message_out.print(Time_Hour);
      message_out.print(F(":"));
      if (Time_Minute < 10) message_out.print("0");
      message_out.println(Time_Minute);
      message_out.print(F("GPS:"));
      if (GPS_Enabled == 1) message_out.println("ON");   
      if (GPS_Enabled == 0) message_out.println("OFF"); 
      message_out.print(F("WIRE:"));
      if (Perimeter_Wire_Enabled == 1) message_out.println("ON");   
      if (Perimeter_Wire_Enabled == 0) message_out.println("OFF"); 

}



// Test Wire Sensor
    if (TFT_Menu_Command == 41) {
      message_out.println("Test Wire Sensor");

      bool Test_Complete = 0;

      for (int i = 0; i <= 30; i++) {

          if (i > 28) Test_Complete = 1;
            ADCMan.run();
            // ADCMan.setCapture(pinPerimeterLeft, 1, 0);
          
            if (millis() >= nextTime)  {
              nextTime = millis() + 50;
              if (perimeter.isInside(0) != inside) {
                inside = perimeter.isInside(0);
                counter++;
              }
            }
     
          Serial3.print((perimeter.isInside(0)));
          Serial3.println("\a");
          delay(300);  
    
          Serial3.print(perimeter.getMagnitude(0));
          Serial3.println("\b");
          delay(200);  

          Serial3.print(Test_Complete);
          Serial3.println("\c");
          delay(200);  
    
          message_out.print(F("IN/Out:"));
          message_out.print(perimeter.isInside(0));
          message_out.print(F("   MAG:"));
          message_out.print(perimeter.getMagnitude(0)); 
          message_out.print(F("   i:"));
          message_out.println(i);
          }
      message_out.println(F("Test Completed"));
      }


// Start Sonar Test
  if (TFT_Menu_Command == 45) {
    message_out.println(F("Sonar Test"));
    bool Test_Complete = 0;

      for (int i = 0; i <= 30; i++) {

        if (i > 28) Test_Complete = 1;
        if (Sonar_1_Activate == 1) distance1 = PingSonarY(trigPin1, echoPin1, 1, 1, 1, 5, 0);          //SONAR1
        if (Sonar_1_Activate == 0) distance1 = 999;
        delay(15);       
        if (Sonar_2_Activate == 1) distance2 = PingSonarY(trigPin2, echoPin2, 2, 2, 2, 0, 0);         //SONAR2
        if (Sonar_2_Activate == 0) distance1 = 999;
        delay(15);
        if (Sonar_3_Activate == 1) distance3 = PingSonarY(trigPin3, echoPin3, 3, 3, 3, 10, 0);          //SONAR3
        if (Sonar_3_Activate == 0) distance1 = 999;
        delay(15);
        
        Serial3.print(distance1);
        Serial3.println("\a");
        delay(300);  
    
        Serial3.print(distance2);
        Serial3.println("\b");
        delay(200);  

        Serial3.print(distance3);
        Serial3.println("\c");
        delay(200); 

        Serial3.print(Test_Complete);
        Serial3.println("\d");
        delay(200);    

        message_out.print("Test Complete");
        message_out.println(Test_Complete);
      
      
      }
    message_out.println(F("Sonar Test Complete"));
    

    }


// Start Compass Test
  if (TFT_Menu_Command == 48) {
    message_out.println(F("Compass Test"));
    bool Test_Complete = 0;

      int Cycles = 40;

      for (int i = 0; i <= Cycles; i++) {

        if (i > (Cycles - 2) ) Test_Complete = 1;
        Get_Compass_Reading();

        int Compass_Degrees_TX = Compass_Heading_Degrees;
        delay(300);
        
        Serial3.print(Heading * 10);
        Serial3.println("\a");
        delay(300);  
      
        Serial3.print(Compass_Degrees_TX);
        Serial3.println("\b");
        delay(300); 

        message_out.print("Heading: ");
        message_out.print(Heading);
        message_out.print("  Degrees: ");
        message_out.println(Compass_Degrees_TX);
  
     
        Serial3.print(Test_Complete);
        Serial3.println("\c");
        delay(300);    


      }

    message_out.print(F("Compass Test Complete"));
    message_out.println(Test_Complete);
    }


// Start GYRO Test
  if (TFT_Menu_Command == 39) {
    message_out.println(F("GYRO Test"));
    bool Test_Complete = 0;

      int Cycles = 60;

      for (int i = 0; i <= Cycles; i++) {

        if (i > (Cycles - 2) ) Test_Complete = 1;
        Get_GYRO_Reading();
        Print_GYRO_Reading();

       
        Serial3.print(GYRO_Angle_X);
        Serial3.println("\a");
        delay(300);  
      
        Serial3.print(GYRO_Angle_Y);
        Serial3.println("\b");
        delay(300); 
    
        Serial3.print(Test_Complete);
        Serial3.println("\c");
        delay(300);    

        //message_out.print("Angle X: ");
        //message_out.print(GYRO_Angle_X);
        //message_out.print(" Angle Y: ");
        //message_out.println(GYRO_Angle_Y);

      }

    message_out.print(F("Compass Test Complete"));
    message_out.println(Test_Complete);
    }


// Start Volt Amp Test
  if (TFT_Menu_Command == 47) {
    message_out.println(F("Volt Amp Test"));
    bool Test_Complete = 0;

      for (int i = 0; i <= 30; i++) {

        if (i > 28) Test_Complete = 1;
        
        Read_Serial1_Nano();
        delay(200);

        int VoltsRX = (Volts * 100) / 2;
   
        Serial3.print(VoltsRX);
        Serial3.println("\a");
        delay(100);  
    
        Serial3.print(Amps * 100);
        Serial3.println("\b");
        delay(100); 
        
        Serial3.print(Test_Complete);
        Serial3.println("\c");
        delay(300);    

        message_out.print("VoltsRX: ");
        message_out.print(VoltsRX);
        message_out.print("  Volts: ");
        message_out.print(Volts);
        message_out.print("  Amps: ");
        message_out.println(Amps);
      }

    message_out.print(F("Volt Amp Test Complete"));
    message_out.println(Test_Complete);
    }

// Start Tilt Test
  if (TFT_Menu_Command == 40) {
    message_out.println(F("Tilt Test"));
    bool Test_Complete = 0;
    Setup_Tilt_Tip_Safety();

      for (int i = 0; i <= 30; i++) {

        if (i > 28) Test_Complete = 1;
        
        Check_Tilt_Tip_Angle(); 
        delay(200);
   
        Serial3.print(Tilt_Angle_Sensed);
        Serial3.println("\a");
        delay(100);  
    
        Serial3.print(Tilt_Orientation_Sensed);
        Serial3.println("\b");
        delay(100); 
        
        Serial3.print(Test_Complete);
        Serial3.println("\c");
        delay(300);    

        message_out.print(F("   Data sent"));

        message_out.print(F("  Test Completed "));
        message_out.println(Test_Complete);
      }

    message_out.print(F("Tilt Test Complete : "));
    message_out.println(Test_Complete);
    }



// Start Bumper Test
  if (TFT_Menu_Command == 50) {
    message_out.println(F("Bumper Bar Test"));
    bool Test_Complete = 0;
    bool Bump_LH;
    bool Bump_RH;

      for (int i = 0; i <= 30; i++) {

        if (i > 28) Test_Complete = 1;
        
        if (digitalRead(Bumper_Switch_Frnt_LH))  Bump_LH = 0; 
        if (!digitalRead(Bumper_Switch_Frnt_LH)) Bump_LH = 1;
        if (digitalRead(Bumper_Switch_Frnt_RH))  Bump_RH = 0; 
        if (!digitalRead(Bumper_Switch_Frnt_RH)) Bump_RH = 1;
        delay(200);

        int VoltsRX = (Volts * 100) / 2;
   
        Serial3.print(Bump_LH);
        Serial3.println("\a");
        delay(100);  
    
        Serial3.print(Bump_RH);
        Serial3.println("\b");
        delay(100); 
        
        Serial3.print(Test_Complete);
        Serial3.println("\c");
        delay(300);    

        message_out.print("Bump LH: ");
        message_out.print(Bump_LH);
        message_out.print("  Bump RH: ");
        message_out.println(Bump_RH);
      }

    message_out.print(F("Volt Bumper Test Complete"));
    message_out.println(Test_Complete);
    }


}

void Send_Mower_Tracking_Data() {
        Serial3.print(Turn_To_Home);
        Serial3.println("\a");
        delay(100);  
    
        Serial3.print(Find_Wire_Track);
        Serial3.println("\b");
        delay(100); 
        
        Serial3.print(Go_To_Charging_Station);
        Serial3.println("\c");
        delay(300);    

        Serial3.print(Mower_Docked);
        Serial3.println("\d");
        delay(300);    

        Serial3.print(Mower_Status_Value);
        Serial3.println("\l");
        delay(300); 

        Serial3.print(Mower_Error_Value);
        Serial3.println("\f");
        delay(300); 
        

}

void Send_Mower_Error_Data() {
        
        Serial3.print(Mower_Status_Value);
        Serial3.println("\a");
        delay(300); 

        Serial3.print(Mower_Error_Value);
        Serial3.println("\b");
        delay(300); 
        
        message_out.print("Sending Error Data to TFT");

        message_out.print(F("|MS:"));
        message_out.print(Mower_Status_Value); 
        message_out.print(F("|ME:"));
        message_out.print(Mower_Error_Value); 
        }


void Send_Mower_Running_Data() {
        int Delay_running = 200;
        
        message_out.println(F(""));
        message_out.println(F("Updating TFT Screen: Turn Point"));
       
        Serial3.print(Sonar_Status);
        Serial3.println(F("\a"));        
        delay(Delay_running);
    
        Serial3.print(Outside_Wire);
        Serial3.println(F("\b"));
        delay(Delay_running);        
        
        Serial3.print(Bumper_Status);
        Serial3.println("\c");
        delay(Delay_running);    

        Serial3.print(Mower_Status_Value);
        Serial3.println("\s");
        delay(Delay_running);    

        Serial3.print(Mower_Error_Value);      
        Serial3.println("\e");
        delay(Delay_running); 
  
        Serial3.print(Tilt_Angle_Sensed);      
        Serial3.println("\f");
        delay(Delay_running); 

        // Reformet Volts value for transmission
        float VoltsTX1 = Volts * 100;
        VoltsTX = VoltsTX1;
        
        Serial3.print(VoltsTX);      
        Serial3.println("\g");
        delay(Delay_running);

        Serial3.print(GPS_Inside_Fence);      
        Serial3.println("\h");
        delay(Delay_running);

        Serial3.print(GPS_Lock_OK);      
        Serial3.println("\i");
        delay(Delay_running);        

        Calculate_TFT_Mower_Status_Value(); 


        message_out.print(F("|S:"));          
        message_out.print(Sonar_Status);
        message_out.print(F("|W:"));
        message_out.print(Outside_Wire);  
        message_out.print(F("|B:"));
        message_out.print(Bumper_Status); 
        message_out.print(F("|MS:"));
        message_out.print(Mower_Status_Value);  
        message_out.print(F("|ME:"));
        message_out.print(Mower_Error_Value); 
        message_out.print(F("|Tip:"));
        message_out.print(Tilt_Angle_Sensed);     
        message_out.print(F("|VTX:"));
        message_out.print(VoltsTX);          
        message_out.print(F("|GPS Inside Fence:"));
        if (GPS_Inside_Fence == 0) message_out.print("OUT");           
        if (GPS_Inside_Fence == 1) message_out.print("IN");
        message_out.print(F("|GPS Lock:"));
        if (GPS_Lock_OK == 0) message_out.println("No lock");           
        if (GPS_Lock_OK == 1) message_out.println("RTK FIX");
        }


// Sends Wheel Amp Data during Test
void Send_Wheel_Amp_Data() {
        Serial3.print(Wheel_Blocked);      
        Serial3.println("\a");
        delay(300);
        }



// Transfers the values to the TFT in Docked Mode.
void Send_Mower_Docked_Data()  {

        Calculate_TFT_Mower_Status_Value(); 
        // Reformat Volts value for transmission
        float VoltsTX1 = Volts * 100;
        VoltsTX = VoltsTX1;
        
        Serial3.print(VoltsTX);      
        Serial3.println("\a");
        delay(300);
      
        Serial3.print(Mower_Status_Value);      
        Serial3.println("\w");
        delay(300); 

        Serial3.print(Mower_Error_Value);      
        Serial3.println("\c");
        delay(300);   

        Serial3.print(Charging);      
        Serial3.println("\d");
        delay(300); 

        int GPS_Lock_OK_Docked_TX;
        if (GPS_Lock_OK == 0) GPS_Lock_OK_Docked_TX = 2;
        if (GPS_Lock_OK == 1) GPS_Lock_OK_Docked_TX = 5;
        Serial3.print(GPS_Lock_OK_Docked_TX);      
        Serial3.println("\e");
        delay(300); 

        message_out.print(F("|VTX:"));
        message_out.print(VoltsTX);
        message_out.print(F("|MS:"));
        message_out.print(Mower_Status_Value);            
        message_out.print(F("|ME:"));
        message_out.print(Mower_Error_Value);                 
        message_out.print(F("|C:"));
        message_out.print(Charging); 
        message_out.print(F("|LOCK:"));
        message_out.print(GPS_Lock_OK);            
        } 

void Calculate_TFT_Mower_Status_Value() {

   Mower_Status_Value = 0;

   if ((Wire_Detected == 1) && (Tilt_Orientation_Sensed == 0)) {
      Mower_Error = 0;
      if ((Mower_Docked == 1) || (Mower_Parked == 1)) {   
         Mower_Error_Value = 0;
         }
   }

   
   
   if (Wire_Detected == 0) {

        // If the mower is running and no wire is detected then the full error screen is displayed
        if (Mower_Running == 1) {
              Mower_Error = 1;
              Mower_Error_Value = 1;     // 1 = No Wire Detected
              }
        // If the mower is docked then the Wire Off message is displayed on the docked screen. 
        if ((Mower_Docked == 1) || (Mower_Parked == 1)) {
              Mower_Error_Value = 1;
              }
        }


   if (Mower_Docked == 1)           Mower_Status_Value = 1;
   if (Mower_Parked == 1)           Mower_Status_Value = 2; 
   
   if (Mower_Parked_Low_Batt == 1)  {
     Mower_Status_Value = 4;  // Error Mode
     Mower_Error_Value = 2;   // 2 = Low Battery
     }
   
   if (Mower_Error == 1)                                    Mower_Status_Value = 4;  // Error
   if (Mower_Error == 3) {
        Mower_Status_Value = 4;  // Error
        Mower_Error_Value = 3;   
        }
   if (Mower_Running == 1)                                  Mower_Status_Value = 5;
   if (Manuel_Mode == 1)                                    Mower_Status_Value = 6;
   if (Tracking_Wire == 1)                                  Mower_Status_Value = 7;
   if (Rain_Hit_Detected == 1)                              Mower_Status_Value = 8;
   if (Exiting_Dock == 1)                                   Mower_Status_Value = 9;

   }
