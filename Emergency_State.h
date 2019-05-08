#include <stdio.h>
#include <wiringPi.h>


//Emergency State Defines
#define PARSE_ERROR_STATE    0
#define HUMIDITY_ERROR_STATE 1
#define BATTERY_ERROR_STATE  2
#define TILT_ERROR_STATE     3
#define GYRO_ERROR_STATE     4
#define WATER_ERROR_STATE    5
#define GPS_ERROR_STATE      6

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


static inline int Emergency(int ErrorCode)
{
	//Initialization and Setup
	if(wiringPiSetup() == -1){
		printf("Setup Failed\r\n");
		return 0;
		}
		
	//Declare Variables, Emergency	
	int state = PARSE_ERROR_STATE;	
	
	//Declare Variables and Pins, Water Error
	pinMode(WATER_PUMP_PIN,OUTPUT);
	int WLCheck = 0;
	int waterState = WATER_INIT;
	
/***********************************************************************
*							Code Starts Here						   *
***********************************************************************/
while(1){
switch(state){
/***********************************************************************
*							Parse Error 								   *
***********************************************************************/
case PARSE_ERROR_STATE:

	//Check for No Error
	if(ErrorCode == NO_ERROR_CODE){
		printf("No Error Detected \n");				
		return 0;
		
		}
	//Check for Battery Error	
	else if((ErrorCode & BATTERY_ERROR_CODE) == BATTERY_ERROR_CODE){
		printf("Battery Error Detected");		
		state = BATTERY_ERROR_STATE;
		break;
		
		}
	//Check for Water Error	
	else if((ErrorCode & WATER_ERROR_CODE) == WATER_ERROR_CODE){
		printf("Water Error Detected");		
		state = WATER_ERROR_STATE;
		break;
		
		}
	//Check for Humidity Error	
	else if((ErrorCode & HUMIDITY_ERROR_CODE) == HUMIDITY_ERROR_CODE){
		printf("Humidity Error Detected");		
		state = HUMIDITY_ERROR_STATE;
		break;
		
		}
	//Check for Tilt Error	
	else if((ErrorCode & TILT_ERROR_CODE) == TILT_ERROR_CODE){
		printf("Tilt Error Detected");		
		state = TILT_ERROR_STATE;
		break;
		
		}
	//Check for Gyro Error	
	else if((ErrorCode & GYRO_ERROR_CODE) == GYRO_ERROR_CODE){
		printf("Gyro Error Detected");		
		state = GYRO_ERROR_STATE;
		break;
		
		}
	//Check for GPS Error	
	else if((ErrorCode & GPS_ERROR_CODE) == GPS_ERROR_CODE){
		printf("GPS Error Detected");		
		state = GPS_ERROR_STATE;
		break;
		
		}


	break;
/***********************************************************************
*							Humidity Error 							   *
***********************************************************************/
case HUMIDITY_ERROR_STATE:
	//Insert Error Actions

	
	return 0;
	break;
/***********************************************************************
*							Battery Error								   *
***********************************************************************/
case BATTERY_ERROR_STATE:
	//Insert Error Actions

	return 0;
	break;
/***********************************************************************
*							Tilt Error							   *
***********************************************************************/
case TILT_ERROR_STATE:
	//Insert Error Actions

	return 0;
	break;
/***********************************************************************
*							Gyro Error 							   *
***********************************************************************/
case GYRO_ERROR_STATE:
	//Insert Error Actions

	return 0;
	break;
/***********************************************************************
*							Water Error Code								   *
***********************************************************************/
case WATER_ERROR_STATE:
	
	//main code
	while(1){
		switch(waterState){
			case WATER_INIT:
				state = WATER_CHECK;
				break;
			
			case WATER_CHECK:
				//Calling water sensor function
				//WLCheck = WLSC(); 
				//include battery Below
			
				if(WLCheck == 1){
					state = WATER_WPUMPON;
				}else if (WLCheck == 0){
					state = WATER_EXITSTATE;
				}else{
					state = WATER_EMEGENCY;
				}
				break;
			case WATER_EMEGENCY:
				printf("Nothing happened yet \n");
				state = WATER_CHECK;
				break;
			case WATER_WPUMPON:
				digitalWrite(WATER_PUMP_PIN, HIGH);
				state = WATER_CHECK;
				break;
			case WATER_EXITSTATE:
				printf("water pump turned off \n");
				digitalWrite(WATER_PUMP_PIN, LOW);
				return 0;
				break;
		}
	}

	return 0;
	break;
/***********************************************************************
*							GPS Error Code								   *
***********************************************************************/
case GPS_ERROR_STATE:
	//Insert Error Actions

	return 0;
	break;
	
	
}
return 0;
}
}

