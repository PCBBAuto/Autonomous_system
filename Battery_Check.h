#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
//#include "ads1115_rpi.c"
#include "ads1115_rpi.h"

#define SCALE_FACTOR 0.2
#define BatteryADC   0
#define LowBattThreshold 11.94
#define FAILED	0
#define PASS	1

int BatteryCheck(void) {

	//declare variables
	float VoltageLevel = 0;
	char *bus = "/dev/i2c-1";
	
	// Initialize I2C
	if(openI2CBus(bus) == -1)
	{
		return EXIT_FAILURE;
	}
	// Sets I2C Address on Pi
	setI2CSlave(0x48);
	
	// Reads voltage value
	VoltageLevel = readVoltage(BatteryADC)/SCALE_FACTOR;
	
	//Compare to threshold
	if (VoltageLevel <= LowBattThreshold){
		return FAILED;
	}
	else{
		return PASS;
	}
}
