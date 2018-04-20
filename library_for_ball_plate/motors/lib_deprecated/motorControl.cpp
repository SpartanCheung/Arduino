// 
// 
// 

#include "motorControl.h"
#include "Servo.h"

motorControl::motorControl(uint8_t controlPin, uint8_t stdAngle)
{
    currentAng = stdAngle;
    previousAng = 0;
    isCalibrated = false;
    stdAng = stdAngle;

    myServo.attach(controlPin);
}

void motorControl::toTheAng (int goalAng, int interval) {
    int distanceAng = goalAng - currentAng;
    if (isCalibrated) {
        if (distanceAng > 0) {
		for (int i = currentAng; i <= goalAng; i++) {
			myServo.write(i);
			delay(interval);
		    }
	    }
	    else {
            for (int i = currentAng; i >= goalAng; i--) {
                myServo.write(i);
                delay(interval);
		    }
	    }
        previousAng = currentAng;
        currentAng = myServo.read();
    }   
    
}

void motorControl::caliAng (int interval) {
    if (!isCalibrated) {
        Serial.println("Wait till the plate becomes horizontal...");
        int pos = 100;
        for (int pos = 100; pos <= stdAng; pos ++) {
            myServo.write(pos);
            delay(interval);
			previousAng = currentAng;
			currentAng = pos;
			Serial.println(pos);
        }
        Serial.println("Motor initialized!");
		
        isCalibrated =  true;
    }
}





