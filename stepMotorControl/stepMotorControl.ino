#include <Stepper.h>

#define STEPS 512

Stepper myStepper1(STEPS, 8, 10, 9, 11);
int previous = 0;

void setup()
{
	myStepper.setSpeed(20);
}

void loop()
{
	int val = analogRead(0);
	myStepper.setSpeed(val - previous);
	previous = val;
}
