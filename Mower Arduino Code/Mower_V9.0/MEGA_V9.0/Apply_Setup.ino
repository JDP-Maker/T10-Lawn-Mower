void Print_Mower_Status() {
	//message_out.print("Mower Stat....");
	if (Mower_Docked == 1) message_out.print(F("Docked:1|"));
	if (Mower_Parked == 1) message_out.print(F("Parked:1|"));
	if (Mower_Running == 1) message_out.print(F("Running:1|"));
	if (Manuel_Mode == 1) message_out.print(F("Manuel Mode:1|"));
	if (Mower_Parked_Low_Batt == 1) message_out.print(F("Park_Low_Batt:1|"));
	if (Mower_Error == 1) message_out.print(F("Mower Error:1|"));
	
}


void Setup_Tilt_Tip_Safety() {
	if (Angle_Sensor_Enabled == 1)     pinMode(Tilt_Angle, INPUT);//define Data input pin input pin
	if (Tip_Over_Sensor_Enabled == 1)  pinMode(Tilt_Orientation, INPUT);//define Data input pin input
}

void Prepare_Mower_from_Settings() {
	
	if (Use_Charging_Station == 1) {
		Mower_Docked  = 1;
		Mower_Parked  = 0;
		Mower_Running = 0;
	}
	
	
	if (Use_Charging_Station == 0) {
		Mower_Docked  = 0;
		Mower_Parked  = 1;
		Mower_Running = 0;
	}
}



void Setup_DFRobot_QMC5883_HMC5883L_Compass() {
	
	if (Compass_Activate == 1) {
		
        /*Setup Compass
		*************************************************************************/
        if (LCD_Screen_Keypad_Menu == 1) {
			lcd.clear();
			lcd.print(F("Compass  "));
			lcd.setCursor(0, 1);
			lcd.print(F("Setup"));
		}
		
        int Compass_Attempt = 0;
        int Compass_Found = 0;
		
        //HMC5883 Compass
        while ((!compass.begin()) && (Compass_Attempt <= 5)){
            message_out.println(F("No HMC or QMC5883 sensor found, check wiring!"));
            delay(500);
            Compass_Attempt = Compass_Attempt + 1;
		}
		if (compass.isHMC()) {
			message_out.println(F("Initialize DF Robot HMC5883 Compass"));
			Compass_Detected = 1;                        // HMC5883
			if (LCD_Screen_Keypad_Menu == 1) {
				lcd.setCursor(6,0);
				lcd.print(F(": HMC5883"));
				delay(500);
			}
			
			//compass.setRange(HMC5883L_RANGE_1_3GA);
			//compass.setMeasurementMode(HMC5883L_CONTINOUS);
			//compass.setDataRate(HMC5883L_DATARATE_15HZ);
			//compass.setSamples(HMC5883L_SAMPLES_8);
			//Compass_Found = 1;
		}
		
		//QMC5883 Compass
		else if (compass.isQMC()) {
			message_out.println(F("Initialising DF Robot QMC5883 Compass"));
			Compass_Detected = 2;                        // HMC5883
			if (LCD_Screen_Keypad_Menu == 1) {
				lcd.setCursor(6,0);
				lcd.print(F(": QMC5883"));
				delay(500);
			}
			compass.setRange(QMC5883_RANGE_2GA);
			compass.setMeasurementMode(QMC5883_CONTINOUS); 
			compass.setDataRate(QMC5883_DATARATE_50HZ);
			compass.setSamples(QMC5883_SAMPLES_8);
		}
		
		
		// Escape the loop if no compass is found but compass is activated in the settings
		if ((Compass_Attempt > 5) && (Compass_Found == 0)) {
			message_out.println("No Valid Compass Found");
			Compass_Activate = 0;
			message_out.println("Compass Deactivated");
			delay(3000);
		}
		if (LCD_Screen_Keypad_Menu == 1) {
			lcd.setCursor(0,1); 
			lcd.print(F("Done!             "));
			delay(500);
			lcd.clear();
		}
		//Wire.endTransmission(); 
	}
	
	
	
	if (Compass_Activate == 0) {
		message_out.println(F("Compass Switched off - Select 1 in setup to switch on.")); 
	}
	
}


void Setup_Gyro() {
	
	if (GYRO_Enabled == 1) {
        message_out.println("GYRO GY-521 Activated");
        Wire.begin();
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x6B);
        Wire.write(0);
        Wire.endTransmission(true);  
	}
}


void Setup_Relays() {
	message_out.println(F("Setup Relays"));
	pinMode(Relay_Motors, OUTPUT);
	delay(5);
	Turn_Off_Relay();
	delay(5);
}

