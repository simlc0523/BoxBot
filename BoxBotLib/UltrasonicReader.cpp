/*
	UltrasonicReader.cpp - Library implementation for all ultrasonic reader functions
	Code created by Eugene Hamzezadeh, 14 Oct 2017
	Class created by Lynn Sim, 16 Oct 2017
*/
#include "Arduino.h"
#include "UltrasonicReader.h"

UltrasonicReader::UltrasonicReader(int tPin=6, int ePin=7):
		_triggerPin(tPin), _echoPin(ePin)
{
  pinMode(_triggerPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

long UltrasonicReader::readDistance()
{
  digitalWrite(_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_triggerPin, LOW);
  long duration = pulseIn(_echoPin, HIGH);
  return duration*0.034/2;
}
