const int readAPin = A0;
const int outLedPin = 11;
int ePosition;
int brightness;

void setup()
{
	Serial.begin(9600);
	pinMode(readAPin, INPUT);
	pinMode(outLedPin, OUTPUT);
}

void loop()
{
	ePosition = analogRead(readAPin);
	brightness = map(ePosition, 0, 1023, 0, 255);
	analogWrite(outLedPin,brightness);
	if (Serial.available()) {
		String command = Serial.readString();
		if (command == "get brightness") {
			Serial.println(ePosition);
			Serial.println(brightness);
		}
	}
}
