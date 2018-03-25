#define xReadPin A4 // xRead read on y direction
#define yReadPin A5 // yRead read on x direction
#define xPosPin 8
#define yPosPin 11
#define xNegPin 10
#define yNegPin 9


int caliRefAnalog[8] = { 73, 98, 965, 90, 965, 915, 75, 903 }; // 1x 1y 2x 2y 3x 3y 4x 4y --analogRead Values
float caliRefReal[8] = { 0.0, 0.0, 337.5, 0.0, 337.5, 270.5, 0.0, 270.5 }; // 1x 1y 2x 2y 3x 3y 4x 4y --Real location
int location[2];
float realLocation[2];

void setup()
{
	pinMode(xPosPin, INPUT);
	pinMode(yPosPin, INPUT);
	pinMode(xNegPin, INPUT);
	pinMode(yNegPin, INPUT);
	
	Serial.begin(9600);
}

void loop()
{
	// --------------------measurement of x position
	pinMode(xPosPin, OUTPUT);
	pinMode(xNegPin, OUTPUT);
	digitalWrite(xPosPin, HIGH);
	digitalWrite(xNegPin, LOW);
	delay(5);
	location[0] = analogRead(xReadPin);
	delay(5);
	pinMode(xPosPin, INPUT);
	pinMode(xNegPin, INPUT);
	
	// ---------------------measurement of y position
	pinMode(yPosPin, OUTPUT);
	pinMode(yNegPin, OUTPUT);
	digitalWrite(yPosPin, HIGH);
	digitalWrite(yNegPin, LOW);
	delay(5);
	location[1] = analogRead(yReadPin);
	delay(5);
	pinMode(yPosPin, INPUT);
	pinMode(yNegPin, INPUT);

	// -----------------------print out the location
	locateTouch(location, realLocation);
	Serial.print("x:");
	Serial.print(realLocation[0]);
	Serial.print("   ");
	Serial.print("y:");
	Serial.print(realLocation[1]);
	Serial.println();
}


 void locateTouch(const int* loc, float * realLoc) {
	float location1[2];
	float location2[2];
	location1[0] = caliRefReal[0] + (loc[0] - caliRefAnalog[0]) * ((caliRefReal[5] - caliRefReal[0]) / (caliRefAnalog[5] - caliRefAnalog[0]));
	location1[1] = caliRefReal[1] + (loc[1] - caliRefAnalog[1]) * ((caliRefReal[6] - caliRefReal[1]) / (caliRefAnalog[6] - caliRefAnalog[1]));
	location2[0] = caliRefReal[2] + (loc[0] - caliRefAnalog[2]) * ((caliRefReal[7] - caliRefReal[2]) / (caliRefAnalog[7] - caliRefAnalog[2]));
	location2[1] = caliRefReal[3] + (loc[1] - caliRefAnalog[3]) * ((caliRefReal[8] - caliRefReal[3]) / (caliRefAnalog[8] - caliRefAnalog[3]));
	realLoc[0] = (location1[0] + location2[0]);
	realLoc[1] = (location1[1] + location2[1]);
}