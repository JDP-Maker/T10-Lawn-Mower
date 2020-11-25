/*
	includes_defines_variables.h
	-- LawnBot --
	
	This source code of graphical user interface
	has been generated automatically by RemoteXY editor.
	To compile this code using RemoteXY library 2.4.3 or later version
	download by link http://remotexy.com/en/library/
	To connect using RemoteXY mobile app by link http://remotexy.com/en/download/
	- for ANDROID 4.5.1 or later version;
	- for iOS 1.4.1 or later version;
	
	This source code is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.
*/



//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library

//pick the right define for connect type
//#define REMOTEXY_MODE__ESP8266_HARDSERIAL  //connect to exsisting WiFi Access Point, get IP, App connect to IP
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT  //ESP8266 will create a WiFi Access Point
//#define REMOTEXY_MODE__ESP8266_HARDSERIAL_CLOUD  //conect to exsisting WiFi Access Point, then Cloud server
//#define REMOTEXY__DEBUGLOGS message_out

#include <RemoteXY.h>

// RemoteXY connection settings
#ifdef REMOTEXY_MODE__ESP8266_HARDSERIAL
	#define REMOTEXY_SERIAL Serial2
	#define REMOTEXY_SERIAL_SPEED 115200
	#define REMOTEXY_WIFI_SSID "PAGEWORLD"
	#define REMOTEXY_WIFI_PASSWORD "JOHN2018"
	#define REMOTEXY_SERVER_PORT 6377
#endif

// RemoteXY connection settings
#ifdef REMOTEXY_MODE__ESP8266_HARDSERIAL_CLOUD
	#define REMOTEXY_SERIAL Serial2
	#define REMOTEXY_SERIAL_SPEED 115200
	#define REMOTEXY_WIFI_SSID "PAGEWORLD"
	#define REMOTEXY_WIFI_PASSWORD "JOHN2018"
	#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
	#define REMOTEXY_CLOUD_PORT 6376
	#define REMOTEXY_CLOUD_TOKEN "68761ab39de863f1222b58f5a0acb5e7"
#endif

// RemoteXY connection settings
#ifdef REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT
	#define REMOTEXY_SERIAL Serial2
	#define REMOTEXY_SERIAL_SPEED 115200
	#define REMOTEXY_WIFI_SSID "RemoteXY"
	#define REMOTEXY_WIFI_PASSWORD "12345678"
	#define REMOTEXY_SERVER_PORT 6377
#endif

// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
{ 255, 4, 0, 0, 0, 76, 0, 10, 16, 1,
	5, 32, 3, 43, 55, 55, 39, 54, 31, 4,
	128, 1, 1, 65, 11, 5, 26, 129, 0, 21,
	1, 22, 4, 8, 66, 108, 97, 100, 101, 32,
	83, 112, 101, 101, 100, 0, 2, 0, 8, 15,
	50, 9, 2, 26, 31, 31, 79, 78, 0, 79,
	70, 70, 0, 129, 0, 20, 11, 26, 4, 8,
	77, 111, 116, 111, 114, 115, 32, 82, 101, 108,
	97, 121, 0
};

// this structure defines all the variables and events of your control interface
struct {
	
	// input variables
	int8_t joystick_1_x; // =-100..100 x-coordinate joystick position
	int8_t joystick_1_y; // =-100..100 y-coordinate joystick position
	int8_t Blade_Speed; // =0..100 slider position
	uint8_t Motor_Relay; // =1 if switch ON and =0 if OFF
	
	// other variable
	uint8_t connect_flag;  // =1 if wire connected, else =0
	
} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27

/* defined the right motor control pins */
#define PIN_MOTOR_RIGHT_UP 23
#define PIN_MOTOR_RIGHT_DN 22
#define PIN_MOTOR_RIGHT_SPEED 9

/* defined the left motor control pins */
#define PIN_MOTOR_LEFT_UP 24
#define PIN_MOTOR_LEFT_DN 25
#define PIN_MOTOR_LEFT_SPEED 10

/* defined the Relay pin */
#define RELAY 26



int Status = 0;
int Old_Status = 0;
int Relay_Status = 0;
int Old_Relay_Status = 0;
int Mow_Motor_Speed = 0;
int Old_Mow_Motor_Speed = 0;
int while_loop_active = 0;

/* defined two arrays with a list of pins for each motor */
unsigned char RightMotor[3] =
{PIN_MOTOR_RIGHT_UP, PIN_MOTOR_RIGHT_DN, PIN_MOTOR_RIGHT_SPEED};
unsigned char LeftMotor[3] =
{PIN_MOTOR_LEFT_UP, PIN_MOTOR_LEFT_DN, PIN_MOTOR_LEFT_SPEED};
