// Listens to the serial 3 port if a menu command has been executed.
void Check_TFT_Serial_Input() {
  
  String Serial3_RX_Value  = "";                                     
  int Number_Received;
 
  while (Serial3.available() > 0) {
    char recieved = Serial3.read();
    if ( recieved != '\g' ) {   
      Serial3_RX_Value = Serial3_RX_Value +  (char)recieved;          
      } 
      else if (recieved == '\g') {
        TFT_Menu_Command  = Serial3_RX_Value.toInt();                        
        Serial3_RX_Value  = "";       // changed to string    
        Confirm_TX_or_RX_Action();    // Prints the Menu Selected
        delay(100);
        Confirm_RX();                 // Confirms the transmition is received unless 57 (Docked Info)

      if ((Mower_Docked == 1) || (Mower_Parked == 1)) delay(500);
      Send_Data_To_TFT();                                   // Send data to TFT - depends on menu code received
      Receive_Data_From_TFT();                              // Receive Data from TFT - depends on menu code received
      }         
      
    else message_out.print(F("No Data Received|"));
  }

}



void Activate_TFT_Menu() {

        message_out.println();
        message_out.println(F("TFT Menu Activated"));
        Menu_Complete_TFT = false;                                // Menu complete will return to the normal loop
        delay(500);
        message_out.println("waiting for command");
     
     while (Menu_Complete_TFT == false) {                      // holds the program in a loop until a selection has been made in the membrane button menu
          Check_TFT_Serial_Input();
          delay(200);
          if (TFT_Menu_Command == 1) Menu_Complete_TFT = true;  
          }

      }


void Confirm_RX() {      
      // confirms to the TFT that a request for data transfer has been received.
      Serial3.print(TFT_Menu_Command * 3);
      Serial3.println("\h");
      delay(200); 
      message_out.print("Confirmstion Code Sent : ");
      message_out.println(TFT_Menu_Command * 3); 
      }




// Based on the code received this menu confirms the menu item to be used.
void Confirm_TX_or_RX_Action() {

message_out.print("TFT Menu Command: ");
message_out.print(TFT_Menu_Command );
message_out.print(" = ");

if (TFT_Menu_Command == 1)  message_out.println(F("Main Menu"));
if (TFT_Menu_Command == 2)  message_out.println(F("Quick Start Menu"));
if (TFT_Menu_Command == 3)  message_out.println(F("Exit Dock Menu"));
if (TFT_Menu_Command == 4)  message_out.println(F("Options Menu"));
if (TFT_Menu_Command == 5)  message_out.println(F("Time Menu"));
if (TFT_Menu_Command == 6)  message_out.println(F("Sensors Menu"));
if (TFT_Menu_Command == 7)  message_out.println(F("Motion Menu"));
if (TFT_Menu_Command == 8)  message_out.println(F("Tracking Menu"));
if (TFT_Menu_Command == 9)  message_out.println(F("Navigation Menu"));
if (TFT_Menu_Command == 10) message_out.println(F("Sonar Menu"));
//  Leave 11 Free.
if (TFT_Menu_Command == 12) message_out.println(F("Rain Sensor Menu"));
if (TFT_Menu_Command == 13) message_out.println(F("Stop Menu"));
if (TFT_Menu_Command == 14) message_out.println(F("Wheel Motor Menu"));
if (TFT_Menu_Command == 15) message_out.println(F("Blade Motor Menu"));
if (TFT_Menu_Command == 16) message_out.println(F("Movement Menu"));
if (TFT_Menu_Command == 17) message_out.println(F("Tracking Exit Points"));
if (TFT_Menu_Command == 18) message_out.println(F("Find Wire"));
if (TFT_Menu_Command == 19) message_out.println(F("Track PID"));
if (TFT_Menu_Command == 20) message_out.println(F("Set Alarm 1"));
if (TFT_Menu_Command == 21) message_out.println(F("Set Alarm 2"));
if (TFT_Menu_Command == 22) message_out.println(F("Set Alarm 3"));
if (TFT_Menu_Command == 23) message_out.println(F("Set Time"));
if (TFT_Menu_Command == 24) message_out.println(F("Tip Sensor Menu"));
if (TFT_Menu_Command == 25) message_out.println(F("Pattern Menu"));
if (TFT_Menu_Command == 26) message_out.println(F("Battery Menu"));
if (TFT_Menu_Command == 27) message_out.println(F("Compass Menu"));
if (TFT_Menu_Command == 28) message_out.println(F("GYRO Menu"));
if (TFT_Menu_Command == 29) message_out.println(F("Wheel Block Amps Menu"));
if (TFT_Menu_Command == 30) message_out.println(F("Setup Other Menu"));

if (TFT_Menu_Command == 38) message_out.println(F("Wheel Amp Test"));
if (TFT_Menu_Command == 39) message_out.println(F("GYRO Test"));
if (TFT_Menu_Command == 40) message_out.println(F("Tilt Test"));
if (TFT_Menu_Command == 41) message_out.println(F("Wire Test"));
if (TFT_Menu_Command == 42) message_out.println(F("Relay Test"));
if (TFT_Menu_Command == 43) message_out.println(F("Wheel Test"));
if (TFT_Menu_Command == 44) message_out.println(F("Blade Test"));
if (TFT_Menu_Command == 45) message_out.println(F("Sonar Test"));
if (TFT_Menu_Command == 46) message_out.println(F("Turn Test"));
if (TFT_Menu_Command == 47) message_out.println(F("Volt Amp Test"));
if (TFT_Menu_Command == 48) message_out.println(F("Compass Test"));
if (TFT_Menu_Command == 49) message_out.println(F("Go Home Test"));
if (TFT_Menu_Command == 50) message_out.println(F("Bumper Bar"));
if (TFT_Menu_Command == 55) message_out.println(F("Start-Up Value"));
if (TFT_Menu_Command == 57) message_out.println(F("TX Docked Info"));
if (TFT_Menu_Command == 58) message_out.println(F("Mower Running"));

if (TFT_Menu_Command == 99) message_out.println(F("Break TX loop and wait for data..."));
}
