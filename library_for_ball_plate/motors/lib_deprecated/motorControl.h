// motorControl.h

#ifndef _MOTORCONTROL_h
#define _MOTORCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "Servo.h"
#else
	#include "WProgram.h"
#endif

class motorControl
{
 public:
	motorControl(uint8_t controlPin, uint8_t stdAngle);
	void toTheAng(int goalAng, int interval = 15); // default time interval is 15ms
	void caliAng (int interval = 15);
	Servo myServo;
 private:
	int motorPin = 0;
	int currentAng;
	int previousAng;
	int stdAng;
	boolean isCalibrated = false;
};

#endif

