#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Error_Check.h"

//General Defines
#define PASS 1
#define FAIL 0
#define BEACONPIN 11
#define ON   1
#define OFF  0

//Emergency State Defines
#define PARSE_ERROR_STATE    0
#define HUMIDITY_ERROR_STATE 1
#define BATTERY_ERROR_STATE  2
#define TILT_ERROR_STATE     3
#define GYRO_ERROR_STATE     4
#define WATER_ERROR_STATE    5
#define GPS_ERROR_STATE      6
#define ERROR_CHECK          7

//Error Code Defines
#define NO_ERROR_CODE		0b000000
#define BATTERY_ERROR_CODE  0b000001
#define WATER_ERROR_CODE    0b000010
#define HUMIDITY_ERROR_CODE 0b000100
#define TILT_ERROR_CODE     0b001000
#define GYRO_ERROR_CODE     0b010000
#define GPS_ERROR_CODE      0b100000

//Water Error Defines
#define WATER_PUMP_PIN 7
#define WATER_INIT 0
#define WATER_CHECK 1
#define WATER_EMEGENCY 2
#define WATER_WPUMPON 3
#define WATER_EXITSTATE 4 

//Tilt Error Defines
#define ROLL_LOW -3.0
#define ROLL_HIGH 103.0
#define PITCH_LOW -58.0
#define PITCH_HIGH 59.0

//Battery Error Defines

//Prototype Functions
void Beacon(int OnOff);


int Emergency(int ErrorCode)
{
	//Initialization and Setup
	if(wiringPiSetup() == -1){
		printf("Setup Failed\r\n");
		return 0;
		}
		
	//Declare Variables, Emergency	
	int state = PARSE_ERROR_STATE;
	int AnchorDeploy = 0;	
	
	//Water Error Variables and Pins 
	pinMode(WATER_PUMP_PIN,OUTPUT);
	int waterState = WATER_INIT;
	
	
/***********************************************************************
*							Code Starts Here						   *
***********************************************************************/
while(1){
switch(state){
/***********************************************************************
*							Parse Error 							   *
***********************************************************************/
case PARSE_ERROR_STATE: 
	printf("EMERGENCY STATE\r\n");
	
	//Check for No Error
	if(ErrorCode == NO_ERROR_CODE){
		printf("No Error Detected \r\n");
		//Turn Off Beacon
		if (AnchorDeploy!=0){
			//ANCHORDOWN(6);//BRINGS THE ANCHOR BACK UP
		}
		Beacon(OFF);				
		return 0;
		
		}
	//Check for Battery Error	
	else if((ErrorCode & BATTERY_ERROR_CODE) == BATTERY_ERROR_CODE){
		printf("Battery Error Detected\r\n");	
		printf("Entering Battery State\r\n");		
		state = BATTERY_ERROR_STATE;
		break;
		
		}
	//Check for Water Error	
	else if((ErrorCode & WATER_ERROR_CODE) == WATER_ERROR_CODE){
		printf("Water Error Detected\r\n");	
		printf("Entering Water State\r\n");		
		state = WATER_ERROR_STATE;
		break;
		
		}
	//Check for Humidity Error	
	else if((ErrorCode & HUMIDITY_ERROR_CODE) == HUMIDITY_ERROR_CODE){
		printf("Humidity Error Detected\r\n");			
		printf("Entering Humidity State\r\n");		
		state = HUMIDITY_ERROR_STATE;
		break;
		
		}
	//Check for Tilt Error	
	else if((ErrorCode & TILT_ERROR_CODE) == TILT_ERROR_CODE){
		printf("Tilt Error Detected\r\n");
		printf("Entering Tilt State\r\n");		
		state = TILT_ERROR_STATE;
		break;
		
		}
	//Check for Gyro Error	
	else if((ErrorCode & GYRO_ERROR_CODE) == GYRO_ERROR_CODE){
		printf("Gyro Error Detected\r\n");			
		printf("Entering Gyro State\r\n");		
		state = GYRO_ERROR_STATE;
		break;
		
		}
	//Check for GPS Error	
	else if((ErrorCode & GPS_ERROR_CODE) == GPS_ERROR_CODE){
		printf("GPS Error Detected\r\n");		
		state = GPS_ERROR_STATE;
		break;
		
		}
	break;
/***********************************************************************
*							Humidity Error 							   *
***********************************************************************/
case HUMIDITY_ERROR_STATE:
	//Turn On Beacon
	Beacon(ON);
	//serves as a check for the water pump sensor
	//does not activate anything on its own
	
	break;
/***********************************************************************
*							Battery Error							   *
***********************************************************************/
case BATTERY_ERROR_STATE:
	//Turn On Beacon
	Beacon(ON);
	//AnchorDOWN(6);
	state = ERROR_CHECK;


	break;
/***********************************************************************
*							Tilt Error							       *
***********************************************************************/
case TILT_ERROR_STATE:
	//Turn On Beacon
	Beacon(ON);
	state = ERROR_CHECK;



	break;
/***********************************************************************
*							Mag Error 							   
***********************************************************************/
case GYRO_ERROR_STATE:
	//Turn On Beacon
	Beacon(ON);
	state = ERROR_CHECK;




	break;
/***********************************************************************
							Water Error Code								  
***********************************************************************/
case WATER_ERROR_STATE:
	//Turn On Beacon
	Beacon(ON);
	
	//main code
		switch(waterState){
			case WATER_INIT:
				waterState = WATER_CHECK;
				break;
			
			case WATER_CHECK:
				//Run Error Check
				ErrorCode = ErrorCheck();
				
				//Check for Battery Error
				if((ErrorCode & BATTERY_ERROR_CODE) == BATTERY_ERROR_CODE){
				printf("Battery Error Detected\r\n");		
				state = BATTERY_ERROR_STATE;
				waterState = WATER_INIT;
				break;
				}
				
				//Check for Water Error	
			    if((ErrorCode & WATER_ERROR_CODE) == WATER_ERROR_CODE){
				printf("Water Error Confirmed\r\n");		
				waterState = WATER_WPUMPON;
				break;
				}
				
				//No Error Detected
				state = ERROR_CHECK;
				waterState = WATER_EXITSTATE;
				break;
				
				
			case WATER_WPUMPON:
				//Turn on Water Pump
				digitalWrite(WATER_PUMP_PIN, HIGH);
				waterState = WATER_CHECK;
				break;
			
			case WATER_EXITSTATE:
				//Exit Water Pump State
				printf("water pump turned off \n");
				digitalWrite(WATER_PUMP_PIN, LOW);
				state = ERROR_CHECK;
				waterState = WATER_INIT; 
				break;
		}

	break;
/***********************************************************************
*							GPS Error Code						       *
***********************************************************************/
case GPS_ERROR_STATE:
	//Insert Error Actions
	
	break;


/***********************************************************************
*							Error Check								   *
***********************************************************************/
case ERROR_CHECK:
	//Run Error Check
	printf("Emergency Error Check State\r\n");
	ErrorCode = ErrorCheck();
	state = PARSE_ERROR_STATE;	
	break;
	

}
}
}





/***********************************************************************
*							Beacon On/Off								   *
***********************************************************************/
void Beacon(int OnOff){
	
	pinMode(BEACONPIN, OUTPUT);
	digitalWrite(BEACONPIN, OnOff);
	}
