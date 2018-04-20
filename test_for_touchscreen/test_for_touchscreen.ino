#include "touchScreen.h"


void setup()
{
	Serial.begin(9600);
}

touchScreen myTouchScreen(11, 9, 10, 8, A4, A5); // x+,x-,y+,y-,xR,yR

void loop()
{	
	if (!myTouchScreen.calibrationFlag){
		myTouchScreen.calibration();
	}
	/*while (!myTouchScreen.calibrationFlag) {
		myTouchScreen.calibration();
	}*/
	myTouchScreen.capturePosVol();
	myTouchScreen.calculatePos();
	Serial.print("x:");
	Serial.print(myTouchScreen.position[0]);
	Serial.print("   ");
	Serial.print("y:");
	Serial.print(myTouchScreen.position[1]);
	Serial.println();
}
