/*	Main program for the BoxBot
		IR controller, which uses an interrupt, determines which function will be executed
		Uses BasicMotion, LightScanner, LineSensor, and UltrasonicReader libraries
*/

#include <Servo.h>
#include "BasicMotion.h"
#include "LightScanner.h"
#include "UltrasonicReader.h"
#include "LineSensor.h"

#include <IRremote.h>
const byte IR_PIN = 2;
IRrecv irRecv(IR_PIN);
decode_results results;
volatile int vButton = 99;
 
BasicMotion motion(0, 10, 9); //ROTATE_SPEED 0, LEFT_WHEEL_PIN 10, RIGHT_WHEEL_PIN 9
LightScanner seeker(16, 17, 11, 10); //LEFT_LIGHT_PIN (16=A2), RIGHT_LIGHT_PIN (17=A3), HEAD_SERVO_PIN 11, LIGHT_ACCURACY 10
UltrasonicReader usr(6, 7);	//triggerPin = 6, echoPin = 7
LineSensor lineSensor(18, 19, 3, 4); //LEFT_LINE_INPUT (18=A4), RIGHT_LINE_INPUT (19=A5), left LED power 3, right LED power 4);

//int aButton[] = {13,1,2,3,4,5,6,7,8,9,0}; //0 element is power button, each entry represents the lowbyte code fromt he remote
int aButton[] = {207,119,143,15,87,183,55,103,151,23,167}; //Paul's control
const int LINE_FOLLOW_SPEED = 100;

void setup() {
	Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(IR_PIN), readRemote, CHANGE);
  irRecv.enableIRIn(); // Start the IR receiver
  delay(250);
}

void loop() {
//	ctrl = readRemote();  //read the remote control
//  Serial.println(ctrl);
//  delay(750);

//	if(ctrl != lastCmd)
//	{
//		lastCmd = ctrl;
//Serial.print("vButton: ");
//Serial.println(vButton);
		switch (vButton)
		{
			case 0: //stop BoxBot
        Serial.println("Stop");
				while(1){};
				break;
			case 1: //1 - line follower
        motion.calibrate(4.0);
				followLine(1);
				break;
			case 2: //2 - light follower
        motion.calibrate(5.5);
				followLight(2);
				break;
			case 3: //3 - object avoidance
        motion.calibrate(5.5);
				avoidObject(3);
				break;
      case 4: //4 - box turns
        motion.calibrate(5.5);
        boxTurns(4);
        break;
			default:
				break;
		}

//	}
}

void readRemote()
{
  int ctrl = 99;
  if (irRecv.decode(&results)) {
    ctrl = lowByte(results.value);  //Get just the right most byte
    Serial.print("Ctrl: ");
    Serial.println(ctrl);
    irRecv.resume(); // Receive the next value
    for(int i=0; i<11; i++)
    {
      if(ctrl == aButton[i])
      {
        vButton = i;
        break;
      }
    }
  }
}

void followLight(int key)
{
  seeker.calibrate(0, 40, 1.00688, 1.01789); //left adjustment, right adjustment, left constant, right constant
	seeker.initOrientation(motion);
	while(vButton == key)
		seeker.followLight(motion);
}

void avoidObject(int key)
{
  while(vButton == key)
  {
    long distance = usr.readDistance();
    Serial.print("Distance: ");
    Serial.println(distance);
		if(distance <= 30)	//avoid objects within 30 cm
			motion.increaseRotation(90, 1);
		else
			motion.moveBothWheels(100, 500);
    delay(250);
  }
}

void followLine(int key)
{
  lineSensor.enableSensor();
	while(vButton == key)
	{
		int leftReading = lineSensor.readLeftSensor();// - 22;
		int rightReading = lineSensor.readRightSensor();
  Serial.print("Line Sensor - ");
  Serial.print(leftReading);
  Serial.print(" : ");
  Serial.print(rightReading);
  Serial.println();

    if(leftReading < 600)
      motion.moveRight(100, 20);
    else if(rightReading < 600)
      motion.moveLeft(100, 20);
    else
      motion.moveBothWheels(LINE_FOLLOW_SPEED, 35);
/*
		if(abs(leftReading - rightReading) <= 100) {
			motion.moveBothWheels(LINE_FOLLOW_SPEED, 35);
		}else{
			if(leftReading > rightReading) {
				motion.increaseRotation(5, 1);
			} 
			if(rightReading > leftReading) {
				motion.increaseRotation(5, -1);
			}
		}
		delay(250);
*/
	}
  lineSensor.disableSensor();
}

void boxTurns(int key)
{
  while(vButton == key)
  {
    Serial.println("Box turns");
    for (int i = 0; i < 4; i++)
    {
      motion.moveLeftWheel(150, 1000);
      motion.moveBothWheels(150, 1000);
      delay(500);
    }
  }
}


