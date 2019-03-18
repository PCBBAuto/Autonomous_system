/*Pi Functions
 * 
void   pinMode(int pin, int mode);
int    digitalRead(int pin);
void   digitalWrite(int pin, int value);
void   pwmWrite(int pin, int value);
int    analogRead(int pin);
void   analogWrite(int pin, int value);
int  softPwmCreate (int pin, int value, int range); Range must be 100, value is 0-100
void softPwmWrite(int pin, int value); value is 0-100
void softPwmStop(int pin);

*/

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "Motor_Function.h"

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
#define AnchClock 10 //Board Pin24
#define AnchCount 11 //Board Pin26
#define AnchLock  7 //Board Pin7

//Trolly Motor
#define TrollySpeedUp  13 //Board Pin21
#define TrollySpeedDwn 14 //Board Pin23
#define ServoRight     1  //Board Pin12
#define ServoLeft  	   21 //Board Pin29
#define Reset  		   29 //Board Pin40

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
//#define PIN40 25

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


int main(int argc, char **argv){
	
	//initialization and setup
	if(wiringPiSetup() == -1){
		printf("Setup Failed\r\n");
		return 0;
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
	//pinMode(PIN40, OUTPUT);
	
	//declare variables
	int state = TOP_LEVEL_INIT;
	int MoveServoRight = NO;
	int MoveServoLeft = NO;
	int SpeedUp = NO;
	int SpeedDwn = NO;
	int MotorOnOff = OFF;
	int MotorReset = NO;
	int AnchorLock = OFF;
	int BatteryLevel = NOMINAL;
	int AnchorSwitch = OFF;
	int MrResetti = OFF;
	
	//int BatteryLevel = NOMINAL;
	int receiverOutput = 0;
	//digitalWrite(PIN40, 1);
	
/***********************************************************************
					Code Starts Here
***********************************************************************/
while(1){
	switch(state){
			case TOP_LEVEL_INIT:
			printf("Top Level Init State\r\n");
			//Initialize Variables
			receiverOutput = 0;
			
			//Check Inputs
			receiverOutput = fourVal();
					//CheckPower();
			
			//Go to MOTOR_MOVE
			if(receiverOutput == NOTHING){state = MOTOR_MOVE; 		break;}
			
			//Go to ANCHOR_STATE
			if(receiverOutput == AnchorMode){state = ANCHOR_STATE;	break;}
			
				break;
			
			case NOM_POWER_INIT:
			
				break;
			
			case MOTOR_MOVE:
			printf("Enter Motor Function\r\n");
			Motor_State();
			
			//Go to init
			state = TOP_LEVEL_INIT;		
				break;
			
			case ANCHOR_STATE:
			printf("Enter Anchor Function\r\n");
			Anchor_State();
			
			//Go to init
			state = TOP_LEVEL_INIT;
				break; 
				
			case LOW_POWER_INIT:
			
				break;
				
			case EXIT_LOW_POWER:
			
				break;
		
		}
	}
	return 0;
}

