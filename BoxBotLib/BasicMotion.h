/*
	BasicMotion.h - Library definition for basic motion functions
	Code created by Eugene Hamzezadeh, 9 Oct 2017
	Class created by Lynn Sim, 10 Oct 2017
*/

#ifndef BASICMOTION_H
#define BASICMOTION_H

#include "Arduino.h"
#include <Servo.h>

#define LEFT 0	//directions for rotate function
#define RIGHT 1

class BasicMotion
{
	public:
		BasicMotion(int, int, int);
//		void rotate(int, int);
		void calibrate(int);
		void moveBothWheels(int, int);
		void moveLeftWheel(int, int);
		void moveRightWheel(int, int);
    void increaseRotation(int, int);
		void moveLeft(int, int);
		void moveRight(int, int);
		
	private:
		int _spd;
		int _leftWheelPin;
		int _rightWheelPin;
		Servo _leftWheel;
		Servo _rightWheel;
		void _prepareBothWheels();
		void _prepareLeftWheel();
		void _prepareRightWheel();
		void _stopBothWheels();
		void _stopLeftWheel();
		void _stopRightWheel();
};
#endif