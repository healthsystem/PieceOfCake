#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     IRseeker,       sensorI2CCustom)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorL,        tmotorTetrix, PIDControl, reversed, encoder)

#define MOTOR_NUM          5
int motorReq[ MOTOR_NUM ];
void GoInches(float inches, int speed);

void GoInches(float inches, int speed)
{
	ResetEncoders();
	wait1Msec(200);
	motorReq[motorL] = speed;
	motorReq[motorR] = speed;
	motor[motorL] = speed;
	motor[motorR] = speed;
	while ((abs(nMotorEncoder[motorR]) + abs(nMotorEncoder[motorL])) / 2 < (convert(inches)))
	}

task main()

{
wait1Msec(3000);
GoInches(50, 50);
wait1Msec(10000);

//waitForStart;
}
