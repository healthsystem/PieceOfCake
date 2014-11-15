#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     IRseeker,       sensorI2CCustom)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorL,        tmotorTetrix, PIDControl, reversed, encoder)

#include "rdpartyrobotcdr-3.3.1\drivers\hitechnic-irseeker-v2.h"
//#include "JoystickDriver.c"

#define MOTOR_NUM          5
#define ENCODER_TICKS_INCH 102

int motorReq[ MOTOR_NUM ];
void GoInches(float inches, int speed);
void ResetEncoders();

int convert(float inches)
{
	return (int)(inches * ENCODER_TICKS_INCH);
}


void ResetEncoders()
{
	nMotorEncoder[motorL] = 0;
	nMotorEncoder[motorR] = 0;
	wait10Msec(30);
}

void Turn90(string direction)
{
	// Adjust the requested direction to reflect the actual location of the beacon.
	//direction = beaconDirection == direction ? "L" : "R";
	motorReq[motorL] = direction == "L" ? -50 :50;
	motorReq[motorR] = direction == "L" ? 50 : -50;
	wait10Msec(100);
	StopMotors();
}



void GoInches(float inches, int speed)
{
	ResetEncoders();
	wait1Msec(200);
	motorReq[motorL] = speed;
	motorReq[motorR] = speed;
	motor[motorL] = speed;
	motor[motorR] = speed;
	while  ((abs(nMotorEncoder[motorR]) + abs(nMotorEncoder[motorL])) / 2 < (convert(inches))){}
}
//waitForStart();

task main()

{
wait1Msec(3000);
GoInches(12, 50);

Turn90("L");
	motor[motorL] = 0;
	motor[motorR] = 0;

wait1Msec(1000);

//EndOfMatch();

}
