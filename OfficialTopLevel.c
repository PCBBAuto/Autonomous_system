#include <stdio.h>
#include <stdbool.h> 
#include <wiringPi.h>
#include "Emergency_State.h"
#include "ads1115_rpi.c"
#include "Speed_Control.h"
#include "Yaw_Control.h"


//State Defines
#define Init_State           69
#define Start_State          0
#define Outbound_State       1
#define Emergency_State      2
#define OrientationA_State   3
#define AnchorDrop_State     4
#define Collection_State     5
#define AnchorRetrieve_State 6
#define OrientationB_State   7
#define Return_State         8
#define Dock_State           9
#define Test_State           666

//General Defines
#define DELAY    420
#define GoButton 23
#define NO_ERROR 0 
#define ON       1
#define OFF      0
#define BEACONPIN 11

//Speed Control
#define MAXSPEED 3
#define STOP     0
#define SPEED1   1
#define SPEED2   2

//OutBound State Defines
#define Init_Outbound 		   0
#define IncSpeed_Outbound 	   1
#define CourseCalc_Outbound    2
#define CourseCheck_Outbound   3

//Collection Defines
#define GPS_Coordinate_Files "GPS_Coordinate_Files.txt"
#define INIT_COLLECTION 0
#define CHECK_ERROR_COLLECTION 1
#define COLLECTION 3
#define NextSTATE 4
#define COLLECTION_TIME 120000 //2 min collection time

//Declare Function Prototypes
int PositionError(float LAT1,float LON1, float LAT2, float LON2);

//Declare Structs
struct Coordinates {
	float DestinationLat;
	float DestinationLong;
	float CurrentLong;
	float CurrentLat;
	float CorrectLong;
	float CorrectLat;
} coordinates; 

struct Trolly {
	int currentSpeed;
	int desiredSpeed;
} trolly; 


