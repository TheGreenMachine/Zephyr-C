#include "WPILib.h"
#include "GamePadL.h"


class RobotDemo : public SimpleRobot
{
RobotDrive myRobot;
GamepadL gamepad; 
GamepadL gamepad2;
Jaguar shooter;
Compressor comp;
Relay rel;
float speed;
const float shooterStep;
Relay::Value pistonPosition;
float leftSpeed;
float rightSpeed;
bool is1Stick;
public:
RobotDemo(void):
myRobot(2, 1),
gamepad(1),
gamepad2(2),
comp(1,1),
shooter(3),
rel(2),
speed(0),
shooterStep(0.01),
pistonPosition(Relay::kOff),
leftSpeed(0.0),
rightSpeed(0.0),
is1Stick(false)
{
	myRobot.SetExpiration(0.1);
	comp.Start();
	myRobot.SetSafetyEnabled(true);
}

void mechanismSet()
{
	shooter.Set(speed);
	if(!is1Stick)
	{
	myRobot.TankDrive(leftSpeed, rightSpeed);
	}
	else{
		myRobot.TankDrive(leftSpeed, leftSpeed);
	}
	rel.Set(pistonPosition);
	
}

void Autonomous(void)
{
	myRobot.SetSafetyEnabled(false);
	myRobot.Drive(0.5, 0.0); 
	Wait(2.0); //    for 2 seconds
	myRobot.Drive(0.0, 0.0);
}

float RegulateSpeed (float speed)
{
	if (speed > 1.0)
	{
		speed = 1.0;
	} 
	if (speed < -1.0)
	{
		speed = -1.0;
	}
	return speed;
}

void OperatorControl(void)
{

	while (IsOperatorControl())
	{
		
		//RegulateSpeed(speed);
		//if (leftstick.GetY() == 1 && rightstick.GetY() == 1)
		leftSpeed= gamepad.GetLeftY()*(-1);
		rightSpeed = gamepad.GetRightY();
		
		if (gamepad.GetRawButton(5))
		{
			pistonPosition = Relay::kReverse;
		}
		else{
			pistonPosition = Relay::kForward;
		}
		
		if (gamepad.GetRawButton(6))
		{
			speed+=shooterStep;
		}
		if (gamepad.GetRawButton(8))
		{
			speed -=shooterStep;
		}
		if (gamepad.GetRawButton(1))
		{
			speed=-1;
		}
		if (gamepad.GetRawButton(2))
		{
			speed=0;
		}
		if (gamepad.GetRawButton(9))
		{
			is1Stick=!is1Stick;
		}
		mechanismSet();
		Wait(0.005);
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
