/**
 * Arduino Ghost Detector
 * v0.2
 *
 * by DomesticHacks
 * http://www.domestichacks.info/
 * http://www.youtube.com/DomesticHacks
 *
 * License:
 * Creative Commons: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */
 
#define PIN_SENSOR 5
#define PIN_SPKR 9
#define PIN_INSTR 10
#define FILTER_MEASURES 30

uint16_t sensorVal;
uint8_t displayVal;
uint16_t toneVal;

uint8_t measurCount;
uint16_t measurSum;

void setup()
{
	pinMode(PIN_INSTR, OUTPUT);
	pinMode(PIN_SPKR, OUTPUT);
	pinMode(PIN_SENSOR, INPUT);
}

void loop()
{
	measurCount = 0;
	measurSum = 0;
	do {
		sensorVal = analogRead(PIN_SENSOR);
		
		measurSum = measurSum + sensorVal;
		measurCount++;
	} while (measurCount < FILTER_MEASURES);
	
	sensorVal = measurSum / measurCount;
	sensorVal = constrain(sensorVal, 1, 100);
	
	displayVal = map(sensorVal, 1, 100, 1, 255);
	analogWrite(PIN_INSTR, displayVal);
	
	toneVal = map(sensorVal, 1, 100, 100, 1000);
	if (sensorVal > 25) {
		tone(PIN_SPKR, toneVal, 80);
	}
}
