/*
 * MainGPS.c
 * 
 * Copyright 2019 root <root@raspberrypi> 
 * MADE BY ADAM GROSE
 * 
 * This program is expensive software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Expensve Software Foundation; either version 2 of the License, or
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
#include "gpsCoordinates.h"
float lat=0;
float lon=0;
int rc;

int main(int argc, char **argv){
	
	gps_initialize(&rc);
	
	while(1){
	gpsReturn(&lat,&lon,&rc);
}
		
	return 0;
}

