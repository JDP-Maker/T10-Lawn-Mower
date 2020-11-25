// BUTTONS PARKED MENU


// Test to displyed on the LCD screen when using the membrane key menus
void Print_LCD_Menu_Parked(byte LCD_Menu_Parked) {
  if (LCD_Menu_Parked == 1)   lcd.print("Mow Grass     ");
  if (LCD_Menu_Parked == 2)   {
    if (Use_Charging_Station == 1)  lcd.print(F("Go To Dock"));
    if (Use_Charging_Station == 0)  lcd.print(F("Dock Removed"));
    }
  if (LCD_Menu_Parked == 3)   lcd.print(F("Trampoline Cut"));
  if (LCD_Menu_Parked == 4)   lcd.print(F("Test Mower"));
  if (LCD_Menu_Parked == 5)   lcd.print(F("Setup Mower"));
  if (LCD_Menu_Parked == 6)   lcd.print(F(""));    // Leave Blank
  Max_Options_Parked = 6;
  }
  

 void Check_Membrane_Switch_Input_Parked() {

  //Menu Options if the Mower is Parked.
     Read_Membrane_Keys();
     Menu_Complete = 1;
     Menu_Mode_Selection = 0;
     Menu_View = 0;

     if(!Start_Key_X)  {                                    // If the start key is pressed
        message_out.println();
        message_out.println(F("Start Key Pressed"));
        Menu_Complete = false;                                // Menu complete will return to the normal loop
        lcd.clear();
        delay(5);
        message_out.println();
        message_out.println(F("Parked Menu Activated"));
        delay(500);

 

      while (Menu_Complete == false) {                      // holds the program in a loop until a selection has been made in the membrane button menu
        if (Menu_View == 0) {
          lcd.setCursor(1,0);
          Print_LCD_Menu_Parked(1);
          lcd.setCursor(1,1);
          Print_LCD_Menu_Parked(2);
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
          Run_Menu_Order_Parked();
          }
        if(!Minus_Key_X) {
          Menu_View = Menu_View + 1;
          Run_Menu_Order_Parked();
        }
        if(!Stop_Key_X){
          message_out.println(F("Stop key is pressed"));
          Menu_Complete = true;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Menu Cancelled");
          delay(1000);
          lcd.clear();          
          Menu_Mode_Selection = 0;
          }
      }
    Activate_Menu_Option_Parked();
    }
 }

 void Run_Menu_Order_Parked() {
     if (Menu_View > Max_Options_Parked) Menu_View = Menu_View -1;
     if (Menu_View < 0) Menu_View = Menu_View + 1;
     message_out.print(F("- key is pressed "));
     lcd.clear();
     lcd.setCursor(1,0);
     Print_LCD_Menu_Parked(Menu_View);
     lcd.setCursor(1,1);
     Print_LCD_Menu_Parked( Menu_View + 1);
     lcd.setCursor(0,0);
     lcd.print(">");
     Menu_Mode_Selection = Menu_View;
     message_out.print(F("Menu View : "));
     message_out.print(Menu_View);
     message_out.print(F("| Menu Selection"));
     message_out.println(Menu_Mode_Selection);
     delay(100);
     }


// Defines the actions when that option is selected with the keypad.
void Activate_Menu_Option_Parked() {
     
     if (Menu_Mode_Selection == 1) {
      Menu_Mode_Selection = 0;
      lcd.clear();
      Print_Membrane_Switch_Input_Timing();
      lcd.clear();
      lcd.print(F("Mow Re-Starting"));
      message_out.println(F("Mower Starting"));
      delay(2000);
      Manouver_Start_Mower();                                             // Restarts the mower again from standing position
      lcd.clear();     
      }

     if (Menu_Mode_Selection == 2) {
      if (Use_Charging_Station == 1) {
          lcd.clear();
          lcd.print(F("Returning Home"));
          message_out.println(F("Sending Mower Home"));
          delay(100);
          Menu_Mode_Selection = 0;                                      // Releases the loop in the membrane button section.
          delay(1000);
          lcd.clear();
          Manouver_Go_To_Charging_Station();        
          }
      if (Use_Charging_Station == 0) {
          lcd.clear();
          lcd.print(F("No Dock Active"));
          message_out.println(F("Activate Docking Station in Settings"));
          delay(100);
          Menu_Mode_Selection = 0;                                      // Releases the loop in the membrane button section.
          delay(1000);
          lcd.clear();
          }
     }
      
      if (Menu_Mode_Selection == 3) {
        lcd.clear();
        lcd.print("Trampoline Cut!");
        message_out.println(F("Mower Set to Cut under Trampoline"));
        Menu_Mode_Selection = 0;
        delay(3000);
        lcd.clear();
        Special_Cut_Under_Trampoline_Function();
        }

      if (Menu_Mode_Selection == 4) {
        lcd.clear();
        lcd.print("Test Mower Menu");
        message_out.println(F("Test Menu Selected"));
        Menu_Mode_Selection = 0;
        delay(3000);
        lcd.clear();
        Print_Membrane_Switch_Input_Tests();
        }

      if (Menu_Mode_Selection == 5) {
        lcd.clear();
        lcd.print("Setup Mower");
        message_out.println(F("Mower Setup Selected"));
        Menu_Mode_Selection = 0;
        delay(3000);
        lcd.clear();
        Print_Membrane_Switch_Input_Settings();
        }

      if (Menu_Mode_Selection == 6) {
        lcd.clear();
        lcd.print("Slot 6 - Empty");
        message_out.println(F("Slot 6 Selected"));
        Menu_Mode_Selection = 0;
        delay(3000);
        lcd.clear();
        // Insert Function Here();
        }
  }


void Check_Membrane_Keys_Running() {

     Read_Membrane_Keys();
     if(!Stop_Key_X){
        Manouver_Park_The_Mower();
        Check_Membrane_Switch_Input_Parked();   
        Menu_Mode_Selection = 0;
        }
}
     
  
