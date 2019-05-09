/*Program name: Anchor_Control.h
* Name: Rafael Ramirez
* Date: 5/2/19
* Description: Control the anchor motor to allow for anchor drop and anchor retrieval
* 				Functions created for team use
*/


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


//MOTOR FUNCTION HANDLE
void Motor();
void AnchorUP(int);
void AnchorDOWN(int);

//Anchor Motor (SEE PI PIN DIAGRAM)
#define ANCHOR_UP 		30
#define ANCHOR_DOWN 	21
#define MotorSwitch		23  //Board Pin23


//******************Code starts here**********************************

static inline void AnchorControl(){
//int main(int argc, char **argv){	//TEST HEADER FOR .C FILES
	
	
	//initialization and setup FOR PI(STANDARD)
	if(wiringPiSetup() == -1){
		printf("\r\nSetup Failed\r\n");
	//return 0;	//UNCOMMENT FOR INT MAIN HEADER USEAGE
		}
		
	//Setup PI for Anchor Motor
	pinMode(ANCHOR_DOWN, OUTPUT);
	pinMode(ANCHOR_UP, OUTPUT);
	pinMode(MotorSwitch, OUTPUT);
	
	//initialization ALL PINS TO BE OFF
	digitalWrite(ANCHOR_DOWN, OFF);
	digitalWrite(ANCHOR_UP, OFF);
	digitalWrite(MotorSwitch, OFF);
	
	//Turn Motor ON
	//AnchorMotor();

}


//		Functions below


//							AnchorUP	
//bring anchor back up until it reaches certain amount of clicks
//for now we say 12 feet so 24 clicks								
	
void AnchorUP(int Click)
{
	int i = Click;
	while(i >= 0){
	//Pull anchor back up
	digitalWrite(ANCHOR_UP, ON);
	delay(250);// 1/4 OF A SECOND PER CLICK
	digitalWrite(ANCHOR_UP, OFF);
	i--;
	}
}

//							Anchor Down
//will keep dropping anchor until it reaches certain amount of clicks 
//for now we say 12 feet so 24 clicks
	
void AnchorDOWN(int Click)
{
	int i = Click;
	while(i >= 0){
	//Drop Anchor
	digitalWrite(ANCHOR_DOWN, ON);
	printf("\n Drop: ");
	printf("%d",i);
	delay(500);// 1/4 OF A SECOND PER CLICK
	digitalWrite(ANCHOR_DOWN, OFF);
	i--;//keep dropping until 24 clicks go by
	}
}


//							AnchorMotor_Control	
//keeps anchor motor on
// CONSULT TEAM FOR FUTURE IMPLEMENTATION							   

/*void AnchorMotor()
{
	digitalWrite(MotorSwitch, ON);
	//keep the motor on for 10 seconds(code testing purposes)
	delay(10000);
	//digitalWrite(MotorSwitch, OFF);

}
*/


