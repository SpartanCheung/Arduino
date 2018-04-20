//#include "motorControl.h"
#include <Servo.h>

void toTheAng(int goalAng, int index, Servo & myServo, int interval = 15); // function used to control the servo
Servo xMotor;
Servo yMotor;
int currentAng[2] = {0,0}; // document the angle index 0 - x motor, index 1 - y motor
int previousAng[2] = {0,0}; // document the angle of last period
boolean returnOrigin = false;

void setup()
{

	Serial.begin(9600);
	xMotor.attach(7);
	yMotor.attach(5);

}

void loop()
{	
	if (!returnOrigin) {
		toTheAng(114, 0, xMotor, 10);
		toTheAng(118, 1, yMotor, 10);
		returnOrigin = true;
	}
	toTheAng(140, 0, xMotor,12);
	toTheAng(90, 1, yMotor,12);
	toTheAng(100, 0, xMotor, 12);
	toTheAng(130, 1, yMotor, 12);
}


void toTheAng(int goalAng,int index, Servo & myServo, int interval=15) {
	if (currentAng[index] < goalAng) {
		for (int i = currentAng[index]; i <= goalAng; i++) {
			myServo.write(i);
			delay(interval);
			previousAng[index] = currentAng[index];
			currentAng[index] = myServo.read();
		}
	}
	else {
		for (int i = currentAng[index]; i >= goalAng; i--) {
			myServo.write(i);
			delay(interval);
			previousAng[index] = currentAng[index];
			currentAng[index] = myServo.read();
		}
	}
}
