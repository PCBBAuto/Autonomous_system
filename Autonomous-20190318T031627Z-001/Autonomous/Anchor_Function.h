
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "Function.h"

/***********************************************************************
					Component Pin Defines
***********************************************************************/
//Reciever Defines
#define RecCh1 26 //Board Pin32
#define RecCh2 23 //Board Pin33
#define RecCh3 24 //Board Pin35
#define RecCh4 27 //Board Pin36

//Gyroscope
#define GyroSDA 8 //Board Pin3
#define GyroSCL 9 //Board Pin5

//AnchorMotor
#define AnchClock 10 //Board Pin24 DOWN
#define AnchCount 11 //Board Pin26 UP
#define AnchLock  7 //Board Pin7

//Trolly Motor
#define TrollySpeedUp  13 //Board Pin21
#define TrollySpeedDwn 14 //Board Pin23```````````
#define ServoRight     1  //Board Pin12
#define ServoLeft  	   21 //Board Pin29
#define Reset  		   29 //Board Pin40
#define MotorOn		   0  //Board Pin11
/**********************************************************************/


//States
#define TOP_LEVEL_INIT 55
#define NOM_POWER_INIT 56
#define LOW_POWER_INIT 57
#define MOTOR_STATE    58
#define ANCHOR_STATE   59
#define EXIT_LOW_POWER 60
#define MOTOR_INIT	   61
#define MOTOR_CLOCK    62
#define MOTOR_COUNTER  63
#define SERVOLEFT 	   64
#define SERVORIGHT     65
#define EXIT_MOTOR     66
#define MOTOR_MOVE_INIT 67
#define MOTOR_MOVE_IDLE 68
#define MOTOR_MOVE      69
#define EXIT_MOTOR_MOVE 70
#define ANCHOR_INIT    71
#define ANCHOR_UP 	   72
#define ANCHOR_DWN	   73
#define EXIT_ANCHOR	   74

//Reciever Defines
#define NOTHING			20
#define MotorSPEEDUP	21
#define MotorSPEEDDOWN	22
#define ServoLEFT		23
#define ServoRIGHT		24
#define RESET			25
#define AnchorMode		26
#define AnchorUP		27
#define AnchorDOWN		28

//Misc Defines
#define OFF 0
#define ON 1
#define YES 1
#define NO 1
#define IDLE 10
#define MOVE_RIGHT 11
#define MOVE_LEFT 12
#define NOMINAL 1
#define LOW 0
#define Delay 250
			
static inline void Anchor_State(){
	
	//initialization and setup
	if(wiringPiSetup() == -1){
		printf("Setup Failed\r\n");
		return;
		}
		
	//Pin Setup - Reciever
	pinMode(RecCh1, INPUT);
	pinMode(RecCh2, INPUT);
	pinMode(RecCh3, INPUT);
	pinMode(RecCh4, INPUT);
	pinMode(GyroSDA, INPUT);
	pinMode(GyroSCL, INPUT);
	pinMode(AnchClock, OUTPUT);
	pinMode(AnchCount, OUTPUT);
	pinMode(AnchLock, OUTPUT);
	pinMode(TrollySpeedUp, OUTPUT);
	pinMode(TrollySpeedDwn, OUTPUT);
	pinMode(ServoRight, OUTPUT);
	pinMode(ServoLeft, OUTPUT);
	pinMode(Reset, OUTPUT);
	
	//declare variables
	int state = ANCHOR_INIT;
	int AnchorLock = OFF;
	int BatteryLevel = NOMINAL;
	int AnchorSwitch = OFF;
	int MrResetti = OFF;
	
	int receiverOutput = 0;
	
	printf("Anchor State Entered\n\r");
/***********************************************************************
					Code Starts Here
***********************************************************************/
while(1){
	switch(state){
			case ANCHOR_INIT:
				//Initialize Variables
				receiverOutput = 0;
				
				//Initialize Pins
				digitalWrite(AnchClock, OFF);
				digitalWrite(AnchLock, OFF);
				digitalWrite(AnchCount, OFF);
				
				//Check Inputs
				receiverOutput = fourVal();	
					//CheckPower();
				
				//Go to ANCHOR_DWN
				if(receiverOutput == AnchorDOWN){
					
					   state = ANCHOR_DWN;
					   break;
				}
				//Go to ANCHOR_UP
				if(receiverOutput == AnchorUP){
					
					   state = ANCHOR_UP;
					   break;
				}
				//Go to EXIT_ANCHOR
				if(receiverOutput == RESET || receiverOutput == NOTHING){
					   state = EXIT_ANCHOR;
					   break;
				}
				//If nothing is detected, continue to stay here
				break;
/***********************************************************************
*							ANCHOR DOWN 							   *	
***********************************************************************/
			case ANCHOR_DWN:
			
					   //lower Anchor
					   digitalWrite(AnchClock, ON);
					   delay(Delay);
					   
					   //Return to Init State
					   state = ANCHOR_INIT;
						
					   //test print
					   printf("Anchor Down\r\n");
				break;

/***********************************************************************
*							ANCHOR UP   							   *	
***********************************************************************/
			case ANCHOR_UP:
			
					   //raise Anchor
					   digitalWrite(AnchCount, ON);
					   
					   //Return to Init State
					   state = ANCHOR_INIT;
					   delay(Delay);
						
					   //test print
					   printf("Anchor Up\r\n");
				break;
				
/***********************************************************************
*						ANCHOR MODE EXIT   							   *	
***********************************************************************/
			case EXIT_ANCHOR:

					   //exit Anchor Mode
					   digitalWrite(AnchorLock, OFF);
					   digitalWrite(AnchClock, OFF);
					   digitalWrite(AnchCount, OFF);
						
					   //test print
					   printf("Exit Anchor Mode\r\n");
					   return;
				break;
		}
	}
	//return;
}
