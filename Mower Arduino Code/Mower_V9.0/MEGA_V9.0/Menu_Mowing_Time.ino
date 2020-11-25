// Test to displyed on the LCD screen when using the membrane key menus

// BUTTONS TIMING MENU

void Print_LCD_Menu_Timing(byte LCD_Menu_Timing) {
  if (LCD_Menu_Timing == 1) lcd.print(F("Max Mow Time"));
  if (LCD_Menu_Timing == 2) lcd.print(F("1hr Mow Time"));
  if (LCD_Menu_Timing == 3) lcd.print(F("2hr Mow Time"));
  if (LCD_Menu_Timing == 4) lcd.print(F("  "));                  //leave blank
  Max_Options_Timing = 4;
 }  



void Print_Membrane_Switch_Input_Timing() {

  //Menu Options if the Mower is Timing.
     Read_Membrane_Keys();
     Menu_Complete = 1;
     Menu_Mode_Selection = 0;
     Menu_View = 0;

    
      message_out.println();
      message_out.println(F("Test Menu Activated"));
      Menu_Complete = false;                                // Menu complete will return to the normal loop
      lcd.clear();
      delay(5);
 

      while (Menu_Complete == false) {                      // holds the program in a loop until a selection has been made in the membrane button menu
        if (Menu_View == 0) {
          lcd.setCursor(1,0);
          Print_LCD_Menu_Timing(1);
          lcd.setCursor(1,1);
          Print_LCD_Menu_Timing(2);
          }
        // Gets the values again from the keys
        Read_Membrane_Keys();
        delay(100);
             
        if(!Start_Key_X){
          Menu_Complete = true;
          message_out.println(F("Start key is pressed"));
          lcd.clear();
          }
        if(!Plus_Key_X) {
          message_out.println(F("+ key is pressed"));
          Menu_View = Menu_View - 1;
          Run_Menu_Order_Timing();
          }
        if(!Minus_Key_X) {
          Menu_View = Menu_View + 1;
          Run_Menu_Order_Timing();
        }
        if(!Stop_Key_X){
          message_out.println(F("Stop key is pressed"));
          Menu_Complete = true;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(F("Menu Cancelled"));
          delay(1000);
          lcd.clear();          
          Menu_Mode_Selection = 0;
          }
      }
    Activate_Menu_Option_Timing();
    }

 void Run_Menu_Order_Timing() {
     if (Menu_View > Max_Options_Timing) Menu_View = Menu_View -1;
     if (Menu_View < 0) Menu_View = Menu_View + 1;
     message_out.print(F("- key is pressed "));
     lcd.clear();
     lcd.setCursor(1,0);
     Print_LCD_Menu_Timing(Menu_View);
     lcd.setCursor(1,1);
     Print_LCD_Menu_Timing( Menu_View + 1);
     lcd.setCursor(0,0);
     lcd.print(">");
     Menu_Mode_Selection = Menu_View;
     message_out.print(F("Menu View : "));
     message_out.print(Menu_View);
     message_out.print(F("| Menu Selection"));
     message_out.println(Menu_Mode_Selection);
     delay(100);
     }


void Activate_Menu_Option_Timing() {
     
     if (Menu_Mode_Selection == 1) {
       // Maximum Mower Timing
       lcd.clear();
       lcd.print(F("Max Mow"));
       lcd.setCursor(0,1);
       lcd.print(F("Selected"));
       message_out.println(F("Maximum Mow Time Selected"));
       delay(5000);
       lcd.clear();
       Menu_Mode_Selection = 0;
       lcd.clear();
       Menu_Complete = false;
       // Add actions here
       Alarm_Timed_Mow_ON = 0;
       Mow_Time_Set = 1;
       }
     
 
     
     if (Menu_Mode_Selection == 2) {
       // 1hr Mowing
       message_out.println(F("1 hr Mow Time Selected"));
       lcd.clear();
       Menu_Mode_Selection = 0;
       lcd.clear();
       Menu_Complete = false;

           // Ations Here
           Time t = rtc.time();
           Alarm_Timed_Mow_ON = 1;                          // Activate the Mow Timer Alarm
           Alarm_Timed_Mow_Hour = t.hr + 1;                 // Sets time to 1 hour later.
           Alarm_Timed_Mow_Minute = t.min;                  // Minutes are the same

           // Displays the Finish time on the Serial Monitor
           message_out.print(F("Finish Time set to : "));
           message_out.print(Alarm_Timed_Mow_Hour);
           message_out.print(F(":"));
           if (Alarm_Timed_Mow_Minute < 10) message_out.print ("0");
           message_out.println(Alarm_Timed_Mow_Minute);
           
           lcd.print("1hr Mow Selected");
           lcd.setCursor(0,1);
           lcd.print("Ends: ");
           lcd.print(Alarm_Timed_Mow_Hour);
           lcd.print(":");
           if (Alarm_Timed_Mow_Minute < 10) lcd.print("0");
           lcd.print(Alarm_Timed_Mow_Minute);
           Mow_Time_Set = 1;
           delay(2000);
       }
    

     if (Menu_Mode_Selection == 3) {
       // 2hr Mowing
       message_out.println(F("2 hr Mow Time Selected"));
       lcd.clear();
       Menu_Mode_Selection = 0;
       lcd.clear();
       Menu_Complete = false;

           // Ations Here
           Time t = rtc.time();
           Alarm_Timed_Mow_ON = 1;                          // Activate the Mow Timer Alarm
           Alarm_Timed_Mow_Hour = t.hr + 2;                 // Sets time to 1 hour later.
           Alarm_Timed_Mow_Minute = t.min;                  // Minutes are the same

           // Displays the Finish time on the Serial Monitor
           message_out.print(F("Finish Time set to : "));
           message_out.print(Alarm_Timed_Mow_Hour);
           message_out.print(F(":"));
           if (Alarm_Timed_Mow_Minute < 10) message_out.print ("0");
           message_out.println(Alarm_Timed_Mow_Minute);
           
           lcd.print(F("2hr Mow Selected"));
           lcd.setCursor(0,1);
           lcd.print(F("Ends: "));
           lcd.print(Alarm_Timed_Mow_Hour);
           lcd.print(":");
           if (Alarm_Timed_Mow_Minute < 10) lcd.print("0");
           lcd.print(Alarm_Timed_Mow_Minute);
           Mow_Time_Set = 1;
           delay(2000);
       }
        
   
  }
