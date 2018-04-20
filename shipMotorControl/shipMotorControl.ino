#include <Servo.h>  

#define PIN_SERVO 5
Servo myServo;
Servo myServo2;
int goalPos = 100;
int startPos = 150;

void setup()
{
	Serial.begin(9600);
	myServo.attach(PIN_SERVO);
	myServo2.attach(7);
	
}

void loop()
{
	
	if(startPos < goalPos){
		for (int pos = startPos; pos <= goalPos; pos++) {
			myServo.write(pos);
			delay(15);
			startPos = myServo.read();
			Serial.println(startPos);
		}
	}
	else {
		for (int pos = startPos; pos >= goalPos; pos--) {
			myServo.write(pos);
			delay(15);
			startPos = myServo.read();
			Serial.println(startPos);
		}
		Serial.println("yes");
	}
	
	/*for(int pos = startPos; pos <= goalPos; pos++) {
		myServo.write(pos);
		delay(15);
	}

	for(int pos = goalPos; pos >= startPos; pos--) {
		myServo.write(pos);
		delay(15);
	}*/
}
