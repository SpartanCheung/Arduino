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
	// functions
	void capturePosVol();
	void calculatePos();
	void calibration();
	float aver(int temp[], int size);
	boolean touchTest();

	// constructor	
	touchScreen(int xPosPin, int xNegPin, int yPosPin, int yNegPin, uint8_t xReadPin, uint8_t yReadPin);

private:
	int posVol[2];
	int posVolRef[8] = { 73, 98, 965, 90, 965, 915, 75, 903 };
	float posRef[8] = { 0.0, 0.0, 337.5, 0.0, 337.5, 270.5, 0.0, 270.5 };// 4 reference points
};

#endif