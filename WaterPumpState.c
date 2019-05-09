/*
 * WaterPumpState.c
 * 
 * Copyright 2018 root <root@raspberrypi>
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


#include <stdio.h>
#include <wiringPi.h>
#include "WLSC.h"
#define WP 7

//states definds
#define INIT 0
#define CHECK 1
#define EMEGENCY 2
#define WPUMPON 3
#define EXITSTATE 4

int main(int argc, char **argv)
{
	if(wiringPiSetup() == -1){
		printf("Setup Failed\r\n");
		return 0;
	}
	//set pin WaterPump 7 to an output pin
	pinMode(WP,OUTPUT);
	
	//declar variables
	int WLCheck = 0;
	int state = INIT;
	
	//main code
	while(1){
		switch(state){
			case INIT:
				state = CHECK;
				break;
			
			case CHECK:
				//Calling water sensor function
				WLCheck = WLSC(); 
				//include battery Below
			
				if(WLCheck == 1){
					state = WPUMPON;
				}else if (WLCheck == 0){
					state = EXITSTATE;
				}else{
					state = EMEGENCY;
				}
				break;
			case EMEGENCY:
				printf("Nothing happened yet \n");
				state = CHECK;
				break;
			case WPUMPON:
				digitalWrite(WP, HIGH);
				state = CHECK;
				break;
			case EXITSTATE:
				printf("water pump turned off \n");
				digitalWrite(WP, LOW);
				return 0;
				break;
		}
	}
}

