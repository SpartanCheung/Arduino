#include "touchScreen.h"
#include <Servo.h>


/*======Declaring the self-defined functions*/
void toTheAng(int goalAng, int index, Servo & myServo, int interval = 12); // function used to control the servo

/*----------------------------------------------------------------------------------------------------
DECLARING OBJECTS AND VARIABLES
------------------------------------------------------------------------------------------------------*/

/*======Declaring the servo objects and relative variables*/
Servo xMotor;
Servo yMotor;
int currentAng[2] = { 0,0 }; // document the angle index 0 - x motor, index 1 - y motor
int previousAng[2] = { 0,0 }; // document the angle of last period
boolean returnOrigin = false;

/*======Declaring the touchScreen object*/
touchScreen myTouchScreen(11, 9, 10, 8, A4, A5); // x+, x-, y+, y-, xR, yR

/*======Declaring the pid relative variables */
//double kp[2] = { 0.5,2.5};
double kp[2] = { 0.7,1.2 }; //v2
double ki[2] = { 1.0,1.0 }; //v2
//double kd[2] = { 0.0975, 0.25 };
double kd[2] = { 0.110, 0.25 }; //v2
double ka[2] = { 0.00,0.00 }; //v2
double error_current[2]		= {	0.0,0.0	};	// now(k)-goal(k)		{x,y}
double error_last[2]		= { 0.0,0.0 };	
double error_last_last[2]	= { 0.0,0.0 };	
double deltaErr_last[2]		= { 0.0,0.0 };  // e(k-1)-e(k-2)	~
double deltaErr_last_last[2] = { 0.0,0.0 }; // e(k-2)-e(k-3)	~
//double pTerm[2] = { 0,0 };
double iTerm[2] = { 0,0 };
//double dTerm[2] = { 0,0 };
//double aTerm[2] = { 0,0 };
double pidOutput[2] = { 0,0 };
int outPut[2] = {110,110};
int Goal[2] = { 160,100 }; 
int compPeriod = 9;		// ms
boolean convertFlag = false;
int time = 0;
int timeDis = 0;




/*-----------------------------------------------------------------------------------------------------
main Arduino Function*/

void setup()
{
	Serial.begin(9600);
	xMotor.attach(7);
	yMotor.attach(5);
}

void loop()
{
	if (myTouchScreen.calibrationFlag) {
		myTouchScreen.calibration();
	}
	if (!convertFlag) {
		convPID();
	}
	if (!returnOrigin) {
		toTheAng(112, 0, xMotor, 10);
		toTheAng(118, 1, yMotor, 10);
		returnOrigin = true;
	} else {
			timeDis = millis() - time;
			time = millis();
			if (timeDis >= compPeriod) {
				myTouchScreen.capturePosVol();
				myTouchScreen.calculatePos();
				errorCal();
				for (int i = 0; i < 2; i++) {
					pidCal(i);
				}
				outPutTrans();
				
				toTheAng(outPut[0], 0, xMotor,8);
				toTheAng(outPut[1], 1, yMotor,8);
			}	
	}
}


/*----------------------------------------------------------------------------------------------------------------
 Function:toTheAngle
		to drive the motor to the goal angle
 Parameters: 
	goalAng		- the wanted angle of Servo arm
	index		- 0~xServo , 1~yServo
	myServo		- the reference to the Servo object
	interval	- the interval time, default value is 12ms, short interval means faster movement 
				  but also may cause servo fall behind software
------------------------------------------------------------------------------------------------------------------*/
void toTheAng(int goalAng, int index, Servo & myServo, int interval = 12) {
	if (currentAng[index] < goalAng) {
		for (int i = currentAng[index]; i <= goalAng; i++) {
			myServo.write(i);
			delay(interval);
			previousAng[index] = currentAng[index];
			currentAng[index] = myServo.read();
		}
	}
	else {
		for (int i = currentAng[index]; i >= goalAng; i--) {
			myServo.write(i);
			delay(interval);
			previousAng[index] = currentAng[index];
			currentAng[index] = myServo.read();
		}
	}
	//Serial.println("done");
}


