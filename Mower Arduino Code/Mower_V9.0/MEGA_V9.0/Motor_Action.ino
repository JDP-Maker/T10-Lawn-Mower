
void Motor_Action_Go_Mowing_Speed() {
  
  // No Mag speed adjustment active just go full speed
  if (MAG_Speed_Adjustment == 0) Motor_Action_Go_Full_Speed();  
  
  // Adjust wheel speed according to the MAG level
  if (MAG_Speed_Adjustment == 1) {
          if (MAG_Now >= Slow_Speed_MAG) {
            Motor_Action_Go_Full_Speed(); 
            }
        
          if (MAG_Now < Slow_Speed_MAG)  {
            Motor_Action_Go_Slow_Speed(); 
            }
    }
}

void Motor_Action_Go_Full_Speed()     {
      analogWrite(ENAPin, PWM_MaxSpeed_RH);                       // Speed = 0-255  (255 is max speed). Speed is set in the settings                        
      analogWrite(ENBPin, PWM_MaxSpeed_LH);                       // Anaolgwirte sends PWM signals Speed = 0-255  (255 is max speed)
      message_out.print(F("Wheel:FULL|"));
      }  

void Motor_Action_Go_Slow_Speed()     {
      analogWrite(ENAPin,  PWM_Slow_Speed_RH);                       // Speed = 0-255  (255 is max speed). Speed is set in the settings                        
      analogWrite(ENBPin,  PWM_Slow_Speed_LH);                       // Anaolgwirte sends PWM signals Speed = 0-255  (255 is max speed)
      message_out.print(F("Wheel:SLOW|"));
      }  

void Motor_Action_GoFullSpeed_Out_Garage()     {
  //Speeds can be changed to give the mower a slight curve when exiting the Garage.
  
  PWM_MaxSpeed_LH = PWM_MaxSpeed_LH + 20;                          
  if (PWM_MaxSpeed_LH > 255)  PWM_MaxSpeed_LH = 255;
  if (PWM_MaxSpeed_RH > 255)  PWM_MaxSpeed_RH = 255;
  
  analogWrite(ENAPin, PWM_MaxSpeed_RH);                                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
  analogWrite(ENBPin, PWM_MaxSpeed_LH);   
  message_out.print(F("Wheel:FULL|"));
  }


void SetPins_ToGoForwards()     {                                 // Motor Bridge pins are set for both motors to move forwards.
  digitalWrite(IN1Pin, LOW);                                      // Motor Birdge pins are set to high or low to set the direction of movement
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
  message_out.print(F("Wheel:For|"));
  }


void SetPins_ToGoBackwards()      {                               // Motor Bridge pins are set for both motors to move Backwards
  digitalWrite(IN1Pin, HIGH);                                     // Motor 1
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);                                     // Motor 2
  digitalWrite(IN4Pin, LOW);
  message_out.print(F("Wheel:Rev|"));
  delay(20);
  }


void Motor_Action_Stop_Motors()  {                                     // Motor Bridge pins are set for both motors to stop
  digitalWrite(ENAPin, 0);
  digitalWrite(IN1Pin, LOW);                                    //Motor 1
  digitalWrite(IN2Pin, LOW);

  digitalWrite(ENBPin, 0);                                      //Motor 2
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);

  message_out.print(F("Wheel:0FF|"));
}


void SetPins_ToTurnLeft()       {                              // Pins are set so that Motors drive in opposite directions
    digitalWrite(IN1Pin, LOW);                                   // Motor 1
    digitalWrite(IN2Pin, HIGH);
    digitalWrite(IN3Pin, HIGH);                                  // Motor 2
    digitalWrite(IN4Pin, LOW);
    message_out.print(F("Wheel:TL_|"));  
    }


void SetPins_ToTurnRight() {                                    // Pins are set so that Motors drive in opposite directions
      digitalWrite(IN1Pin, HIGH);                                   // Motor 1
      digitalWrite(IN2Pin, LOW);
      digitalWrite(IN3Pin, LOW);                                    //Motor 2
      digitalWrite(IN4Pin, HIGH);
      message_out.print(F("Wheel:R|"));
      }


// USed to turn the mower at a set speed.
void Motor_Action_Turn_Speed() {
      analogWrite(ENAPin, (PWM_MaxSpeed_RH - Turn_Adjust) );                                  // Change the 0 value to 10 or 20 to recuce the speed
      analogWrite(ENBPin, (PWM_MaxSpeed_LH - Turn_Adjust) );                                  // Change the 0 value to 10 or 20 to recuce the speed
      }


// Turns the mowing blades on
void Motor_Action_Spin_Blades()  {
  if (Cutting_Blades_Activate == 1) {                                       // Blades are turn ON in settings and will spin!
    delay(20);
    digitalWrite(PIN_MOW_MOTOR_RIGHT_UP, HIGH);
    digitalWrite(PIN_MOW_MOTOR_RIGHT_DN, HIGH);
	digitalWrite(PIN_MOW_MOTOR_CENTER_UP, HIGH);
    digitalWrite(PIN_MOW_MOTOR_CENTER_DN, HIGH);
	digitalWrite(PIN_MOW_MOTOR_LEFT_UP, HIGH);
    digitalWrite(PIN_MOW_MOTOR_LEFT_DN, HIGH);
    delay(20);
    analogWrite(PIN_MOW_MOTOR_RIGHT_SPEED, PWM_Blade_Speed);
	analogWrite(PIN_MOW_MOTOR_CENTER_SPEED, PWM_Blade_Speed);
	analogWrite(PIN_MOW_MOTOR_LEFT_SPEED, PWM_Blade_Speed);
    delay(20);
    message_out.print(F("Blades:ON_|"));
   }                 

  if (Cutting_Blades_Activate == 0) {                                     // Blades are turn off in settings and will not spin!
    void StopSpinBlades();

  }
}

void Motor_Action_Stop_Spin_Blades()  {
  delay(20);
    digitalWrite(PIN_MOW_MOTOR_RIGHT_UP, LOW);
    digitalWrite(PIN_MOW_MOTOR_RIGHT_DN, LOW);
	digitalWrite(PIN_MOW_MOTOR_CENTER_UP, LOW);
    digitalWrite(PIN_MOW_MOTOR_CENTER_DN, LOW);
	digitalWrite(PIN_MOW_MOTOR_LEFT_UP, LOW);
    digitalWrite(PIN_MOW_MOTOR_LEFT_DN, LOW);
  delay(20);
  message_out.print(F("Blades:0FF|"));
}

//Steers the Mower depending on the PID input from the Algorythm
void Motor_Action_Dynamic_PWM_Steering() {
      analogWrite(ENAPin, PWM_Right);                             // ENA low = Right Swerve   ENB low = Left Swerve
      analogWrite(ENBPin, PWM_Left);
      message_out.print(F("PWM_R:"));
      message_out.print(PWM_Right);
      message_out.print(F("|"));
      message_out.print(F("PWM_L:"));
      message_out.print(PWM_Left);
      message_out.print(F("|"));
}
