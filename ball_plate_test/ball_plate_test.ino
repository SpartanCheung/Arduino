#include <Servo.h>
#include "touchScreen.h"

Servo xServo;
Servo yServo;
touchScreen myTouchScreen(11, 9, 10, 8, A4, A5); // x+,x-,y+,y-,xR,yR

void setup()
{
	Serial.begin(9600);
	xServo.attach(5);
	yServo.attach(6);
}

void loop()
{
	if (!myTouchScreen.calibrationFlag) {
		myTouchScreen.calibration();
	}
	myTouchScreen.capturePosVol();
	myTouchScreen.calculatePos();
  

}
