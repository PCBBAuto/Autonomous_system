#include <stdio.h>
#include <wiringPi.h>
#include "tiltError.h"
#include "magError.h"
#include "Battery_Check.h"

//State Defines
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

//General Defines
#define FAILED 0

int ErrorCheck()
{
	//Initialization and Setup
	if(wiringPiSetup() == -1){
		printf("Setup Failed\r\n");
		return 0;
		}
		
	//Declare Variables	
	int ErrorCode = 0b000000;
	int n = 0;
	
	//REPLACE THERE WITH ERROR CHECK FUNCTIONS
	int BatteryCheck = BatteryCheck();
	int WaterCheck = WLSC(); // water level 
	int TiltCheck = isBoatTilted(); 
	int HumidityCheck = humidity();
	int GyroCheck = magCheck();
	int GPSCheck = 0;

/***********************************************************************
*							Code Starts Here						   *
***********************************************************************/	
	//Check for Battery Error
	if(BatteryCheck == FAILED){
		
		ErrorCode |= BATTERY_ERROR_CODE;
		
		}
	//Check for Water Error
	if(WaterCheck == FAILED){
		
		ErrorCode |= WATER_ERROR_CODE;
		
		}
	//Check for Humidity Error
	if(HumidityCheck == FAILED){
		
		ErrorCode |= HUMIDITY_ERROR_CODE;
		
		}
	//Check for Tilt Error
	if(TiltCheck == FAILED){
		
		ErrorCode |= TILT_ERROR_CODE;
		
		}
	//Check for GPS Error
	if(GPSCheck == FAILED){
		
		ErrorCode |= GPS_ERROR_CODE;
		
		}
	//Check for Gyro Error
	if(GyroCheck == FAILED){
		
		ErrorCode |= GYRO_ERROR_CODE;
		
		}
	
	//Print Error Code In Binary
	n = ErrorCode;
	printf("Error Code = ");
	while(n){
		if (n & 1) printf("1");
		else printf("0");
		
		n >>=1;
		}
		printf(", %d\n", ErrorCode);
	
	return ErrorCode;
}



