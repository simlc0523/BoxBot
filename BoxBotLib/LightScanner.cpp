/*
	LineScanner.cpp - Library implementation for all line scanner functions
	Code created by Eugene Hamzezadeh, 14 Oct 2017
	Class created by Lynn Sim, 20 Oct 2017
*/

#include <Arduino.h>
#include "LightScanner.h"

LightScanner::LightScanner(int leftInput, int rightInput, int headPin, int readStep):
    _leftSensorInput(leftInput), _rightSensorInput(rightInput)
{
	_servoPin = headPin;
	_readResolution = readStep;
	_steps = 180 / _readResolution;
}

void LightScanner::calibrate(int l=0, int r=0, double lc=1.00688, double rc=1.01789) {
	_adjLeft = l;
	_adjRight = r;
	_leftConstant = lc;
	_rightConstant = rc;
}

void LightScanner::initOrientation(BasicMotion motion)
{
	int angle = 0;
  while(angle < 80 or angle > 100)
	{
    _reScanLight(100);
    angle = determineLightAngle();

		//Point light sensor at brightest light
		_head.attach(_servoPin);
		_head.write(angle);
		delay(500);
		_head.detach();
		
		Serial.print("Angle: ");
		Serial.println(angle);
		
    if(angle > 100) {
      motion.increaseRotation(angle, 1);
    }else
    if(angle < 80) {
      motion.increaseRotation(angle, -1);
    }else {
      break;  //BoxBot is pointing very close to light
    }
  }
}

void LightScanner::_reScanLight(int stepDelay)
{
	for(int i = 0; i < 180; i++)
		_lightReadings[i] = 0;
	
	_head.attach(_servoPin);
  _head.write(0);
  delay(700);
	int degree = 0;
	int leftReading = 0;
	int rightReading = 0;
  for(int i = 0; i < _steps; i++)
	{
    degree = i * _readResolution;
    _head.write(degree);
    delay(stepDelay);
    leftReading = analogRead(_leftSensorInput) + _adjLeft;
//    rightReading = analogRead(_rightSensorInput); //+ _adjRight;
    _lightReadings[i] = leftReading; //(leftReading + rightReading) / 2;
		Serial.print("Light[");
		Serial.print(i);
		Serial.print("]: ");
		Serial.println(_lightReadings[i]);
  }
	_head.detach();
}

/*
int* LightScanner::readBroad(int stepDelay) {
	int values[_steps];
	_head.write(0);
	int degree = 0;
	int leftReading = 0;
	int rightReading = 0;
	for(int i = 0; i < _steps; i++) {
		degree = i * _readResolution;
		head.write(degree);
		delay(stepDelay);
		leftReading = analogRead(_leftSensorInput) + _adjLeft;
		rightReading = analogRead(_rightSensorInput) + _adjRight;
		values[i] = (leftReading + rightReading) / 2;
	}
	return values;
}
*/

void LightScanner::readNarrow()
{
	_narrow[0] = _leftConstant * (analogRead(_leftSensorInput) + _adjLeft);
	_narrow[1] = _rightConstant * (analogRead(_rightSensorInput) + _adjRight);
}

int LightScanner::determineLightAngle()
{
	int highestIndex = 0;
	for(int i = 0; i < _steps; i++) {
		if(_lightReadings[i] > _lightReadings[highestIndex]){
			highestIndex = i;
		}
	}
	return highestIndex * _readResolution;
}

void LightScanner::followLight(BasicMotion motion)
{
//	int l = 0;
//	int r = 0;
	double left = 0;
	double right = 0;

	left = (analogRead(_leftSensorInput) + _adjLeft); // * _leftConstant;
	right = (analogRead(_rightSensorInput) + _adjRight); // * _rightConstant;
//	left = _leftConstant * l;
//	right = _rightConstant * r;
	Serial.print("Left:Right light scans - ");
	Serial.print(left);
	Serial.print(" : ");
	Serial.println(right);
	delay(500);
	if(abs(left-right) < 90)
	{
		Serial.println("Moving both wheels, moving forward");
		motion.moveBothWheels(180, 1000);
	}
	if(left > right)
	{
		Serial.println("Moving right wheel, turning left");
		motion.moveRightWheel(180, 300);
	}
		if(left < right)
	{
		Serial.println("Moving left wheel, turning right");
		motion.moveLeftWheel(180, 300);
	}
}
