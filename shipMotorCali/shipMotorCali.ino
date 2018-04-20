#include <Servo.h>
Servo xServo;
Servo yServo;

int pos = 0;

void setup()
{
	Serial.begin(9600);
	xServo.attach(6);
	yServo.attach(5);
}

void loop()
{
	int r;
	for (pos = 100; pos <= 120; pos = pos + 1) {
		xServo.write(pos);
		delay(10);
	}

	for (pos = 119; pos >= 100; pos = pos - 1) {
		xServo.write(pos);
		delay(10);
	}
}
	/*xNineGServo.write(130);
	delay(100);*/
