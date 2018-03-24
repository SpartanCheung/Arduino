#include <Servo.h>

Servo nineGServo;

int pos = 0;

void setup()
{
	Serial.begin(9600);
	nineGServo.attach(11);
}

void loop()
{
	pos = random(0, 180);
	nineGServo.write(pos);
	Serial.println(pos);
	delay(100);
}
