#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorscoop,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorlift,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

#define JOYSTICK_MIN 10
#define SERVO_CHANGE_RATE 10

int MOTOR_LP = 55;
int MOTOR_LN = -MOTOR_LP;
int MOTOR_WP = 75;
int MOTOR_WN = -MOTOR_WP;
int MOTOR_F = 50;
int servoUp = 63;
int servoDown = 0;

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  definitions and variables for the motor slew rate controller.              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

#define MOTOR_NUM               5
#define MOTOR_MAX_VALUE         127
#define MOTOR_MIN_VALUE         (-127)
#define MOTOR_DEFAULT_SLEW_RATE 5      // Default will cause 375mS from full fwd to rev
#define MOTOR_FAST_SLEW_RATE    256     // essentially off
#define MOTOR_TASK_DELAY        15      // task 1/frequency in mS (about 66Hz)
#define MOTOR_DEADBAND          10

// Array to hold requested speed for the motors
int motorReq[ MOTOR_NUM ];

// Array to hold "slew rate" for the motors, the maximum change every time the task
// runs checking current mootor speed.
int motorSlew[ MOTOR_NUM ];



/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  Task  - compares the requested speed of each motor to the current speed    */
/*          and increments or decrements to reduce the difference as necessary */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

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

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
	// Place code here to initialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
	disableDiagnosticsDisplay();
	SensorType[S2] = sensorNone;
	SensorType[S3] = sensorNone;
	SensorType[S4] = sensorNone;
	servo[servo1]=0;
	servo[servo2]=0;
	return;
}

void shovelthingy()
{

	getJoystickSettings(joystick);

	if (joy1Btn(1) == 1)
	{
		motor[motorscoop]=1;
	}
	else if (joy1Btn(3) == 10)
	{
		motor[motorscoop] = -10;
	}
	else
	{
		motor[motorscoop]=0;
	}
}

void scissorLift()
{
	getJoystickSettings(joystick);

	if (joy1Btn (6) == 1 )//6 is left trigger
	{
		motor[motorlift] = 75;
	}
	else if (joy1Btn (7) == 1) // is if, else if, not working? Trying if, else, if
	{
		motor[motorlift] = -75;
	}
	else //right trigger
	{
		motor[motorlift]= 0;
	}
}

void servothingy()
{
	getJoystickSettings(joystick);

	if (joy1Btn(0))//button zero is x
	{
		servo[servo1] = servoUp;
		//servo[servo2] = servoUp;
	}
	else if (joy1Btn(2))//button 2 is b
	{
		servo[servo1] = servoDown;
	//servo[servo2] = servoDown;
	}
  else
  {
  	servo[servo1] = 127;
	}
}

void ballrelease()
{
	getJoystickSettings(joystick);

	if (joy1Btn(4))
	{
		servo[servo3] = 127;
	}
	else
	{
		servo[servo3] = 0;
	}

}

void driveMotors ()
{
	int joyLeft = joystick.joy1_y1;
	int joyRight = joystick.joy1_y2;

	// If the left or right joysticks are engaged beyond a minimum threshold, operate the drive
	// motors; else stop them. The threshold is needed because a joystick that is not being touched
	// can still show small non-zero values.
	// Uses exponential increase in speed to help smooth the control at slow speeds.
	if ((abs(joyLeft) > JOYSTICK_MIN) || (abs(joyRight) > JOYSTICK_MIN))
	{
		if (abs(joyLeft) < 80)
		{
			if (joyLeft > 0)
				joyLeft = 1*pow(1+.056,joyLeft);// reverse (1+.056,joyLeft) to produce more gentle curve
			else
				joyLeft = -1*pow(1+.056,abs(joyLeft));
		}

		if (abs(joyRight) < 80)
		{
			if (joyRight > 0)
				joyRight = 1*pow(1+.056,joyRight);
			else
				joyRight = -1*pow(1+.056,abs(joyRight));
		}

		motor[motorL] = (joyLeft)*90/127;
		motor[motorR] = (joyRight)*90/127;
	}
	else
	{
		motor[motorL] = 0;
		motor[motorR] = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase

	//StartTask(MotorSlewRateTask);

	while (true)
	{
		///////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////
		////                                                   ////
		////      Add your robot specific tele-op code here.   ////
		////                                                   ////
		///////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////

		// Insert code to have servos and motors respond to joystick and button values.

		// Look in the ROBOTC samples folder for programs that may be similar to what you want to perform.
		// You may be able to find "snippets" of code that are similar to the functions that you want to
		// perform.

		getJoystickSettings(joystick);   // Obtain current game controller settings

		nxtDisplayString(0, "joy1_x1: %d ", joystick.joy1_x1);
		nxtDisplayString(1, "joy1_y1: %d ", joystick.joy1_y1);
		nxtDisplayString(2, "joy1_x2: %d ", joystick.joy1_x2);
		nxtDisplayString(3, "joy1_y2: %d  ", joystick.joy1_y2);
		nxtDisplayString(4, "Buttons: %d  ", joystick.joy1_Buttons);
		nxtDisplayString(5, "TopHat:  %d  ", joystick.joy1_TopHat);
		ballrelease();
		servothingy();
		scissorLift();
		shovelthingy();
		// Drive Motors
		driveMotors();
		// Move the lift
	}
}
