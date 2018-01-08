/*
	UltrasonicReader.cpp - Library definition for all ultrasonic reader functions
	Code created by Eugene Hamzezadeh, 14 Oct 2017
	Class created by Lynn Sim, 19 Oct 2017
*/
#ifndef UltrasonicReader_h
#define UltrasonicReader_h

#include <Arduino.h>

class UltrasonicReader
{
  public:
    UltrasonicReader(int, int);
    long readDistance();
    
  private:
    int _triggerPin;
    int _echoPin;
};

#endif