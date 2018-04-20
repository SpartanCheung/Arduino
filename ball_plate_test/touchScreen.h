// touchScreen.h

#ifndef _TOUCHSCREEN_h
#define _TOUCHSCREEN_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class touchScreen {
public:
	// memebers
	uint8_t pins[6]; // pins for touchscreen
	float position[2];
	boolean calibrationFlag = false;

	// functions
	void capturePosVol();
	void calculatePos();
	void calibration();
	float aver(int temp[], int size);
	boolean touchTest();
	void captureFilter(int numOfPoints);

	// constructor	
	touchScreen(uint8_t xPosPin, uint8_t xNegPin, uint8_t yPosPin, uint8_t yNegPin, uint8_t xReadPin, uint8_t yReadPin);

private:
	int untouchedOutput[2]; 
	int posVol[2];
	int posVolRef[8] = { 73, 98, 965, 90, 965, 915, 75, 903 };
	float posRef[8] = { 0.0, 0.0, 337.5, 0.0, 337.5, 270.5, 0.0, 270.5 };// 4 reference points
};

#endif