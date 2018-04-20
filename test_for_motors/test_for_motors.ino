#include <Servo.h>
#include <EEPROM.h>

int currentAng;

Servo xServo;
Servo yServo;


int pos = 90;

void setup()
{
	Serial.begin(9600);
	xServo.attach(7);
	yServo.attach(5);
}

void loop()
{
	currentAng = yServo.read();
	toTheAngle(118, 15);
}

void toTheAngle(int goalAng, int interval) {  // interval is the control delay of every 1 degree, we sugguest use 15ms at least.
	int distanceAng = goalAng - currentAng;
	if (distanceAng > 0) {
		for (int i = currentAng; i <= goalAng; i++) {
			xServo.write(i);
			delay(interval);
		}
	}
	else {
		for (int i = currentAng; i >= goalAng; i--) {
			xServo.write(i);
			delay(interval);
		}
	}
}
