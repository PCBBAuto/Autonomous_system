//DO NOT DELE
/*#include "Speed_Control.h"
Develop Isolation Code Rev.2*/
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
#define Delay 250

/***********************************************************************
*							FUNCTION HANDLE							   *
***********************************************************************/
//MOTOR FUNCTION HANDLE
void Motor();
void SpeedUP(int);
void SpeedDOWN(int);
void DesireSpeed(int C, int D);

/***********************************************************************
					Component Pin Defines for PI
***********************************************************************/
//Trolly Motor (SEE PI PIN DIAGRAM)
#define TrollySpeedUp 	21 //Board Pin21
#define TrollySpeedDwn	25 //Board Pin25
#define MotorSwitch		23  //Board Pin23

/***********************************************************************
*							MOTOR_INIT CODE							   *
***********************************************************************/
static inline void SpeedControl(int CurrentSpeed, int DesSpeed){
//int main(int argc, char **argv){	//TEST HEADER FOR .C FILES
	//(TEST CODE) User input NEED TO SET AS FUNCTION PARAMETERS
	//int DesSpeed = 5;
	//int CurrentSpeed = 2; 
	
	//initialization and setup FOR PI(STANDARD)
	if(wiringPiSetup() == -1){
		printf("\r\nSetup Failed\r\n");
	//return 0;	//UNCOMMENT FOR INT MAIN HEADER USEAGE
		}
		
	//Setup PI for Trolly Motor
	pinMode(TrollySpeedUp, OUTPUT);
	pinMode(TrollySpeedDwn, OUTPUT);
	pinMode(MotorSwitch, OUTPUT);
	//initialization ALL PINS TO BE OFF
	digitalWrite(TrollySpeedUp, OFF);
	digitalWrite(TrollySpeedDwn, OFF);
	digitalWrite(MotorSwitch, OFF);
	
	//Turn Motor ON
	Motor();
	//KEY FUNCTION
	DesireSpeed(CurrentSpeed, DesSpeed);
	printf("\r\nTEST Completed\r\n");

	//return 0;	//UNCOMMENT FOR INT MAIN HEADER USEAGE
}

/***********************************************************************
*							Code Starts Here						   *
***********************************************************************/
//KEY CODE FOR SPEED CONTROL
void DesireSpeed(int CSpeed, int DSpeed){
	
	int CalculatedSpeed = -CSpeed + DSpeed; //ORDER MATTERS
	if(CalculatedSpeed < 0)
	{
		SpeedDOWN(abs(CalculatedSpeed));
	}
	if(CalculatedSpeed > 0){
		SpeedUP(CalculatedSpeed);
	}
}

/***********************************************************************
*							MOTOR_SPEEDUP								*	
***********************************************************************/	
void SpeedUP(int Calc)
{
	int i = 0;
	while(i <= Calc){
	//TEST CALCULATION
	printf("\nMotor Speed UP: ");
	printf("%d",i);
	//Increase Motor Speed
	digitalWrite(TrollySpeedUp, ON);
	delay(Delay);
	digitalWrite(TrollySpeedUp, OFF);
	i++;
	}
}

/***********************************************************************
*							MOTOR_SPEEDDOWN							   *
***********************************************************************/	
void SpeedDOWN(int Calc)
{
	int i = Calc;
	while(i >= 0){
	//TEST CALCULATION
	printf("\nMotor Speed Down: ");
	printf("%d",i);
	//Decrease Motor Speed
	digitalWrite(TrollySpeedDwn, ON);
	delay(Delay);
	digitalWrite(TrollySpeedDwn, OFF);
	i--;
	}
}

/***********************************************************************
*							MOTOR_Control								   *
***********************************************************************/
void Motor()
{
	//Motor ON
	printf("\nMotor ON OR OFF\r\n");
	digitalWrite(MotorSwitch, ON);
	delay(Delay);
	digitalWrite(MotorSwitch, OFF);

}


