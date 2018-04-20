// 
// 
// 

#include "motorControl.h"
#include "Servo.h"

motorControl::motorControl(uint8_t controlPin, uint8_t stdAngle)
{
    currentAng = 0;
    previousAng = 0;
    isCalibrated = false;
    stdAng = stdAngle;
    myServo.attach(controlPin);
	motorPin = controlPin;
}

//void motorControl::caliAng(int interval) {
//	Serial.println("Wait till the plate becomes horizontal...");
//	toTheAng(stdAng, 15);
//	Serial.println("Motor initialized!");
//	Serial.println(isCalibrated);
//	isCalibrated = true;
//	Serial.println(isCalibrated);
//	Serial.print("I'm controled by pin");
//	Serial.println(motorPin);
//}

void motorControl::toTheAng (int goalAng, int interval) {
    //int distanceAng = goalAng - currentAng;
	Serial.print(stdAng);
	Serial.print("     ");
	Serial.print("     ");
	Serial.println(currentAng);
    if (goalAng > currentAng) {
		for (int i = currentAng; i <= goalAng; i++) {
			myServo.write(i);
			delay(interval);
			previousAng = currentAng;
			currentAng = myServo.read();
			Serial.println(i);
		    }
	}
	else {
		for (int i = currentAng; i >= goalAng; i--) {
			myServo.write(i);
			delay(interval);
			previousAng = currentAng;
			currentAng = myServo.read();
			Serial.println(i);
		}
	}
    //previousAng = currentAng;
    //currentAng = myServo.read();   
}







