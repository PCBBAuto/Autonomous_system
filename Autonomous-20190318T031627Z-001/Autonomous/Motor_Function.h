

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "Anchor_Function.h"

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
//#define RESET			25
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

static inline void Motor_State(){
	
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
	pinMode(MotorOn, OUTPUT);
	
	//Turn On Motor
	digitalWrite(MotorOn, ON);
	delay(Delay);
	digitalWrite(MotorOn, OFF);
	
	int state = MOTOR_INIT;
	//int BatteryLevel = NOMINAL;
	int receiverOutput = 0;

	
/***********************************************************************
*							Code Starts Here						   *
***********************************************************************/
while(1){	
	switch(state){
/***********************************************************************
*							MOTOR_INIT								   *
***********************************************************************/
			case MOTOR_INIT:
				//Initialize Variables
				receiverOutput = 0;
				
				//Initialize Pins
				digitalWrite(TrollySpeedUp, OFF);
				digitalWrite(TrollySpeedDwn, OFF);
				digitalWrite(ServoRight, OFF);
				digitalWrite(ServoLeft, OFF);
				digitalWrite(Reset, OFF);
				digitalWrite(AnchClock, OFF);
				digitalWrite(AnchLock, OFF);
				digitalWrite(AnchCount, OFF);
		
				
				//Check Inputs
				receiverOutput = fourVal();	
					//CheckPower();
					
				//LightOn
				//lightBeacon(1);
									
				//Go to EXIT_MOTOR
				if(receiverOutput ==  AnchorMode || receiverOutput == RESET){
					   
					   state = EXIT_MOTOR;
					   break;
					   }
				//Go to MOTOR_CLOCK
				if(receiverOutput == MotorSPEEDUP){
					   
					   state = MOTOR_CLOCK;
					   break;
					   }
				
				//Go to MOTOR_COUNTER
				if(receiverOutput == MotorSPEEDDOWN){
					   
					   state = MOTOR_COUNTER;
					   break;
					   }
					   
				//Go to SERVORIGHT
				if(receiverOutput == ServoRIGHT){
					   
					   state = SERVORIGHT;
					   break;
					   }
					   
				//Go to SERVOLEFT
				if(receiverOutput == ServoLEFT){
					   
					   state = SERVOLEFT;
					   break;
					   }
				break;
/***********************************************************************
*							MOTOR_CLOCK								   *	
***********************************************************************/		
			case MOTOR_CLOCK:
				//Increase Motor Speed
				digitalWrite(TrollySpeedUp, ON);
				
				//Return to Init State
				state = MOTOR_INIT;
				delay(Delay);
				
				//test print
				printf("Motor Speed up\r\n");
			
				break;
/***********************************************************************
*							MOTOR_COUNTER							   *
***********************************************************************/			
			case MOTOR_COUNTER:
				//Decrease Motor Speed
				digitalWrite(TrollySpeedDwn, ON);
				
				//Return to Init State
				state = MOTOR_INIT;
				delay(Delay);
				
				//test print
				printf("Motor Speed Down\r\n");
			
				
				break;
/***********************************************************************
*							SERVOLEFT 								   *
***********************************************************************/
			case SERVOLEFT:
				//Move Servo Left
				digitalWrite(ServoLeft, ON);
				
				//Return to Init State
				state = MOTOR_INIT;
				delay(Delay);
				
				//test print
				printf("Servo Left\r\n");
				
				break; 
/***********************************************************************
*							SERVORIGHT							       *
***********************************************************************/
			case SERVORIGHT:
				//Move Servo Right
				digitalWrite(ServoRight, ON);
				
				//Return to Init State
				state = MOTOR_INIT;
				delay(Delay);
				
				//test print
				printf("Servo Right\r\n");
				
				break;
/***********************************************************************
*							EXIT_MOTOR								   *
***********************************************************************/
			case EXIT_MOTOR:
				//Return to TOP_LEVEL_INIT
				state = MOTOR_INIT;			
				//lightBeacon(0);	
				
				//Go to Anchor State
				if(receiverOutput ==  AnchorMode){
					   
					   //Turn Off Motor
					   digitalWrite(MotorOn, ON);
					   delay(Delay);
					   digitalWrite(MotorOn, OFF);
					   printf("Exit To Top because of Anchor State\r\n");					   
					   return;
					   }
				
				//Go to Reset
				else if(receiverOutput == RESET){
						
						//Turn Off Motor
						digitalWrite(MotorOn, ON);
						delay(Delay);
						digitalWrite(MotorOn, OFF);
						printf("Exit To Top because of RESET\r\n");					   
						return;
						
						}
				break;
		
		}
	}
	//return;
}
