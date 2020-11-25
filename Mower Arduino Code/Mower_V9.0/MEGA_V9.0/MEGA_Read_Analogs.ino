// This File should act just like TXRX_NANO.ino
// It should set the same Variables that TXRX_NANO.ino does
// It will call Calculate_Volt_Amp_Charge at the end just like TXRX_NANO.ino

// These Pins are read by the adcman feature as analog.read can't be used anymore.

void Read_Bat_Rain_Wheel() {

// Run the ADCman to get the pin values as per the settings
	ADCMan.run();
      RawValueAmp = ADCMan.read(Battery_Amps);                              // 
	  RawValueVolt = ADCMan.read(Battery_Volts);                            //  
      Rain_Detected = ADCMan.read(Rain_Sensor);                             // 
      RawWheelAmp = ADCMan.read(Wheel_Amps);                                // 

  //message_out.print("WAMpRaw: ");
  //message_out.print(RawWheelAmp);
  //message_out.print(" |");

Calculate_Volt_Amp_Charge();

}
