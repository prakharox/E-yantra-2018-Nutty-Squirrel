/*
*Team Id: 0039
* Author List: Madhur Raghav, Prakhar Gupta, Ayush Aggarwal, Sarthak Tanwani
* Filename: NS_Task_1_Sandbox.cpp
* Theme: Nutty Squirrel
* Functions: void forward_wls, left_turn_wls, right_turn_wls, Square, Task_1_1,Task_1_2
* Global Variables: forwardtime, turntime, lsensor, msensor, rsensor, psensor
*
*/
#include "NS_Task_1_Sandbox.h"
using namespace std;
int forwardtime = 350, turntime = 300, lsensor, msensor, rsensor, psensor;
int initial_motor_speed = 200;
float Kp = 100, Ki = 40, Kd = 4;
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;
int node = 0;
/*
*
*Function Name: read_sensorvalue
*Input: void
*Output void
*Logic: Reads the values of all the sensors and assigns to global variables
*Example call: read_sensorvalue();
*
*/
void read_sensorvalue(void)
{
	lsensor = ADC_Conversion(1);
	msensor = ADC_Conversion(2);
	rsensor = ADC_Conversion(3);
	psensor = ADC_Conversion(4);
}
/*
*
*Function name:printsensordata
*Input: void
*Output: void
*Logic: Prints the sensor data on console;
*Example call:printsensordata();
*
*/
void printsensordata(void)
{
	//read_sensorvalue();
	cout << lsensor << " " << msensor << " " << rsensor << " " << psensor << endl;
}
/*
*Function Name: nodedetect
*Input: void
*Output: bool
*Logic: Returns true if node is detected or otherwise returns false
*Example call: nodedetect()
*/
bool nodedetect(void)
{
	if (lsensor == 255 && msensor == 255 && rsensor == 255)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*
*
*Function name: PID
*Input:void
*Output: void
*Logic: Calculates the PID value for the given sensor readings
*Example Call: PID();
*
*/
void PID(void)
{
	if(lsensor + rsensor + msensor)
	error = (-3 * lsensor + 3*rsensor)/(lsensor+rsensor+msensor);
	else
	{
		error = previous_error;
	}
	P = error;
	I = I + previous_I;
	D = error - previous_error;

	PID_value = (Kp*P) + (Ki*I) + (Kd*D);
	previous_I = I;
	previous_error = error;
	//cout << error<<endl;
}
/*
*
*Function name: motorcontrol
*Input: void
*Output: void
*Logic: Drivers the motor at different speeds after calculating the speed
*Example call: motorcontrol()
*
*/
void motorcontrol(void)
{
	int left_motor_speed = initial_motor_speed + PID_value;
	int right_motor_speed = initial_motor_speed - PID_value;
	velocity(left_motor_speed, right_motor_speed);
}
/*
*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*
*/
void forward_wls(unsigned char node)
{
	forward();
	do
	{
		read_sensorvalue();
	} while (!nodedetect());
}
/*
*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); //Turns right until black line is encountered
*
*/
void left_turn_wls(void)
{
	forward();
	do
	{
		read_sensorvalue();
	} while (msensor);
	do
	{
		left();
		read_sensorvalue();
	} while (msensor != 255);
}
/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(void)
{
	forward();
	do
	{
		read_sensorvalue();
	} while (msensor);
	do
	{
		right();
		read_sensorvalue();
	} while (msensor!=255);
}
/*
*Function Name:line_follow
*Input: void
*Output: void
*Logic: Implements Line-following algorithm
*Example call: line_follow();
*/
void line_follow()
{
	forward();
	_delay_ms(50);
	do
	{
		read_sensorvalue();
		PID();
		motorcontrol();
		_delay_ms(1);
	} while (!nodedetect());
	cout << node << endl;
	node++;
}
/*
*
* Function Name: Square
* Input: void
* Output: void
* Logic: Use this function to make the robot trace a square path on the arena
* Example Call: Square();
*/
void Square(void)
{
	forward();
	_delay_ms(forwardtime);
	soft_right();
	_delay_ms(turntime);
	forward();
	_delay_ms(forwardtime);
	soft_right();
	_delay_ms(turntime);
	forward();
	_delay_ms(forwardtime);
	soft_right();
	_delay_ms(turntime);
	forward();
	_delay_ms(forwardtime);
	stop();
	_delay_ms(3000);
}
/*
*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.1 logic
* Example Call: Task_1_1();
*
*/
void Task_1_1(void)
{
	line_follow();
	right_turn_wls();
	line_follow();
	left_turn_wls();
	line_follow();
	left_turn_wls();
	line_follow();
	forward();
	_delay_ms(150);
	left();
	_delay_ms(300);
	line_follow();
	forward();
	_delay_ms(150);
	right();
	_delay_ms(700);
	line_follow();
	forward();
	_delay_ms(200);
	line_follow();
	forward();
	_delay_ms(150);
	line_follow();
	forward();
	_delay_ms(150);
	right();
	_delay_ms(600);
	line_follow();
	forward();
	_delay_ms(150);
	left();
	_delay_ms(300);
	line_follow();
	forward();
	_delay_ms(150);
	left();
	_delay_ms(230);
	line_follow();
	forward();
	_delay_ms(430);
	left();
	_delay_ms(250);
	forward();
	_delay_ms(250);
	line_follow();
	forward();
	_delay_ms(150);
	right_turn_wls();
	line_follow();
	stop();
}

/*
*
* Function Name: Task_1_2
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.2 logic
* Example Call: Task_1_2();
*/
void Task_1_2(void)
{

}
