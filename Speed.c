//DO NOT DELE
/*#include "Speed_Control.h"
Develop Isolation Code Rev.1*/
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
//Misc Defines
//#define OFF 0
//#define ON 1
//#define Delay 1250

#include "Speed_Control.h"
int main(int argc, char **argv)
{
	//(TEST CODE) User input NEED TO SET AS FUNCTION PARAMETERS
	//MAX SPEED:5 NEUTRAL:0
	int CurrentSpeed = 0;
	int DesSpeed = 5;
 
	SpeedControl(CurrentSpeed,DesSpeed);

	return 0;
}
