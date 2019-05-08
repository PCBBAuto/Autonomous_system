#include <stdio.h>
#include <stdbool.h> 
#include <wiringPi.h>
#include "Emergency_State.h"
#include "ads1115_rpi.c"


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

//General Defines
#define DELAY 400
#define GoButton 23

//OutBound State Defines
#define Init_Outbound 		   0
#define Speed2_Outbound 	   1
#define CourseCalc_Outbound    2
#define CourseCorrect_Outbound 3

//Declare Structs
struct Coordinates {
	float DestinationLat;
	float DestinationLong;
	float CurrentLong;
	float CurrentLat;
	float CorrectLong;
	float CorrectLat;
} coordinates; 


int main(int argc, char **argv)
{
	//Initialization and Setup
	if(wiringPiSetup() == -1){
		printf("Setup Failed\r\n");
		return 0;
		}
	
	//Initialize Pins
	pinMode(GoButton, INPUT);
	
	//Declare Initial States	
	int state = Init_State;
	int State_OutB = Init_Outbound;
	
	//Declare Variables
	int ErrorCode = 0;	
	int Confirmation = 0;
	int Go = 0;
	

	
/***********************************************************************
*							Code Starts Here						   *
***********************************************************************/
while(1){
switch(state){
/***********************************************************************
*							Init
***********************************************************************/
case Init_State:
	//Run Error Check 
	//**put function here
		
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
/***********************************************************************
*							Start						   
***********************************************************************/
case Start_State:

	//Run Error Check
	//**input function here**
	
	//Check Go button
	Go = digitalRead(GoButton);
	if(Go == 1){
		state = Outbound_State;
		break;
		}
	

	break;
/***********************************************************************
*							Outbound							   
***********************************************************************/
case Outbound_State:

	while(1){
	switch(State_OutB){
		case Init_Outbound:
		//Run Error Check
		
		break;
		
		case Speed2_Outbound:
		break;
		
		case CourseCalc_Outbound:
		break;
		
		case CourseCorrect_Outbound:
		break;
	
		}
	}

	break;
/***********************************************************************
*							Emergency						   
***********************************************************************/
case Emergency_State:
	//Call Emergency Phase
	state = Emergency(ErrorCode);

	return 0;
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

	return 0;
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
*							End Code								   
***********************************************************************/	
	return 0;
}
}
}


