/*
 * GPS.c
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

//headever files to be included
#include <stdio.h>  //standard library 
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <wiringPi.h> //pin defines
#include <lcd.h>     //for lecd functions
#include <gps.h>

//defines
#define D0 4
#define D1 5
#define D2 6
#define D3 0
#define rs 2
#define e  3

//parameters of the lcd screen
#define rows 2
#define cols 16
#define bits 4

int main(int argc, char **argv){
	
	int lcdLat;
	int lcdLong;
	int rc;
	int i=0;
	//int i;
	FILE *fp;
	//struct timeval tv;
	
	struct gps_data_t gps_data;
	fp = fopen("/home/pi/Desktop/Autonomous/gps.txt", "w");
	fprintf(fp, "This is testing for print f \r\n");
	if ((rc = gps_open("localhost", "2947", &gps_data)) == -1){
		printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
		return EXIT_FAILURE;
	}
	gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);
	
	printf("HELLO WORLD \n\r"); 
	if(wiringPiSetup() == -1){
		printf("wiringPi setup error \n\r"); 
	}
	
	//lcd = lcdInit(rows,cols,bits,rs,e,0,0,0,0,D0,D1,D2,D3);
	
	//set lcd pins to output mode
	pinMode(D0,OUTPUT); //data pin 1
	pinMode(D1,OUTPUT); //data pin 2
	pinMode(D2,OUTPUT); //data pin 3
	pinMode(D3,OUTPUT); //data pin 4
	pinMode(rs,OUTPUT); //register select
	pinMode(e,OUTPUT);  //enable
	
	lcdLat = lcdInit(rows,cols,bits,rs,e,D0,D1,D2,D3,0,0,0,0);
	lcdLong = lcdInit(rows,cols,bits,rs,e,D0,D1,D2,D3,0,0,0,0);
	lcdPosition(lcdLat,0,0);
	lcdPosition(lcdLong,0,1);
	//lcdPuts(lcd,"Hello world");
	
	while(1){
		if (gps_waiting (&gps_data, 2000000)){
			if((rc = gps_read(&gps_data)) == -1){
				printf("error occured reading gps data. code: %d, reason: %s\n", rc, gps_errstr(rc));
			}else{
				if((gps_data.status == STATUS_FIX) &&
				   (gps_data.fix.mode == MODE_2D || gps_data.fix.mode == MODE_3D)&&
				   !isnan(gps_data.fix.latitude) &&
				   !isnan(gps_data.fix.longitude)) {
					   printf("latitude: %f, longitude: %f, speed: %f, timestamp: %lf\n", gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.speed, gps_data.fix.time);
					   fprintf(fp, "latitude: %f, longitude: %f, speed: %f, timestamp: %lf\n", gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.speed, gps_data.fix.time);
					   lcdPosition(lcdLat,0,0);
					   lcdPrintf(lcdLat,"lat:%f", gps_data.fix.latitude);
					   lcdPosition(lcdLat,0,1);
					   lcdPrintf(lcdLat,"long:%f", gps_data.fix.longitude);
				   }else{
					   lcdPosition(lcdLat,0,0);
					   fprintf(fp, "-No gps data-\r\n");
					   lcdPuts(lcdLat,"-No gps data-");
				}
			}
		}
		sleep(3);
		lcdClear(lcdLat);	   
		lcdClear(lcdLong);
		i++;
	}
	fclose(fp);
	
	return 0;
}
