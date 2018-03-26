// 
// SpartanCheung
// touchScreen Version1.0 2018.03.26

#include "touchScreen.h"

touchScreen::touchScreen(int xPosPin, int xNegPin, int yPosPin, int yNegPin, uint8_t xReadPin, uint8_t yReadPin) {
		pins[0] = xPosPin;
		pins[1] = xNegPin;
		pins[2] = yPosPin;
		pins[3] = yNegPin;
		pins[4] = xReadPin;
		pins[5] = yReadPin;
		pinMode(xPosPin, INPUT);
		pinMode(yPosPin, INPUT);
		pinMode(xNegPin, INPUT);
		pinMode(yNegPin, INPUT);
		Serial.println("Touchscreen Initialized£¡");
	}

void touchScreen::calibration() {
	boolean isTouched = false;
	//int waitTime = 0;
	int posXTemp[100];
	int posYTemp[100];
	Serial.println("Calibration Activated");
		for (int j = 0; j < 4; j++) {
			Serial.print("Please press on point");
			Serial.println(j);
			while (!isTouched) {
				isTouched = touchTest();
				Serial.println("Waiting for touch...");
				delay(1000);
				//waitTime++; // waitTime inclined every 1 second
			}
			for (int i = 0; i < 100; i++) {
				capturePosVol();
				posXTemp[i] = posVol[0];
				posYTemp[i] = posVol[1];
			}
			posVolRef[2 * j] = (int)aver(posXTemp, 100);
			posVolRef[2 * j + 1] = (int)aver(posYTemp, 100);
			Serial.print("x reference Voltage:");
			Serial.print(posVolRef[2 * j]);
			Serial.print("   ");
			Serial.print("y reference Voltage:");
			Serial.print(posVolRef[2 * j + 1]);
			Serial.println();
			Serial.println("Point Accepted, Please release the point");
		}
	Serial.println("Touchscreen activation done!");

}

void touchScreen::capturePosVol() {
	pinMode(pins[0], OUTPUT);
	pinMode(pins[1], OUTPUT);
	digitalWrite(pins[0], HIGH);
	digitalWrite(pins[1], LOW);
	delay(5);
	posVol[0] = analogRead(pins[4]);
	delay(5);
	pinMode(pins[0], INPUT);
	pinMode(pins[1], INPUT);

	// ---------------------measurement of y position
	pinMode(pins[2], OUTPUT);
	pinMode(pins[3], OUTPUT);
	digitalWrite(pins[2], HIGH);
	digitalWrite(pins[3], LOW);
	delay(5);
	posVol[1] = analogRead(pins[5]);
	delay(5);
	pinMode(pins[2], INPUT);
	pinMode(pins[3], INPUT);
}

void touchScreen::calculatePos() {
	float location1[2];
	float location2[2];
	location1[0] = posRef[0] + (posVol[0] - posVolRef[0]) * ((posRef[4] - posRef[0]) / (posVolRef[4] - posVolRef[0]));
	location1[1] = posRef[1] + (posVol[1] - posVolRef[1]) * ((posRef[5] - posRef[1]) / (posVolRef[5] - posVolRef[1]));
	location2[0] = posRef[2] + (posVol[0] - posVolRef[2]) * ((posRef[6] - posRef[2]) / (posVolRef[6] - posVolRef[2]));
	location2[1] = posRef[3] + (posVol[1] - posVolRef[3]) * ((posRef[7] - posRef[3]) / (posVolRef[7] - posVolRef[3]));
	position[0] = (location1[0] + location2[0]) / 2;
	position[1] = (location1[1] + location2[1]) / 2;
}


boolean touchScreen::touchTest() {
	
}


float touchScreen::aver(int temp[], int size)
{
	long sum = 0, average;
	for (int i = 0; i < size; i++)
	{
		sum += temp[i];
	}
	return sum / size;
}