#include "touchScreen.h"

touchScreen myTouchScreen(8,11,10,9,A4,A5); // x+,x-,y+,y-,xR,yR

void setup()
{
	Serial.begin(9600);
	myTouchScreen.calibration();
}

void loop()
{
	myTouchScreen.capturePosVol();
	myTouchScreen.calculatePos();
	Serial.print("x:");
	Serial.print(myTouchScreen.position[0]);
	Serial.print("   ");
	Serial.print("y:");
	Serial.print(myTouchScreen.position[1]);
	Serial.println();
}
