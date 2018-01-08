/*
	BasicMotion.cpp - Library implementation for all basic motion functions
	Code created by Eugene Hamzezadeh, 9 Oct 2017
	Class created by Lynn Sim, 10 Oct 2017
*/
#include "Arduino.h"
#include <Servo.h>
#include "BasicMotion.h"

BasicMotion::BasicMotion(int rS=0, int lWP=10, int rWP=9):
		_spd(rS), _leftWheelPin(lWP), _rightWheelPin(rWP)
{
}

/*void BasicMotion::rotate(int time, int dir) {	//dir: 0=left, 1=right
	_leftWheel.attach(_leftWheelPin);
	_rightWheel.attach(_rightWheelPin);

	if(dir == LEFT)
	{
		_leftWheel.write(_rotateSpeed);
		_rightWheel.write(_rotateSpeed);
	}
	else
	{
		_leftWheel.write(180 - _rotateSpeed);
		_rightWheel.write(180 - _rotateSpeed);
	}
		
  delay(time);
	_leftWheel.detach();
	_rightWheel.detach();
}
*/
	
void BasicMotion::calibrate(int speed)
{
	_spd = speed;
	Serial.print("Set speed");
	Serial.println(_spd);
}
	
void BasicMotion::moveBothWheels(int speed, int ms) {
	_prepareBothWheels();
  _leftWheel.write(4+speed);
  _rightWheel.write(184-speed);
  delay(ms);
	_stopBothWheels();
}

void BasicMotion::moveLeftWheel(int speed, int ms) {
	_prepareLeftWheel();
  _leftWheel.write(speed);
  delay(ms);
	_stopLeftWheel();
}

void BasicMotion::moveRightWheel(int speed, int ms) {
	_prepareRightWheel();
  _rightWheel.write(4+speed);
  delay(ms);
  _stopRightWheel();
}

void BasicMotion::moveLeft(int speed, int ms) {
	_stopLeftWheel();
	_prepareRightWheel();
  _rightWheel.write(184-speed);
  delay(ms);
  _stopRightWheel();
}

void BasicMotion::moveRight(int speed, int ms) {
	_stopRightWheel();
	_prepareLeftWheel();
  _leftWheel.write(184-speed);
  delay(ms);
  _stopLeftWheel();
}

void BasicMotion::increaseRotation(int angle, int direction) {
//	int servoSpeed = 180;
	int time = round(abs(angle * _spd));
	Serial.print("Angle:Time - ");
	Serial.print(angle);
	Serial.print(" : ");
	Serial.println(time);
	delay(500);
	_prepareBothWheels();
	if(direction < 0) {
		_leftWheel.write(0);
		_rightWheel.write(0);
	}
	if(direction > 0) {
		_leftWheel.write(180);
		_rightWheel.write(180);
	}
	//delay(time);
	//_stopBothWheels();
}

void BasicMotion::_prepareBothWheels() {
	_prepareLeftWheel();
	_prepareRightWheel();
}

void BasicMotion::_prepareLeftWheel() {
	_leftWheel.attach(_leftWheelPin);
}

void BasicMotion::_prepareRightWheel() {
	_rightWheel.attach(_rightWheelPin);
}

void BasicMotion::_stopBothWheels() {
	_stopLeftWheel();
	_stopRightWheel();
}

void BasicMotion::_stopLeftWheel() {
	_leftWheel.detach();
}

void BasicMotion::_stopRightWheel() {
	_rightWheel.detach();
}
