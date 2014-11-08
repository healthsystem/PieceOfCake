#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S3,     IRseeker,       sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorL,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)

#include "rdpartyrobotcdr-3.3.1\drivers\hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"

#define BEFORE_START_10MS 0
#define DRIVE_SPEED 80
#define ENCODER_TICKS_INCH 100
#define ENCODER_TICKS_90_TURN 2275

int motorReq[ MOTOR_NUM ];

void Turn90 (string direction);
void GoInches(float inches, int speed);

task main()
{
void GoInches(float inches, int speed)
{
	ResetEncoders();
	wait1Msec(200);
	motorReq[motorL] = speed;
	motorReq[motorR] = speed;
	//motor[motorL] = speed;
	//motor[motorR] = speed;
	while ((abs(nMotorEncoder[motorR]) + abs(nMotorEncoder[motorL])) / 2 < (convert(inches)))
	{
	}

	StopMotors();
}


}
