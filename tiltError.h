//If the boat is tilted too far, then the beacon is turned on
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wiringPi.h>
#include "topLevel.h"

//define pin
//#define BEACON_PIN 11

#define ROLL_LOW -3.0
#define ROLL_HIGH 103.0
#define PITCH_LOW -58.0
#define PITCH_HIGH 59.0


bool isBoatTilted() {	
	Gyro checkError = magnetometer(); //calling the function
	bool rollInBounds = false;
	bool pitchInBounds = false;
	
	
//if the roll is between range, then boat passes test
	if(gyro.rollValue>= ROLL_LOW && gyro.rollValue<= ROLL_HIGH) {
		rollInBounds = true;
		printf("Roll of Boat passes");
	}else {
//beacon turns on
//goes into emergency phase 
//pinMode (BEACON_PIN,OUTPUT);
//digitalWrite(BEACON_PIN,HIGH);

		printf("Roll of Boat did not pass");
	}
				
//if the pitch is between range, then boat passes test
	if(gyro.pitchValue>= PITCH_LOW && gyro.pitchValue<= PITCH_HIGH) {
		pitchInBounds = true;
		printf("Pitch of boat passes");
	}else {  
//beacon turns on
//pinMode (BEACON_PIN,OUTPUT);
//digitalWrite(BEACON_PIN,HIGH);

		printf("Pitch of Boat did not passes");
	}
	return (rollInBounds && pitchInBounds); 
}

