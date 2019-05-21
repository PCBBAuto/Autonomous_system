/*
 * gpsCoordinates file will hold the function that will return the 
 * latitude and longitude values to be used for navigation
 * 
 */
 
#include <stdio.h>  //standard library 
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <gps.h>


struct gps_data_t gps;

struct gpsData{
	float latv;
	float longv;
}gpsDataVal;

static inline void gps_initialize(int *rc){
	
	if ((*rc = gps_open("localhost", "2947", &gps)) == -1){
		printf("code: %d, reason: %s\n", *rc, gps_errstr(*rc));
	}
	
	gps_stream(&gps, WATCH_ENABLE | WATCH_JSON, NULL);
	
	
	
	
}

static inline void gps_getCoordinates(int *rc){
		if (gps_waiting (&gps, 1000000)){
			if((*rc = gps_read(&gps)) == -1){
				printf("error occured reading gps data.\r\n");
			}else{
				if((gps.status == STATUS_FIX) &&
				   (gps.fix.mode == MODE_2D || gps.fix.mode == MODE_3D)&&
				   !isnan(gps.fix.latitude) &&
				   !isnan(gps.fix.longitude)) {
					   printf("latitude: %f, longitude: %f, speed: %f, timestamp: %lf\n", gps.fix.latitude, gps.fix.longitude, gps.fix.speed, gps.fix.time);
					   gpsDataVal.latv=gps.fix.latitude;
					   gpsDataVal.longv=gps.fix.longitude;
				   }else{
					   printf("-No gps data-\r\n");
					   gpsDataVal.latv=0;
					   gpsDataVal.longv=0;
				}
			}
		}
	
}

static inline void gpsReturn(float *a,float *b, int *rc){

	gps_getCoordinates(rc);
	*a=gpsDataVal.latv;
	*b=gpsDataVal.longv;
}



