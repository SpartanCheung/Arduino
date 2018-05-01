// 
// SpartanCheung
// touchScreen Version1.0 2018.03.26

#include "touchScreen.h"
#include "stdlib.h"

touchScreen::touchScreen(uint8_t xPosPin, uint8_t xNegPin, uint8_t yPosPin, uint8_t yNegPin, uint8_t xReadPin, uint8_t yReadPin) {
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
	}

void touchScreen::calibration() {
	boolean isTouched = false;
	Serial.println("Background references capturing....");
	captureFilter(200);
	untouchedOutput[0] = posVol[0];
	untouchedOutput[1] = posVol[1];// capture the untouched voltage output
	Serial.println("Background references captured!");
	Serial.print("Background x Voltage: ");
	Serial.print(untouchedOutput[0]);
	Serial.print("  Background y Voltage: ");
	Serial.println(untouchedOutput[0]);
	//int waitTime = 0;
	/*int posXTemp[100];
	int posYTemp[100];*/
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
			isTouched = false;
			captureFilter(100);
			posVolRef[2 * j] = posVol[0];
			posVolRef[2 * j + 1] = posVol[1];
			/*for (int i = 0; i < 100; i++) {
				capturePosVol();
				posXTemp[i] = posVol[0];
				posYTemp[i] = posVol[1];
			}
			posVolRef[2 * j] = (int)aver(posXTemp, 100);
			posVolRef[2 * j + 1] = (int)aver(posYTemp, 100);*/
			Serial.print("x reference Voltage:");
			Serial.print(posVolRef[2 * j]);
			Serial.print("   ");
			Serial.print("y reference Voltage:");
			Serial.print(posVolRef[2 * j + 1]);
			Serial.println();
			Serial.println("Point Accepted, Please release the point!");
		}
	Serial.println("Touchscreen activation done!");
	calibrationFlag = true;
}

void touchScreen::capturePosVol() {
	pinMode(pins[0], OUTPUT);
	pinMode(pins[1], OUTPUT);
	digitalWrite(pins[0], HIGH);
	digitalWrite(pins[1], LOW);
	delay(4);
	posVol[0] = analogRead(pins[4]);
	delay(4);
	pinMode(pins[0], INPUT);
	pinMode(pins[1], INPUT);

	// ---------------------measurement of y position
	pinMode(pins[2], OUTPUT);
	pinMode(pins[3], OUTPUT);
	digitalWrite(pins[2], HIGH);
	digitalWrite(pins[3], LOW);
	delay(4);
	posVol[1] = analogRead(pins[5]);
	delay(4);
	pinMode(pins[2], INPUT);
	pinMode(pins[3], INPUT);
}

void touchScreen::calculatePos() {
	float location1[2];
	float location2[2];
	 // ensure the ball went back in the scope
	//location1[0] = posRef[0] + (posVol[0] - posVolRef[0]) * ((posRef[4] - posRef[0]) / (posVolRef[4] - posVolRef[0]));
	//location1[1] = posRef[1] + (posVol[1] - posVolRef[1]) * ((posRef[5] - posRef[1]) / (posVolRef[5] - posVolRef[1]));
	//location2[0] = posRef[2] + (posVol[0] - posVolRef[2]) * ((posRef[6] - posRef[2]) / (posVolRef[6] - posVolRef[2]));
	//location2[1] = posRef[3] + (posVol[1] - posVolRef[3]) * ((posRef[7] - posRef[3]) / (posVolRef[7] - posVolRef[3]));
	location1[0] = map(posVol[0], posVolRef[0], posVolRef[4], posRef[0], posRef[4]);
	location1[1] = map(posVol[1], posVolRef[1], posVolRef[5], posRef[1], posRef[5]);
	location2[0] = map(posVol[0], posVolRef[2], posVolRef[6], posRef[2], posRef[6]);
	location2[1] = map(posVol[1], posVolRef[3], posVolRef[7], posRef[3], posRef[7]);

	position[0] = (location1[0] + location2[0]) / 2;
	position[1] = (location1[1] + location2[1]) / 2;
	if (position[0] < edges[0]) {
		ballStatus = 1;
	}
	else if (position[0] > edges[1]) {
		ballStatus = 2;
	}
	else if (position[1] < edges[2]) {
		ballStatus = 3;
	}
	else if (position[1] > edges[3]) {
		ballStatus = 4;
	}
	else {
		ballStatus = 0;
	}
}

// 求numOfPoints测量坐标电压值的平均坐标电压
void touchScreen::captureFilter(int numOfPoints) {
	int *posXTemp = new int[numOfPoints];
	int *posYTemp = new int[numOfPoints];
	for (int i = 0; i < numOfPoints; i++) {
		capturePosVol();
		posXTemp[i] = posVol[0];
		posYTemp[i] = posVol[1];
	}
	posVol[0] = (int)aver(posXTemp, numOfPoints);
	posVol[1] = (int)aver(posYTemp, numOfPoints);
	delete[] posXTemp;
	delete[] posYTemp;
}

boolean touchScreen::touchTest() {
	captureFilter(100);
	if (abs(posVol[0] - untouchedOutput[0]) > 200 || abs(posVol[1] - untouchedOutput[1]) > 200) {
		return true;
	}
	else {
		return false;
	}
}


float touchScreen::aver(int temp[], int size)
{
	long sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += temp[i];
	}
	return sum / size;
}