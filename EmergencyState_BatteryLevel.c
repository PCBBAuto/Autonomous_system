/*
 * EmergencyState_BatteryLevel.c
 * 
 * Copyright 2019  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

//standard libraries
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
//Michael's motor control to turn motor off
#include "Speed_Control.h"
#include "Anchor_Control.h"

//defines
#define ON 1
#define OFF 0
//#define delay 1000

//Anchor Motor (See PI Pin Diagram)
#define ANCHOR_UP 	30
#define ANCHOR_DOWN 21
#define MotorSwitch	23  //Board Pin23


int main(int argc, char **argv)
{
	
	if(wiringPiSetup() == -1){
		printf("\r\nSetup Failed\r\n");
	//return 0;	//UNCOMMENT FOR INT MAIN HEADER USEAGE
		}
		
	int batteryLevel=11;
	pinMode(MotorSwitch, OUTPUT);
	pinMode(ANCHOR_DOWN, OUTPUT);
	pinMode(ANCHOR_UP, OUTPUT);
	//Initialize Motor to be ON
	digitalWrite(MotorSwitch,ON);
	//Initialize Anchor Motor to be off
	digitalWrite(ANCHOR_DOWN,OFF);
	digitalWrite(ANCHOR_UP,OFF);
	
	if(batteryLevel<12){
			
			//Drops the anchor if battery level is too low
			//AnchorControl(AnchorDown,AnchorUp);
			//AnchorMove(ON,OFF);
			
			//michael's code? if available just add the function here
			//Motor(OFF);
			//digitalWrite(MotorSwitch, ON);
			
			//TURN ON THE ANCHOR MOTOR AND DROP THE ANCHOR 24 clicks(12 feet)
			//AnchorMotor();
			AnchorDOWN(24);
			if(digitalRead(ANCHOR_DOWN)==LOW){
				printf("\nAnchor has reached bottom\n");
			}
			//TURN ANCHOR MOTOR OFF
			//digitalWrite(ANCHOR_DOWN, OFF)
			//TURN THE MOTOR OFF AFTER 1 SECOND
			delay(1000);
			digitalWrite(Mt);
			if(digitalRead(MotorSwitch)==LOW){
				printf("Motor has been turned off\n");
			}
	}
	
	//battery works fine, proceed with operation
	else if(batteryLevel >=12){
		//if(digitalRead(MotorSwitch)==HIGH){
		//delay(1000);
		//Motor();
		printf("Everything works as intended\n");
		//return 0;
	//}
	}
	return 0; 
}

