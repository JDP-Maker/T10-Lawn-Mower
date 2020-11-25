/*
	speed control of the motor
	motor - pointer to an array of pins
	v - motor speed can be set from -100 to 100
*/
void Wheel (unsigned char * motor, int v){
	if (v > 100) v = 100;
	if (v < -100) v = -100;
	if (v > 0) {
		digitalWrite(motor[0], HIGH);
		digitalWrite(motor[1], LOW);
		analogWrite(motor[2], v * 2.55);
	}
	else if (v < 0) {
		digitalWrite(motor[0], LOW);
		digitalWrite(motor[1], HIGH);
		analogWrite(motor[2], (-v) * 2.55);
	}
	else {
		digitalWrite(motor[0], LOW);
		digitalWrite(motor[1], LOW);
		analogWrite(motor[2], 0);
	}
}

void Setup_RemoteXY () {
	/* initialization module RemoteXY */
	RemoteXY_Init ();
	
}

void Spin_mow_motors_right () {
	digitalWrite(PIN_MOW_MOTOR_RIGHT_UP, HIGH);
	digitalWrite(PIN_MOW_MOTOR_RIGHT_DN, LOW);
	digitalWrite(PIN_MOW_MOTOR_CENTER_UP, HIGH);
	digitalWrite(PIN_MOW_MOTOR_CENTER_DN, LOW);
	digitalWrite(PIN_MOW_MOTOR_LEFT_UP, HIGH);
	digitalWrite(PIN_MOW_MOTOR_LEFT_DN, LOW);
}

void Spin_mow_motors_left () {
	digitalWrite(PIN_MOW_MOTOR_RIGHT_UP, LOW);
	digitalWrite(PIN_MOW_MOTOR_RIGHT_DN, HIGH);
	digitalWrite(PIN_MOW_MOTOR_CENTER_UP, LOW);
	digitalWrite(PIN_MOW_MOTOR_CENTER_DN, HIGH);
	digitalWrite(PIN_MOW_MOTOR_LEFT_UP, LOW);
	digitalWrite(PIN_MOW_MOTOR_LEFT_DN, HIGH);
}

void RemoteXY_manual_remote_control () {
	RemoteXY_Handler ();  					//think this needs to run to get current connect status
	if (RemoteXY.connect_flag == 1)	message_out.println("entering wifi manual mode");
	while (RemoteXY.connect_flag == 1) {
		while_loop_active = 1;
		/* event handler module RemoteXY */
		RemoteXY_Handler ();
		
		//check connect status, if changed, from off to on print connect message, if on to off stop all motors
		Status = RemoteXY.connect_flag;
		if (Status != Old_Status) {
			Old_Status = Status;
			if ( RemoteXY.connect_flag == 1 ) {
				message_out.println( "Connected..." );
				lcd.clear();
				lcd.print("Connected...");
				//turn motors off after reconnect
				digitalWrite (RELAY, LOW);
				RemoteXY.Motor_Relay = 0;
			}
			else if ( RemoteXY.connect_flag == 0 )  //I don't think the while loop will ever allow this to be true, but does not hurt
			{
				digitalWrite (RELAY, LOW);
				message_out.println( "Connection lost, SHUT OFF ALL MOTORS" );
				lcd.clear();
				lcd.print("Connection lost");
				lcd.setCursor(0,1);
				lcd.print("SHUT OFF ALL MOTORS");
			}
		}
		
		/* manage Motor Relay pin */
		// only update if changed (don't need relay updating every loop)
		Relay_Status = RemoteXY.Motor_Relay;
		if (Relay_Status != Old_Relay_Status) {
			message_out.print ("Relay_Status = ");
			message_out.println (Relay_Status);
			lcd.clear();
			lcd.print("Relay_Status = ");
			lcd.print(Relay_Status);
			Old_Relay_Status = Relay_Status;
			digitalWrite (RELAY, (Relay_Status == 0) ? LOW : HIGH);
		}
		
		// Mow Motor control - only update when there is a change
		// All Motors go the same speed
		Mow_Motor_Speed = (RemoteXY.Blade_Speed * 2.55);
		if (Mow_Motor_Speed != Old_Mow_Motor_Speed) {
			message_out.print ("Mow Motor Speed = ");
			message_out.println (Mow_Motor_Speed);
			lcd.setCursor(0,1);
			lcd.print("Blade Speed = ");
			lcd.print(Mow_Motor_Speed);
			lcd.print ("   ");   
			Old_Mow_Motor_Speed = Mow_Motor_Speed;
			Spin_mow_motors_right ();
			analogWrite(PIN_MOW_MOTOR_RIGHT_SPEED, Mow_Motor_Speed);
			analogWrite(PIN_MOW_MOTOR_CENTER_SPEED, Mow_Motor_Speed);
			analogWrite(PIN_MOW_MOTOR_LEFT_SPEED, Mow_Motor_Speed);
			message_out.println ("message after analogwrite");
			delay(3000);
		}
		
		/* manage the right Wheel motor */
		Wheel (RightMotor, RemoteXY.joystick_1_y - RemoteXY.joystick_1_x);
		/* manage the left Wheel motor */
		Wheel (LeftMotor, RemoteXY.joystick_1_y + RemoteXY.joystick_1_x);
	}
	// exiting loop make sure motors are off
	if (while_loop_active == 1) {
		while_loop_active = 0;			// reset loop check
		digitalWrite (RELAY, LOW);
		message_out.println( "Connection lost, SHUT OFF ALL MOTORS" );
		lcd.clear();
		lcd.print("Connection lost");
		lcd.setCursor(0,1);
		lcd.print("SHUT OFF ALL MOTORS");
	}
}

