/*
 * Navigation_Prototype.c
 * 
 * Copyright 2019 root <root@SelinasRaspberryPi>
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
#include <math.h>
#include "header.h"
#include "gpsCoordinates.h"

//Defines
#define RadToDeg  180/M_PI
#define DegToRad  M_PI/180

//Declare Function Prototypes
double CorrectBearCalc(double LAT1, double LAT2, double LONG1, double LONG2); //This function returns the Correct Bearing in DEGREES
double CompareBearings(double CorrectBear, double CurrentBear);


/***********************************************************************
							Main
***********************************************************************/
int main(int argc, char **argv)
{
	if (wiringPiSetup() == -1) {
			printf("Setup Failed\r\n");
			return 0;
			
	}
	
	//Declare Variables	
	double bearing = 0;
	
	//Call Function
	bearing  = CorrectBearCalc(39.099912, 38.627089, -94.581213, -90.200203);
	CompareBearings(bearing, getHeading());
	
	return 0;
}














/***********************************************************************
							Calculate Bearing
***********************************************************************/
double CorrectBearCalc(double LAT1, double LAT2, double LONG1, double LONG2){
	
	//Declare Variables
	double X = 0;
	double Y = 0;
	double CorrectBearing = 0;
	
	LAT1 = LAT1 * DegToRad;
	LAT2 = LAT2 * DegToRad;
	LONG1 = LONG1 * DegToRad;
	LONG2 = LONG2 * DegToRad;
	
	//Code Begins here 
	X = cos(LAT2) * sin(LONG2 - LONG1);
	Y = cos(LAT1) * sin(LAT2) - sin(LAT1) * cos(LAT2) * cos(LONG2 - LONG1);
	CorrectBearing = atan2(X, Y);
	CorrectBearing = CorrectBearing * RadToDeg;
	
	
	printf("X = %f Degrees \n", X);
	printf("Y = %f Degrees \n", Y);
	
	return CorrectBearing;
	
	}

/***********************************************************************
							Compare Bearings
***********************************************************************/
double CompareBearings(double CorrectBear, double CurrentBear){
	
	//Declare Variables
	double CourseCorrection = 0;
	
	//Code Begins here 
	CourseCorrection = CorrectBear - CurrentBear;
	printf("Correct Bearing = %f Degrees \n", CorrectBear);
	printf("Current Bearing = %f Degrees \n", CurrentBear);
	printf("Course Correction = %f Degrees \n", CourseCorrection);
	
	return CourseCorrection;
	
	}
