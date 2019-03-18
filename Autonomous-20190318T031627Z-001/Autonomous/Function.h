

#include <softPwm.h>
#include <stdio.h>
#include <wiringPi.h>

//define pins
#define PIN11 26 //Ch1 Pin32           
#define PIN3  23 //Ch5 Pin33
#define PIN5  24 //Ch3 Pin35
#define PIN7  27 //Ch6 Pin36
#define BEACON 25//pin7


//define action
#define NOTHING			20
#define MotorSPEEDUP	21
#define MotorSPEEDDOWN	22
#define ServoLEFT		23
#define ServoRIGHT		24
#define RESET			25
#define AnchorMode		26
#define AnchorUP		27
#define AnchorDOWN		28

static inline void initializePins(){
	pinMode(PIN11, INPUT);
	pinMode(PIN3, INPUT);
	pinMode(PIN5, INPUT);
	pinMode(PIN7, INPUT);
	pinMode(BEACON, OUTPUT);
}

static inline void lightBeacon(int value){
	digitalWrite(BEACON, value);
	printf("light on @ %d\r\n", value);
}

static inline int pwm(int pinNum){
	//variables
	int initTime = 0;
	int endTime = 0;
	int timeDur = 0;
	//stalls till next cycle
	while (digitalRead(pinNum) != 1) {;}
	initTime = micros();
	//stalls till cycle ends
	while (digitalRead(pinNum) == 1) {;}
	endTime = micros();
	timeDur = endTime - initTime;
	//round time duration to 1500 from 1250 and 1750
	if (1250 < timeDur && timeDur< 1750){
		timeDur = 1500;
	}
	//round time duration to 1000 from 750 and 1250
	if (750 < timeDur && timeDur <= 1250){
		timeDur = 1000;
	}
	//round time duration to 500 under 750
	if (timeDur <= 750){
		timeDur = 500;
	}
	//round time to 2000 over 1750
	if (1750 <= timeDur){
		timeDur = 2000;
	}
	return (timeDur);
}

static inline int fourVal(){
	//Initialize Variables
	int CH1, CH3, CH5, CH6;
	
	//Initial state to nothing
	CH1 = 1.5;
	CH3 = .5;
	CH5 = 1.5;
	CH6 = .5;
	
	//Read value
	CH1 = pwm(PIN11); 
	CH5 = pwm(PIN3); 
	CH3 = pwm(PIN5); 
	CH6 = pwm(PIN7);
	
	//Return Nothing 
	if(CH1==1500 && CH5==500 && CH3==1500 && CH6==500){return NOTHING;}
	
	//Return MotorSPEEDUP 
	if(CH1==1500 && CH5==500 && CH3==2000 && CH6==2000){return MotorSPEEDUP;}
	
	//Return MotorSPEEDDOWN 
	if(CH1==1500 && CH5==500 && CH3==1000 && CH6==1000){return MotorSPEEDDOWN;}
	
	//Return ServoLEFT 
	if(CH1==1000 && CH5==1000 && CH3==1500 && CH6==500){return ServoLEFT;}
	
	//Return ServoRIGHT 
	if(CH1==2000 && CH5==2000 && CH3==1500 && CH6==500){return ServoRIGHT;}
	
	//Return RESET 
	if(CH1==1500 && CH5==1000 && CH3==500 && CH6==500){return RESET;}
	
	//Return RESET 
	if(CH1==500 && CH5==1000 && CH3==500 && CH6==1000){return RESET;}
	
	//AnchorMode
	if(CH1==500 && CH5==500 && CH3==1500 && CH6==1000){return AnchorMode;}
	
	//Return AnchorUP
	if(CH1==500 && CH5==500 && CH3==2000 && CH6==1000){return AnchorUP;}
	
	//Return AnchorDOWN
	if(CH1==500 && CH5==500 && CH3==1000 && CH6==1000){return AnchorDOWN;}
	
	return 0;
}