int main(int argc, char **argv)
{
	//Initialization and Setup
	if(wiringPiSetup() == -1){
		printf("Setup Failed\r\n");
		return 0;
		}
	
	//Initialize Pins
	pinMode(GoButton, INPUT);
	pinMode(BEACONPIN, OUTPUT);
	digitalWrite(BEACONPIN, OFF);
	
	//Declare Initial States	
	int state = Init_State;
	state = Test_State;
	int State_OutB = Init_Outbound;
	
	//Declare Variables
	int ErrorCode = 0b000000;	
	int Confirmation = 0;
	int Go = 0;
	int i = 0;
	int newBearing = 0;
	int lastState = 0;
	trolly.currentSpeed = 0;
	trolly.desiredSpeed = 0;
	
	//Declar Collection Variables
	float NewGPSdataLAT=0;
	float NewGPSdataLON=0;
	float OldGPSdataLAT=0;
	float OldGPSdataLON=0;
	int collectionTimerStart = 0;
	int collectionTimerEnd = 0;
	int deltaCollection = 0;
	int collection_state = INIT_COLLECTION;
	FILE *file_ptr;
	
	
	//Initialize Sensors
	for(i=0; i<=2;i++) {
		//ErrorCheck();
		printf("\e[1;1H\e[2J");
	}

/***********************************************************************
*							Code Starts Here						   *
***********************************************************************/
while(1){
switch(state){
/***********************************************************************
*							Init
***********************************************************************/
case Init_State: {
	//Get Error Code
	ErrorCode = ErrorCheck();
	if(ErrorCode != NO_ERROR){
		lastState = state; 
		state = Emergency_State;
		printf("Entering Emergency State \r\n");
		break;
	}
		
	//Get User Destination Coordinate Input
    printf("Hello. please input the destinations LATUTUDE.\r\n");
    scanf("%f", &coordinates.DestinationLat);
    printf("Please input the destinations LONGITUDE. \r\n");
    scanf("%f", &coordinates.DestinationLong);
    printf("You input LATITUDE: %.3f, and LONGITUDE: %.3f \r\n", coordinates.DestinationLat, coordinates.DestinationLong);
    printf("Are these values correct? Press 1 for YES, 0 for NO.\r\n");
    scanf("%d", &Confirmation);
    
    //Check User Input
    if(Confirmation == 1){
		state = Start_State;
		printf("Coordinates saved. Entering Starting State.\r\n");
		printf("Press GO when ready.\r\n");
		break;
		}
		
	//If the user input coordinates incorrectly	
		printf("Coordinates discarded. \r\n");
		delay(DELAY);
		printf("\e[1;1H\e[2J");

	break;
}
/***********************************************************************
*							Start						   
***********************************************************************/
case Start_State: {

	//Run Error Check
	ErrorCode = ErrorCheck();
	if(ErrorCode != NO_ERROR){
		lastState = state;
		state = Emergency_State;
		printf("Entering Emergency State \r\n");
		break;
	}

	//Check Go button
	Go = digitalRead(GoButton);
	if(Go == 1){
		state = Outbound_State;
		break;
		}
	

	break;
}
/***********************************************************************
*							Outbound							   	
***********************************************************************/
case Outbound_State:

	switch(State_OutB){
		case Init_Outbound:
		//Get Error Code
		ErrorCode = ErrorCheck();
		if(ErrorCode != NO_ERROR){
			lastState = state;
			state = Emergency_State;
			printf("Entering Emergency State \r\n");
			break;
		}
		
		//Transition to IncSpeed
		State_OutB = IncSpeed_Outbound;
		trolly.desiredSpeed = MAXSPEED;
		break;
		
		case IncSpeed_Outbound:		
		//Increase speed to 3
		DesireSpeed(trolly.currentSpeed, trolly.desiredSpeed);		
		break;
		
		case CourseCalc_Outbound:
		newBearing = courseCalc(coordinates.DestinationLat, coordinates.DestinationLong);
		YawControl(newBearing);
		break;
		
		case CourseCheck_Outbound:
		//Compare current location to destination location
		break;		
		}
	

	break;
/***********************************************************************
*							Emergency						   
***********************************************************************/
case Emergency_State:
	//Call Emergency Phase
	Emergency(ErrorCode);
	
	
	//Restart Program
	state = lastState;
	
	break;
/***********************************************************************
*							Orientation A						   
***********************************************************************/
case OrientationA_State:

	return 0;
	break;
/***********************************************************************
*							Anchor Drop								   
***********************************************************************/
case AnchorDrop_State:


	return 0;
	break;
/***********************************************************************
*							Collection						   
***********************************************************************/
case Collection_State:
	
		//Main state
		switch(collection_state){
			
			case INIT_COLLECTION:
				//Start Timer
				collectionTimerStart = millis();				
				collection_state = CHECK_ERROR_COLLECTION;
				break;
				
			case CHECK_ERROR_COLLECTION:
				
				//Error Check
				ErrorCode = ErrorCheck();
				if(ErrorCode != 0){
					lastState = state;
					state = Emergency_State;
					printf("Entering Emergency State \r\n");
					break;
				}
				
				//Transition states
				collection_state = COLLECTION;
				break;
			
			case COLLECTION:
				
				//Get GPS Datat
				getGPS(&NewGPSdataLAT, &NewGPSdataLON, &Error);
				
				//Get New Time
				collectionTimerEnd = millis();
				
				//Update GPS File
				if(PositionError(NewGPSdataLAT,NewGPSdataLON,OldGPSdataLAT,OldGPSdataLON) == 0){
					collection_state = INIT_COLLECTION;
				
				}else{
						printf("Latitde: %lf Longitude %lf\r\n",NewGPSdataLAT,NewGPSdataLON);
						file_ptr = fopen(GPS_Coordinate_Files, "a");
						fprintf(file_ptr,"Latitde: %f Longitude %f \r\n",NewGPSdataLAT,NewGPSdataLON);
						fclose(file_ptr);
						OldGPSdataLAT = NewGPSdataLAT;
						OldGPSdataLON = NewGPSdataLON;
						collection_state = INIT_COLLECTION;
						}
						
				//Check if Collection Time is Over
				deltaCollection = collectionTimerEnd - collectionTimerStart;
				if(deltaCollection >= COLLECTION_TIME){
					state = AnchorRetrieve_State;
					collection_state = INIT_COLLECTION;
					
					} 		
				break;		
		}

	break;
/***********************************************************************
*							Anchor Retrieve								   
***********************************************************************/
case AnchorRetrieve_State:


	return 0;
	break;
/***********************************************************************
*							Orientation B								   
***********************************************************************/
case OrientationB_State:


	return 0;
	break;
/***********************************************************************
*							Return								   
***********************************************************************/
case Return_State:


	return 0;
	break;
/***********************************************************************
*							Dock								   
***********************************************************************/
case Dock_State:


	return 0;
	break;
	
/***********************************************************************
*							Test								   
***********************************************************************/
case Test_State:
	
	printf("Heading = %d\r\n", getHeading());
	delay(500);                       


	break;
/***********************************************************************
*							End Code								   
***********************************************************************/	
	return 0;
}
}
}



/***********************************************************************
*							Helper Function							   
***********************************************************************/

/***********************************************************************
*							position Error								   
***********************************************************************/
int PositionError(float LAT1,float LON1, float LAT2, float LON2){
	if(((LAT2-LAT1)<.0001)   && 
      ((LAT1-LAT2)<.0001)    &&
	  ((LON2-LON1)<.0001)  &&
	  ((LON1-LON2)<.0001)){
		  printf("0 \n");
		  return 0;
	  }else {
		  printf("1 \n");
		  return 1;
	  }
}