/*----------------------------------------------------------------------------------------------------------------
Function:errorCal 
		to calculate the error value (pos)
Parameters: None
------------------------------------------------------------------------------------------------------------------*/
void errorCal() {
	for (int i = 0; i < 2; i++) {
		error_last_last[i] = error_last[i];
		error_last[i] = error_current[i];
		error_current[i] = myTouchScreen.position[i] - Goal[i];	
	}
	Serial.println("Calculation done");
	Serial.print(error_current[0]);
	Serial.print("   ");
	Serial.println(error_current[1]);
}

/*----------------------------------------------------------------------------------------------------------------
Function:outPutTrans
		to transform the error output to the angle output
Parameters: None
------------------------------------------------------------------------------------------------------------------*/
void outPutTrans() {
	double xPlateAng = map(pidOutput[0], -90, 90, 5, -5);  // Transfer Function (Waited to be revised)
	double yPlateAng = map(pidOutput[1], -90, 90, 5, -5);

	xPlateAng = plateThresh(xPlateAng,5);
	yPlateAng = plateThresh(yPlateAng,10);

	switch (myTouchScreen.ballStatus)  // if the ball is still in the scope?
	{
	case 0:
		break;
	case 1:
		xPlateAng = 10;
		break;
	case 2:
		xPlateAng = -10;
		break;
	case 3:
		yPlateAng = 10;
		break;
	case 4:
		yPlateAng = -10;
		break;
	default:
		break;
	}

	outPut[0] = (int)	 2.0184 * xPlateAng + 106.28;
	outPut[1] = (int)	-1.9703 * yPlateAng + 113.36; // calibarated

	if (myTouchScreen.ballStatus) {
		toTheAng(outPut[0], 0, xMotor, 15);
		toTheAng(outPut[1], 1, yMotor, 15);
		delay(10);
	}
	//Serial.println(outPut[0]);
	//Serial.println(outPut[1]);
}


/*----------------------------------------------------------------------------------------------------------------
Function:pidCal
		to calculate the pid output using errors
Parameters: None
------------------------------------------------------------------------------------------------------------------*/
void pidCal(int index) {
	int i = index;
	double pTerm = kp[i] * error_current[i];
	iTerm[i] += (ki[i] * error_current[i]);
	double deltaErr = error_current[i] - error_last[i];
	double dTerm = kd[i] * (((5 * deltaErr) + (3 * deltaErr_last[i]) + (1 * deltaErr_last_last[i])) / 10.0);
	double aTerm = ka[i] * (((deltaErr - deltaErr_last[i]) + (deltaErr_last[i] - deltaErr_last_last[i])) / 2.0);
	pidOutput[i] = pTerm + iTerm[i] + dTerm + aTerm;
	deltaErr_last_last[i] = deltaErr_last[i];
	deltaErr_last[i] = deltaErr;
}


/*----------------------------------------------------------------------------------------------------------------
Function:plateThresh
	the angle of plate should be limited to - 5 to 5 degrees.
Parameters: None
------------------------------------------------------------------------------------------------------------------*/
double plateThresh(double Ang, double thresh) {
	if (Ang > 0 && Ang > thresh) {
		return thresh;
	} 
	if (Ang < 0 && Ang < -thresh) {
		return -thresh;
	}
	return Ang;
}

/*----------------------------------------------------------------------------------------------------------------
Function:convPID
		convert the user-given pid parameters into real coefficient with given control period time.
Parameters: None
convert formula:
1. kp = kp;
2. ki = ki * (compT / 1000);
3. kd = kd / (compT / 1000);
4. ka = ka * (compT / 1000);
------------------------------------------------------------------------------------------------------------------*/
void convPID() {
	for (int i = 0; i < 2; i++) {
		double factor = double(compPeriod) / 1000;
		ki[i] = ki[i] * factor;
		kd[i] = kd[i] / factor;
		ka[i] = ka[i] * factor;
	}
	convertFlag = true;
}


