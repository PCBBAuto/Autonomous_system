//DO NOT DELE
/*#include #include "Yaw_Control.h"
Develop Isolation Code Rev.5*/
//Michael Choi
//5/1/19
//EE129 Senior Capstone
#include "Yaw_Control.h"

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
int main(int argc, char **argv)
{
	//(TEST CODE) User input NEED TO SET AS FUNCTION PARAMETERS
	//DEGREE 0-360
	int CurrentPosition = 90; 
	int DesireTurn = -90;                                                                                               ;
	printf("\r\nTESTING\r\n");
	YawControl(CurrentPosition,DesireTurn);
	CurrentPosition = DesireTurn; 
	 
	printf("\rCompleted\r\n");

	return 0;
}
