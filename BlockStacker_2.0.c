/* 
*****************************************************
Author: Bryan Monti
Date: 5/4/2012
Time: 7:47:31 PM

Name: BlockStacker MK2

Description: This program is going to be used on the 
BlockStacker bot. This robot is equipped with a camera 
and a height adjustable claw to stack the colored blocks.
The method for color tracking will be to directly look
for the color then use the track_confidence() function
to idenity the correct color in the sequence. It will 
first scan for the blue block then move in to capture
it. It will then place it in the MPA and move onto the 

TODO: Figure out how to stack blocks in MPA without losing track of location

NOTES: 
1. If track confidence returns a value >= 50, use it.
2. Robot must start with claw in open position.
***************************************************** 
*/
#pragma region DEFINES
#define BOTTOM 0
#define MIDDLE 1
#define TOP 2
#define OPEN 1
#define CLOSED 0
#pragma endregion

#pragma region Startup Requirments
int current_position = BOTTOM;//claw starts in bottom position
int claw_state = OPEN;//claw starts in open position
#pragma endregion

#pragma region Motor ports
int LEFT_MOTOR = 0;
int RIGHT_MOTOR = 3;
int PULLEY_MOTOR = 1;
#pragma endregion

#pragma region Servo ports
int CLAW_SERVO = 0;
#pragma endregion

#pragma region Track setups here
int BLUE_TRACK = 3; //Blue tracking is on track 3
int YELLOW_TRACK = 1; //Yellow tracking is on track 1
int RED_TRACK = 0; //Red tracking is on track 0
#pragma endregion

//#pragma region Function Prototypes

#pragma region Claw_Height
void claw_position(position)
{
	switch(position)
	{
		case BOTTOM:
			if(current_position != BOTTOM)//to prevent the claw from damage or falling off slide
			{
				if(current_position == TOP)
				{
					move_to_position(PULLEY_MOTOR,-1000,0);
					sleep(10);//check to see if you can cut time
					current_position = BOTTOM;	
				}
				else if(current_position == MIDDLE)
				{
					move_to_position(PULLEY_MOTOR,-1000,0);
					sleep(6);//check if this needs more time
					current_position = BOTTOM;
				}
			}
			break;

		case MIDDLE:
			if(current_position != MIDDLE)//to prevent the claw from damage or falling off slide
			{
				if(current_position == BOTTOM)
				{
					move_to_position(PULLEY_MOTOR,1000,6000);
					sleep(10);//check to see if you can cut time
					current_position = MIDDLE;
				}
				else if(current_position == TOP)
				{
					move_to_position(PULLEY_MOTOR,-1000,6000);//negative because its going from TOP to BOTTOM
					sleep(6);//check if this is enough time
					current_position = MIDDLE;
				}
			}
			break;

		case TOP://Goal is to be in TOP position
			if(current_position != TOP)//to prevent the claw from smashing or falling off slide
			{
				if(current_position == BOTTOM)
				{
					move_to_position(PULLEY_MOTOR,1000,12000);
					sleep(10);
					current_position = TOP;
				}
				else if(current_position == MIDDLE)
				{
					move_to_position(PULLEY_MOTOR,1000,12000);
					sleep(6);
					current_position = TOP;
				}
			}
			break;
	}

}//Well, that's a fuck load of code.
#pragma endregion

#pragma region Open_Claw
void open_claw()//try condensing this into one function like above
{
	if(claw_state != OPEN)
	{
		set_servo_position(CLAW_SERVO,1300);
		claw_state = OPEN;
	}
	else //Error checking
	{
		printf("I'm in the open position already!\n");
	}
}
#pragma endregion

#pragma region Close_Claw
void close_claw()
{
	if(claw_state != CLOSED)
	{
		set_servo_position(CLAW_SERVO,250);
		claw_state = CLOSED;
	}
	else //Error checking
	{
		printf("I'm in the closed position already!\n");
	}
}
#pragma endregion

#pragma region Drive_Straight
void DRIVE_STRAIGHT()
{
	while(digital(8) == 0)
	{
		move_to_position(LEFT_MOTOR,1000,250);
		move_to_position(RIGHT_MOTOR,1000,250);
		sleep(1);
		clear_motor_position_counter(LEFT_MOTOR);
		clear_motor_position_counter(RIGHT_MOTOR);
	}
}
#pragma endregion

#pragma region Turn_right
void TURN_RIGHT()
{
	mav(LEFT_MOTOR,500);
	mav(RIGHT_MOTOR,-500);
}
#pragma endregion

#pragma region Turn_left
void TURN_LEFT()//setup 45, 90, 135, 180 turns
{
	mav(LEFT_MOTOR,-500);
	mav(RIGHT_MOTOR,500);//Change the negative if needed
}
#pragma endregion

#pragma region Update
void update()//Because I wanted it shorter.
{
	track_update();
}
#pragma endregion

#pragma region Track_blue
void track_blue()
{
	update();
	int blue_x = track_x(BLUE_TRACK,0);
	int blue_y = track_y(BLUE_TRACK,0);
}
#pragma endregion

#pragma region Track_yellow
void track_yellow()//Looks for large yellow blob (block) and follows it then grabs it.
{
	update();
	int yellow_x = track_x(YELLOW_TRACK,0);
	int yellow_y = track_y(YELLOW_TRACK,0);
	if(yellow_x < 70)
	{
		update();
		while(yellow_x < 70)
		{
			TURN_RIGHT();
			sleep(.1);
			update();
		}
	}
	else if(yellow_x > 90)
	{
		update();
		while(yellow_x > 90)
		{
			TURN_LEFT();
			sleep(.1);
			update();
		}
	}
	else
	{
		while(yellow_x > 70 && yellow_y < 90)
		{
			DRIVE_STRAIGHT();//Drive until you hit the yellow block
			sleep(.3);
		}
		close_claw();
		sleep(1);
	}
}
#pragma endregion

#pragma region Track_red
void track_red()//Looks for large red blob (block) and follows it then grabs it, and proceeds to stack it.
{
	update();
	int red_x = track_x(RED_TRACK,0);
	int red_y = track_y(RED_TRACK,0);
	if(red_x < 70)
	{
		update();
		while(red_x < 70)
		{
			TURN_RIGHT();
			sleep(.1);
			update();
		}
	}
	else if(red_x > 90)
	{
		update();
		while(red_x > 90)
		{
			TURN_LEFT();
			sleep(.1);
			update();
		}
	}
	else
	{
		while(red_x > 70 && red_y < 90)
		{
			DRIVE_STRAIGHT();//Drive until you hit the yellow block
			sleep(.3);
		}
		close_claw();
		sleep(1);
	}
}

#pragma endregion

#pragma endregion
int main()
{
	//scan_yellow();
	//track_yellow();
	//locate_mpa(); //MPA has a pink or green sheet to it, use the camera to locate it and bump into it to put the blocks in
	// TESTS CLAW PULLEY
	set_servo_position(CLAW_SERVO,1300);
	sleep(1);
	close_claw();
	clear_motor_position_counter(PULLEY_MOTOR);
	claw_position(TOP);
	claw_position(BOTTOM);
	claw_position(MIDDLE);
	claw_position(BOTTOM);
	claw_position(MIDDLE);
	claw_position(TOP);
	claw_position(MIDDLE);
	claw_position(BOTTOM);
	
}