void manual_lawnbot_main_function () {
	/* event handler module RemoteXY */
	RemoteXY_Handler ();
	
	//check connect status, if changed check on/off and if off stop all motors
	Status = RemoteXY.connect_flag;
	if (Status != Old_Status) {
		Old_Status = Status;
		if ( RemoteXY.connect_flag == 1 )
		{
			message_out.println( "Connected..." );
			lcd.clear();
			lcd.print("Connected...");
			//turn motors off after reconnect
			digitalWrite (RELAY, LOW);
			RemoteXY.Motor_Relay = 0;
		}
		else if ( RemoteXY.connect_flag == 0 )
		{
			digitalWrite (RELAY, LOW);
			message_out.println( "Connection lost, SHUT OFF ALL MOTORS" );
			lcd.clear();
			lcd.print("Connection lost");
			lcd.setCursor(0,1);
			lcd.print("SHUT OFF ALL MOTORS");
			return;
		}
	}
	
	/* manage Motor Relay pin */
	// only update if changed (don't need relay updating every loop)
	Relay_Status = RemoteXY.Motor_Relay;
	if (Relay_Status != Old_Relay_Status) {
		message_out.print ("Relay_Status = ");
		message_out.println (Relay_Status);
		lcd.clear();
		lcd.print("Relay_Status = ");
		lcd.print(Relay_Status);
		Old_Relay_Status = Relay_Status;
		digitalWrite (RELAY, (Relay_Status == 0) ? LOW : HIGH);
	}
	
	// Mow Motor control - only update when there is a change
	// All Motors go the same speed
	Mow_Motor_Speed = (RemoteXY.Blade_Speed * 2.55);
	if (Mow_Motor_Speed != Old_Mow_Motor_Speed) {
		message_out.print ("Mow Motor Speed = ");
		message_out.println (Mow_Motor_Speed);
		lcd.setCursor(0,1);
		lcd.print("Blade Speed = ");
		lcd.print(Mow_Motor_Speed);
		lcd.print ("   ");   
		Old_Mow_Motor_Speed = Mow_Motor_Speed;
		analogWrite(PIN_MOW_MOTOR_RIGHT_SPEED, Mow_Motor_Speed);
		analogWrite(PIN_MOW_MOTOR_CENTER_SPEED, Mow_Motor_Speed);
		analogWrite(PIN_MOW_MOTOR_LEFT_SPEED, Mow_Motor_Speed);
	}
	
	/* manage the right Wheel motor */
	Wheel (RightMotor, RemoteXY.joystick_1_y - RemoteXY.joystick_1_x);
	/* manage the left Wheel motor */
	Wheel (LeftMotor, RemoteXY.joystick_1_y + RemoteXY.joystick_1_x);
}
