//this program checks if the magnetometer is connected or not
//to check this if the values of yaw, pitch and roll are read then the program passes. If not, then turns on beacon
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //added to top level
#include <wiringPi.h>
#include "topLevel.h"
#include "IMU.h" //added to top level

//check to make sure it works, changed bool into int

int magError(){
	bool IMU_on = detectIMU();
	if(IMU_on) {
		printf("Magnetometer is connected");
	} else{
		printf("Magnetometer is not connected.Beacon on.");
		return 0;
//turn beacon on 
//pinMode (BEACON_PIN,OUTPUT);
//digitalWrite(BEACON_PIN,HIGH);
	}
}

