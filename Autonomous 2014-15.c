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
#define DRIVE_SPEED 60
#define MOTOR_DEFAULT_SLEW_RATE 5      // Default will cause 375mS from full fwd to rev
#define MOTOR_FAST_SLEW_RATE    256
#define MOTOR_TASK_DELAY        15      // task 1/frequency in mS (about 66Hz)

string Left = "L";
string Right = "R";

int motorSlew[ MOTOR_NUM ];
int motorReq[ MOTOR_NUM ];
void GoInches(float inches, int speed);
void ResetEncoders();

task MotorSlewRateTask()
{
	int motorIndex;
	int motorTmp;

	// Initialize stuff
	for(motorIndex=0;motorIndex<MOTOR_NUM;motorIndex++)
	{
		motorReq[motorIndex] = 0;
		motorSlew[motorIndex] = MOTOR_DEFAULT_SLEW_RATE;
	}

	// run task until stopped
	while( true )
	{
		// run loop for every motor
		for( motorIndex=0; motorIndex<MOTOR_NUM; motorIndex++)
		{
			// So we don't keep accessing the internal storage
			motorTmp = motor[ motorIndex ];

			// Do we need to change the motor value ?
			if( motorTmp != motorReq[motorIndex] )
			{
				// increasing motor value
				if( motorReq[motorIndex] > motorTmp )
				{
					motorTmp += motorSlew[motorIndex];
					// limit
					if( motorTmp > motorReq[motorIndex] )
						motorTmp = motorReq[motorIndex];
				}

				// decreasing motor value
				if( motorReq[motorIndex] < motorTmp )
				{
					motorTmp -= motorSlew[motorIndex];
					// limit
					if( motorTmp < motorReq[motorIndex] )
						motorTmp = motorReq[motorIndex];
				}

				// finally set motor
				motor[motorIndex] = motorTmp;
			}
		}

		// Wait approx the speed of motor update over the spi bus
		wait1Msec( MOTOR_TASK_DELAY );
	}
}

int convert(float inches)
{
	return (int)(inches * ENCODER_TICKS_INCH);
}



void StopMotors()
{
	motorReq[motorL]=0;
	motorReq[motorR]=0;
	wait10Msec(20);
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


void Turn272(string direction)
{
motorReq[motorL] = direction == "L" ? -12 : 50;
motorReq[motorR] = direction == "L" ? 12 : -50;
	wait10Msec(100);
	StopMotors();
}

void GoInches(float inches, int speed)
{
	ResetEncoders();
	wait1Msec(200);
	motorReq[motorL] = speed;
	motorReq[motorR] = speed;
	//motor[motorL] = speed;
	//motor[motorR] = speed;
	while  ((abs(nMotorEncoder[motorR]) + abs(nMotorEncoder[motorL])) / 2 < (convert(inches))){}
}

void CentrePos1()
{
	GoInches(20,75);
	Turn90(Left);
	GoInches(13,75);
	Turn90(Right);
	GoInches(31,75);
	StopMotors();
}

void CentrePos2 ()

{

	GoInches(39,75);
	Turn272(Left);
	StopMotors();
}

void centrePos3()
{

}


task main()

{
	//waitForStart();
	StartTask(MotorSlewRateTask);
	wait1Msec(1500);
	GoInches(58, 75);
	Turn90(Left);
	CentrePos2();
	wait1Msec(1000);
	//EndOfMatch();
}
