/*
 * AnchorFunction.c
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

//defines
#define ON 1
#define OFF 0
//#define delay 1000

//Anchor Motor (See PI Pin Diagram)
#define ANCHOR_UP 30
#define ANCHOR_DOWN 21


int main(int argc, char **argv)
{
	//Standard PI setup
	if(wiringPiSetup() == -1){
		printf("Setup failed\r\n");
		return 0;
	
	pinMode(ANCHOR_DOWN, OUTPUT);
	pinMode(ANCHOR_UP, OUTPUT);
	//initialization ALL PINS TO BE OFF
	digitalWrite(ANCHOR_DOWN, OFF);
	digitalWrite(ANCHOR_UP, OFF);
	
	//drop anchor for 3 seconds then stop
	digitalWrite(AnchorDown,ON);
	if(digitalRead(AnchorDown) == HIGH){
		printf("Works\n");
		//return 0;
	}
	//10 second delay
	delay(10000);
	
	digitalWrite(AnchorDown, OFF);
	if(digitalRead(AnchorDown) == LOW){
		printf("Also works!\n");
		//return 0;
	}
	
	
	
	return 0;
}

