/*
	LineSensor.cpp - Library implementation for all line sensor functions
	Code created by Eugene Hamzezadeh, 14 Oct 2017
	Class created by Lynn Sim, 20 Oct 2017
*/

#include <Arduino.h>
#include "LineSensor.h"

LineSensor::LineSensor(int leftPin=18, int rightPin=19, int leftLED=3, int rightLED=4):
      _leftSensorPin(leftPin), _rightSensorPin(rightPin)
{
	_controlPins[0] = leftLED;
	_controlPins[1] = rightLED;
	pinMode(_leftSensorPin, INPUT);
	pinMode(_rightSensorPin, INPUT);
	for(int i = 0; i < 2; i++)
		pinMode(_controlPins[i], OUTPUT);
	disableSensor();
};

void LineSensor::enableSensor()
{
	for(int i = 0; i < 2; i++){
			digitalWrite(_controlPins[i], HIGH);
	}
}

void LineSensor::disableSensor()
{
	for(int i = 0; i < 2; i++){
			digitalWrite(_controlPins[i], LOW);
	}
}

int LineSensor::readLeftSensor()
{
	return analogRead(_leftSensorPin);
}

int LineSensor::readRightSensor()
{
	return analogRead(_rightSensorPin);
}
