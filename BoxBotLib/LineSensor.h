/*
	LineSensor.h - Library definition for all line sensor functions
	Code created by Eugene Hamzezadeh, 14 Oct 2017
	Class created by Lynn Sim, 20 Oct 2017
*/
#ifndef LineSensor_h
#define LineSensor_h

#include <Arduino.h>

class LineSensor {
  public:
		LineSensor(int, int, int, int);
		void enableSensor();
		void disableSensor();
		int readLeftSensor();
		int readRightSensor();

  private:
    int _leftSensorPin;
    int _rightSensorPin;
    int _controlPins[2];
};

#endif
