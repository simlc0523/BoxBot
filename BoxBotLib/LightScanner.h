/*
	LineScanner.h - Library definition for all line scanner functions
	Code created by Eugene Hamzezadeh, 14 Oct 2017
	Class created by Lynn Sim, 20 Oct 2017
*/
#ifndef LightScanner_h
#define LightScanner_h

#include <Arduino.h>
#include <Servo.h>
#include "BasicMotion.h"

#define LEFT_SENSOR 0
#define RIGHT_SENSOR 1
#define TIME_DEGREE 11 //Aproximate value, part of the calibration ~1000millisecs / 90*

class LightScanner {
  public:
    LightScanner(int, int, int, int);
    void calibrate(int, int, double, double);
		void initOrientation(BasicMotion);
//    int* readBroad(int);
    void readNarrow();
    int determineLightAngle();
		void followLight(BasicMotion);

    
  private:
		void _reScanLight(int);
    int _leftConstant;
    int _rightConstant;
    int _leftSensorInput;		//pin 15 = A2
    int _rightSensorInput;	//pin 16 = A3
    int _readResolution;		//default to 10
    int _servoPin;					//default to 11
    int _adjLeft;
    int _adjRight;
    int _steps;							//= 180/_readResolution
    Servo _head;
		int _lightReadings[180]; //Worst case where light accuracy = 1 degree. Allocates memory that may not be used.
		double _narrow[2];
};
#endif
