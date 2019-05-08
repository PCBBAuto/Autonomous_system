//DO NOT DELE
/*#include "Yaw_Control.h"
Develop Isolation Code Rev.5*/
//Michael Choi
//5/1/19
//EE129 Senior Capstone

/***********************************************************************
*				Standard Libary for PI configuration				   *
***********************************************************************/
//Standard Libary for PI configuration
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
//Misc Defines (IMPORTANT)
#define OFF 0
#define ON 1
#define Delay 325

/***********************************************************************
*							FUNCTION HANDLE							   *
***********************************************************************/
//MOTOR FUNCTION HANDLE
void TurnRight(int);
void TurnLeft(int);
void DesireTurn(int C, int D);
//void MotorReverse(); //Counter steering

/***********************************************************************
					Component Pin Defines for PI
***********************************************************************/
//Trolly Motor (SEE PI PIN DIAGRAM)
#define ServoRight     22  //Board Pin22
#define ServoLeft  	   24 //Board Pin24

/***********************************************************************
*							MOTOR_INIT CODE							   *
***********************************************************************/
static inline void YawControl(int CurrentPosition, int DesirePosition){
//int main(int argc, char **argv){	//TEST HEADER FOR .C FILES
	//(TEST CODE) User input NEED TO SET AS FUNCTION PARAMETERS
	//int DesSpeed = 5;
	//int CurrentSpeed = 2; 
	printf("\rInitialization Completed\r\n");
	
	//initialization and setup FOR PI(STANDARD)
	if(wiringPiSetup() == -1){
		printf("\r\nSetup Failed\r\n");
	//return 0;	//UNCOMMENT FOR INT MAIN HEADER USEAGE
		}
	printf("\r\nTEST DesireTurn\r\n");
	
	//Setup PI for Trolly Motor
	pinMode(ServoRight, OUTPUT);
	pinMode(ServoLeft, OUTPUT);
	//initialization ALL PINS TO BE OFF
	digitalWrite(ServoRight, OFF);
	digitalWrite(ServoLeft, OFF);
	
		//limitations
	if(DesirePosition > 90)
	{
		DesirePosition = 90;
	}
	if(DesirePosition < -90)
	{
		DesirePosition = -90;
	}
	
	//KEY FUNCTION
	DesireTurn(CurrentPosition/22, DesirePosition/22);
	CurrentPosition = DesirePosition;
	printf("\r\nTESTED\r\n");

	//return 0;	//UNCOMMENT FOR INT MAIN HEADER USEAGE
}

/***********************************************************************
*							Code Starts Here						   *
***********************************************************************/
//KEY CODE FOR STEERING (TURNING) YAW CONTROL
void DesireTurn(int Current, int Desire){
	int Calculated = -Current + Desire; //ORDER MATTERS
	if(Calculated < 0) 
	{
		TurnLeft(abs(Calculated));
	}
	if(Calculated > 0){
		TurnRight(Calculated);
	}
}

/***********************************************************************
*							MOTOR_CLOCKWISE								*	
***********************************************************************/	
void TurnRight(int Calc)
{
	int i = 0;
	while(i <= Calc){
	//TurnRight (CLOCKWISE)
	printf("\nTurnRight: ");
	digitalWrite(ServoRight, ON);
	delay(Delay);
	digitalWrite(ServoRight, OFF);
	//delay(Delay);
	printf("%d",i);
	i++;
	}
}

/***********************************************************************
*							MOTOR_COUNTER						   *
***********************************************************************/	
void TurnLeft(int Calc)
{
	int i = Calc;
	while(i >= 0){
	//TurnLeft (COUNTERCLOCKWISE)
	printf("\nTurnLeft: ");
	digitalWrite(ServoLeft, ON);
	delay(Delay);
	digitalWrite(ServoLeft, OFF);
	//delay(Delay);
	printf("%d",i);
	i--;
	}
}

/***********************************************************************
*							MOTOR_Control								   *
***********************************************************************/
/*void MotorReverse()
{
	//MotorReverse //need math for counter steering
	printf("\nMotorReverse\r\n");
	if
	digitalWrite(x, ON);
	delay(Delay);
	digitalWrite(x, OFF);

}*/


