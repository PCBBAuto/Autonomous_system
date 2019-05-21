#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h> 
#include <wiringPi.h>
#include "ads1115_rpi.h"
#include "header.h"

//Water Defines
#define WLSPIN 13

//Humidity Defines
#define MAXTIMINGS	85
#define DHTPIN		7 //Dan has a question about this?
#define PASS 1
#define FAIL 0
#define HumidityThresh 90
#define HumidityError 0
#define NoError 69

// Magnetometer Connection Defines
#define FAILED	0
#define PASS	1

//Tile Error Defines
#define ROLL_LOW -105
#define ROLL_HIGH 4
#define PITCH_LOW -56.0
#define PITCH_HIGH 55.0

//Batter Check Deifines
#define SCALE_FACTOR 0.2
#define BatteryADC   0
#define LowBattThreshold 11.94
#define FAILED	0
#define PASS	1

/*******************************************************************
							Battery Sensor
*******************************************************************/
int CheckBattery() {

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


/*******************************************************************
							Magnetometer Connction
\*******************************************************************/
int magError(){
	int IMU_on = detectIMU();
	if(IMU_on) {
		printf("Magnetometer is connected\r\n");
		return PASS;
	} else{
		printf("Magnetometer is not connected. Beacon on.\r\n");
		return FAILED;
	}
}

/*******************************************************************
							Tilt Sensor
*******************************************************************/

bool isBoatTilted() {	
	Gyro checkGyro = magnetometer(); 
	bool rollInBounds = false;
	bool pitchInBounds = false;
	
	//if the roll is between range, then boat passes test
	if(checkGyro.rollValue>= ROLL_LOW && checkGyro.rollValue<= ROLL_HIGH) {
		rollInBounds = true;
		printf("Roll of Boat passes\r\n");
	}else {
//beacon turns on
//goes into emergency phase 
//pinMode (BEACON_PIN,OUTPUT);
//digitalWrite(BEACON_PIN,HIGH);

		printf("Roll of Boat did not pass\r\n");
	}
				
//if the pitch is between range, then boat passes test
	if(checkGyro.pitchValue>= PITCH_LOW && checkGyro.pitchValue<= PITCH_HIGH) {
		pitchInBounds = true;
		printf("Pitch of boat passes\r\n");
	}else {  
//beacon turns on
//pinMode (BEACON_PIN,OUTPUT);
//digitalWrite(BEACON_PIN,HIGH);

		printf("Pitch of Boat did not passes\r\n");
	}
	return (rollInBounds && pitchInBounds); 
}


/*******************************************************************
							Water Level Sensor
*******************************************************************/
int WLSC()
{
	//Initialize Pins
	pinMode(WLSPIN, INPUT);
	
	//Code
	if(wiringPiSetup() == -1){
		printf("Setup Failed\r\n");
		return 0;
	}

	if(digitalRead(WLSPIN) == HIGH){
		return FAILED;
	}
	
	return PASS;
}


/*******************************************************************
							Humidity Sensor
*******************************************************************/
int humidity( void )
{
	//Setup WiringPi
	if ( wiringPiSetup() == -1 )
		exit( 1 );

	//Declare Variables
	int dht11_dat[5] = { 0, 0, 0, 0, 0 };
	int dataCheck = 0; 
	
	/*******************************************************************
							Humidity Sensor Code Start
	*******************************************************************/
	while(dataCheck != PASS){
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	float	f; /* fahrenheit */

	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

	/* pull pin down for 18 milliseconds */
	pinMode( DHTPIN, OUTPUT );
	digitalWrite( DHTPIN, LOW );
	delay( 18 );
	
	/* then pull it up for 40 microseconds */
	digitalWrite( DHTPIN, HIGH );
	delayMicroseconds( 40 );
	
	/* prepare to read the pin */
	pinMode( DHTPIN, INPUT );

	/* detect change and read data */
	for ( i = 0; i < MAXTIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( DHTPIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHTPIN );

		if ( counter == 255 )
			break;

		/* ignore first 3 transitions */
		if ( (i >= 4) && (i % 2 == 0) )
		{
			/* shove each bit into the storage bytes */
			dht11_dat[j / 8] <<= 1;
			if ( counter > 50 )
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}

	/*
	 * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	 * print it out if data is good
	 */
	if ( (j >= 40) &&
	     (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
	{
		f = dht11_dat[2] * 9. / 5. + 32;
		printf( "Humidity = %d.%d %% Temperature = %d.%d *C (%.1f *F)\n",
			dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f );
		dataCheck = PASS;	
	}else  {
		//printf( "Invalid Data\n" );
		dataCheck = FAIL;
	}
}
	/*******************************************************************
							Humidity Sensor Code End
	*******************************************************************/
	
	//Check if Humidity is Within Tolerance
	if(dht11_dat[0] >= HumidityThresh){
		
		return(HumidityError);
		}else 
			return(NoError);
		
}