//updated by JDP **********************************************************
void Setup_Motor_Pins() {
	message_out.println(F("Setup Motor Pins"));
	//pinMode(L_EN, OUTPUT);
	//pinMode(R_EN, OUTPUT);
	//pinMode(RPWM, OUTPUT);
	pinMode (PIN_MOTOR_RIGHT_UP, OUTPUT);
	pinMode (PIN_MOTOR_RIGHT_DN, OUTPUT);
	pinMode (PIN_MOTOR_LEFT_UP, OUTPUT);
	pinMode (PIN_MOTOR_LEFT_DN, OUTPUT);
	pinMode(PIN_MOW_MOTOR_RIGHT_UP, OUTPUT);
	pinMode(PIN_MOW_MOTOR_RIGHT_DN, OUTPUT);
	pinMode(PIN_MOW_MOTOR_RIGHT_SPEED, OUTPUT);
	pinMode(PIN_MOW_MOTOR_CENTER_UP, OUTPUT);
	pinMode(PIN_MOW_MOTOR_CENTER_DN, OUTPUT);
	pinMode(PIN_MOW_MOTOR_CENTER_SPEED, OUTPUT);
	pinMode(PIN_MOW_MOTOR_LEFT_UP, OUTPUT);
	pinMode(PIN_MOW_MOTOR_LEFT_DN, OUTPUT);
	pinMode(PIN_MOW_MOTOR_LEFT_SPEED, OUTPUT);
	
	//make sure mow moters are stoped to start
	digitalWrite(PIN_MOW_MOTOR_RIGHT_UP, HIGH);
	digitalWrite(PIN_MOW_MOTOR_RIGHT_DN, LOW);
	digitalWrite(PIN_MOW_MOTOR_CENTER_UP, HIGH);
	digitalWrite(PIN_MOW_MOTOR_CENTER_DN, LOW);
	digitalWrite(PIN_MOW_MOTOR_LEFT_UP, HIGH);
	digitalWrite(PIN_MOW_MOTOR_LEFT_DN, LOW);
	analogWrite(PIN_MOW_MOTOR_RIGHT_SPEED, 0);
	analogWrite(PIN_MOW_MOTOR_CENTER_SPEED, 0);
	analogWrite(PIN_MOW_MOTOR_LEFT_SPEED, 0);
}


void  Turn_On_Relay() {
	message_out.print(F("Relay:ON|"));
	if (PCB == 0) digitalWrite(Relay_Motors, HIGH);                         // Turn of the relay for the main battery power JDP
	if (PCB == 1) digitalWrite(Relay_Motors, HIGH); 
}

void  Turn_Off_Relay() {
	message_out.print(F("Relay:Off|"));
	if (PCB == 0) (digitalWrite(Relay_Motors, LOW));                         // Turn of the relay for the main battery power JDP
	if (PCB == 1) (digitalWrite(Relay_Motors, LOW));    
}

void Setup_Membrane_Buttons() {
	message_out.println(F("Setup Membrane Keys"));
	pinMode(Start_Key, INPUT_PULLUP);            // set pin as input
	pinMode(Plus_Key, INPUT_PULLUP);            // set pin as input
	pinMode(Minus_Key, INPUT_PULLUP);            // set pin as input
	pinMode(Stop_Key, INPUT_PULLUP);            // set pin as input  
}


void Setup_Bumper_Bar() {
	pinMode(Bumper_Switch_Frnt_RH, INPUT_PULLUP); 
	pinMode(Bumper_Switch_Frnt_LH, INPUT_PULLUP); 
}

void Setup_ADCMan() {
	message_out.println(F("Setting up ADCMAN"));
	
	ADCMan.init();  // added by JDP, moved out of "if loops", just go ahead and init even if nothing uses ADCMan
	
	if (Perimeter_Wire_Enabled == 1) {
		// Wire Sensor
		message_out.println(F("Setting up Wire Sensor"));
		//ADCMan.init();  //commented out by JDP, moved out of "if loop"  only do once
		ADCMan.setCapture(pinPerimeterLeft, 1, 0);
		perimeter.setPins(pinPerimeterLeft, pinPerimeterRight);
		//   perimeter.useDifferentialPerimeterSignal = true;   //using new Perimeter files JDP
		perimeter.speedTest(); 
	}
	
	if (GPS_Enabled == 1) {
		// GPS Fence Sensor 
		message_out.println(F("Setting up GPS Fence Sensor"));
		pinMode(GPS_Fence_Signal_Pin, INPUT);
		pinMode(GPS_Lock_Pin, INPUT);
		//ADCMan.init();  //commented out by JDP, moved out of "if loop"  only do once
		ADCMan.setCapture(GPS_Fence_Signal_Pin, 1, 1);
		ADCMan.setCapture(GPS_Lock_Pin, 1, 1);
	}
	
	//**********************added by JDP ************************************************************
	if (Use_MEGA_for_Analog_reads == 1) {
		// Use Mega for all Analog sensors
		message_out.println(F("Setting up Bat A, Bat V, Rain, Wheel Sensor"));
      	pinMode(Battery_Amps, INPUT);
		pinMode(Battery_Volts, INPUT);
		pinMode(Wheel_Amps, INPUT);
		pinMode(Rain_Sensor, INPUT);
		//ADCMan.init(); //commented out by JDP, moved out of "if loop"  only do once
		ADCMan.setCapture(Battery_Amps, 1, 1);
		ADCMan.setCapture(Battery_Volts, 1, 0);
		ADCMan.setCapture(Wheel_Amps, 1, 1);
		ADCMan.setCapture(Rain_Sensor, 1, 1);
	}
	// if you do run the calibrate below, make sure loop is off, no charging, no rain, and disconect volt sensor
    //ADCMan.calibrate();  //run this once then comment out    
	ADCMan.run();
}


void Setup_Check_Pattern_Mow() {
	if (Pattern_Mow == 1) {
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("Pattern Mow");
		lcd.setCursor(0,1);
		lcd.print("Parallel");
		delay(1000);
	lcd.clear();
    }
	if (Pattern_Mow == 2) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pattern");
    lcd.setCursor(0,1);
    lcd.print("Spirals");
    delay(1000);
    lcd.clear();
    }
	}
		