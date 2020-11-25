void Check_Sonar_Sensors() {
	
	// Ping Sonar sensors
	
	//Clears the Trig Pin
	digitalWrite(trigPin1, LOW);
	delayMicroseconds(5);
	digitalWrite(trigPin2, LOW);
	delayMicroseconds(5);
	digitalWrite(trigPin3, LOW);
	
	// Pings each sonar at a 15ms interval
	
	if (Sonar_2_Activate == 1) distance2 = PingSonarX(trigPin2, echoPin2, 2, 2, 2, 0, 0);         //SONAR2
	if (Sonar_1_Activate == 1) distance1 = PingSonarX(trigPin1, echoPin1, 1, 1, 1, 1, 0);         //SONAR1
	if (Sonar_3_Activate == 1) distance3 = PingSonarX(trigPin3, echoPin3, 3, 3, 3, 2, 0);         //SONAR3
	
	if (Sonar_5_Activate == 1) distance5 = PingSonarX(trigPin5, echoPin5, 5, 5, 5, 0, 0);         //SONAR5 added JDP
	if (Sonar_4_Activate == 1) distance4 = PingSonarX(trigPin4, echoPin4, 4, 4, 4, 1, 0);         //SONAR4 added JDP
	if (Sonar_6_Activate == 1) distance6 = PingSonarX(trigPin6, echoPin6, 6, 6, 6, 2, 0);         //SONAR6 added JDP
	
}



/* SONAR Function
************************************************************************************/
// Function to Ping the Sonar calculate the distance from Object to the Sonars.
// Distance calculated is printed to serial printer and displays X or _ on the LCD Screen
// Distance calculated is then used for the object avoidance logic
// Sonars used can be activated in the settings.

int PingSonarX(int trigPinX, int echoPinX, int distanceX, long durationX, int sonarX, int LCDRow, int LCDColumn) {
	pinMode(trigPinX, OUTPUT);
	pinMode(echoPinX, INPUT);
	//Sets the trigPin at High state for 10 micro secs sending a sound wave
	digitalWrite(trigPinX, HIGH);
	digitalWrite(trigPinX, LOW);
	delayMicroseconds(10);
	
	/*Reads the echoPin for the bounced wave and records the time in microseconds*/
	durationX = pulseIn(echoPinX, HIGH);
	
	/*Calculates the distance in cm based on the measured time*/
	distanceX = durationX * 0.034 / 2;
	delay(5);
	
	/* If a 0 distance is measured normally the Sonar ping has not been received.
	distance is then set to 999cm so the missed ping is not seen as an object detected.*/
	if (distanceX == 0) {
		distanceX = 999;
		message_out.print(F("S"));
		message_out.print(sonarX);
		message_out.print(F(":"));
		message_out.print(F("NP!"));
		message_out.print(F("|"));
	}
	
	/*Prints the Sonar letter and distance measured on the serial Monitor*/
	message_out.print(F("S"));
	message_out.print(sonarX);
	message_out.print(F(":"));
	message_out.print(distanceX);
	message_out.print(F("cm"));
	message_out.print(F("/"));
	
	/*If sonar distance is less than maximum distance then an object is registered to avoid*/
	if (distanceX <= maxdistancesonar ) {
		//Prints that Sonar X has detected an object to the Mower LCD.
		lcd.setCursor(LCDRow, LCDColumn);                //sets location for text to be written
		lcd.print("X");
		delay(10);
		if (sonarX == 1) {
			Sonar_Hit_1_Total = (Sonar_Hit_1_Total + 1);
			message_out.print(Sonar_Hit_1_Total);
		}
		if (sonarX == 2) {
			Sonar_Hit_2_Total = (Sonar_Hit_2_Total + 1);
			message_out.print(Sonar_Hit_2_Total);
		}
		if (sonarX == 3) {
			Sonar_Hit_3_Total = (Sonar_Hit_3_Total + 1);
			message_out.print(Sonar_Hit_3_Total);
		}
		// Added by JDP ******************************************************************************************
		if (sonarX == 4) {
			Sonar_Hit_3_Total = (Sonar_Hit_3_Total + 1);
			message_out.print(Sonar_Hit_3_Total);
		} 
		if (sonarX == 5) {
			Sonar_Hit_3_Total = (Sonar_Hit_3_Total + 1);
			message_out.print(Sonar_Hit_3_Total);
		} 
		if (sonarX == 6) {
			Sonar_Hit_3_Total = (Sonar_Hit_3_Total + 1);
			message_out.print(Sonar_Hit_3_Total);
		}
		// End add by JDP *****************************************************************************************
		if ( (Sonar_Hit_1_Total == Max_Sonar_Hit) || (Sonar_Hit_2_Total == Max_Sonar_Hit) || (Sonar_Hit_3_Total == Max_Sonar_Hit) ) {
			Sonar_Hit = 1;  
			Print_Sonar_Hit();
			message_out.println(F(""));
			message_out.println("Sonar Hit Detected");
		}
		// Added by JDP ******************************************************************************************
		if ( (Sonar_Hit_2_Total == Max_Sonar_Hit) || (Sonar_Hit_3_Total == Max_Sonar_Hit) || (Sonar_Hit_4_Total == Max_Sonar_Hit) ) {
			Rear_Sonar_Hit = 1;  
			Print_Rear_Sonar_Hit();
			message_out.println(F(""));
			message_out.println("Rear Sonar Hit Detected");
		}
		// End add by JDP *****************************************************************************************
	}
	
	/*If sonar distance is greater than maximum distance then no object is registered to avoid*/
	if (distanceX > maxdistancesonar) {
		//Prints that the path of Sonar X is open.
		lcd.setCursor(LCDRow, LCDColumn);                 //sets location for text to be written
		lcd.print("_");
		delay(10);
		if (sonarX == 1) {
			Sonar_Hit_1_Total = 0;
			message_out.print(Sonar_Hit_1_Total);
		}
		if (sonarX == 2) {
			Sonar_Hit_2_Total = 0;
			message_out.print(Sonar_Hit_2_Total);
		}
		if (sonarX == 3) {
			Sonar_Hit_3_Total = 0;
			message_out.print(Sonar_Hit_3_Total);
		} 
		// Added by JDP ******************************************************************************************
		if (sonarX == 4) {
			Sonar_Hit_4_Total = 0;
			message_out.print(Sonar_Hit_4_Total);
		}
		if (sonarX == 5) {
			Sonar_Hit_5_Total = 0;
			message_out.print(Sonar_Hit_5_Total);
		}
		if (sonarX == 6) {
			Sonar_Hit_6_Total = 0;
			message_out.print(Sonar_Hit_6_Total);
		}
		// End add by JDP *****************************************************************************************
		
	}
	
	
	return distanceX;
	return sonarX;
	
	
	
}
