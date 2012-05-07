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

int position = BOTTOM;//claw starts in bottom position
int claw_state = OPEN;//claw starts in open position

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

#pragma region Function Prototypes

void claw_position(position)
{
	switch(position)
	{
		case BOTTOM:
			if(position != BOTTOM)//to prevent the claw from damage or falling off slide
			{
				if(position == TOP)
				{
					//move down 4 seconds
				}
				else if(position == MIDDLE)
				{
					//move down 2 seconds
				}
			}
			break;

		case MIDDLE:
			if(position != MIDDLE)//to prevent the claw from damage or falling off slide
			{
				if(position == BOTTOM)
				{
					//move up 2 seconds
				}
				else if(position == TOP)
				{
					//move down 2 seconds
				}
			}
			break;

		case TOP://Goal is to be in TOP position
			if(position != TOP)//to prevent the claw from smashing or falling off slide
			{
				if(position == BOTTOM)
				{
					//move up 4 seconds
				}
				else if(position == MIDDLE)
				{
					//move up 2 seconds
				}
			}
			break;
	}

}//Well, that's a fuck load of code.

void open_claw()//try condensing this into one function like above
{
	if(claw_state != 1)
	{
		set_servo_position(CLAW_SERVO,1300);
		claw_state = 1;
	}
	else //Error checking
	{
		printf("I'm in the open position already!\n");
	}
}

void close_claw()
{
	if(claw_state != 0)
	{
		set_servo_position(CLAW_SERVO,250);
		claw_state = 0;
	}
	else //Error checking
	{
		printf("I'm in the closed position already!\n");
	}
}

void DRIVE_STRAIGHT()
{
	mav(LEFT_MOTOR,500);
	mav(RIGHT_MOTOR,500);
	sleep(1);
}

void TURN_RIGHT()
{
	mav(LEFT_MOTOR,500);
	mav(RIGHT_MOTOR,-500);//This negative may have to be flipped
}

void TURN_LEFT()//setup 45, 90, 135, 180 turns
{
	mav(LEFT_MOTOR,-500);
	mav(RIGHT_MOTOR,500);//Change the negative if needed
}

void update()//Because I wanted it shorter.
{
	track_update();
}

void track_blue()
{
	update();
	int blue_x = track_x(BLUE_TRACK,0);
	int blue_y = track_y(BLUE_TRACK,0);
	
}

void track_yellow()//Looks for large yellow blob (block) and follows it then grabs it.
{
	update();
	int yellow_x = track_x(YELLOW_TRACK,0);
	int yellow_y = track_y(YELLOW_TRACK,0);
	if(yellow_x < 70)
	{
		update();//Is this needed?
		while(yellow_x < 70)
		{
			TURN_RIGHT();
			sleep(.1);
			update();
		}
	}
	else if(yellow_x > 90)
	{
		update();//Is this needed?
		while(yellow_x < 90)
		{
			TURN_LEFT();
			sleep(.1);
			update();
		}
	}
	else
	{
		while(digital(8) == 0)
		{
			DRIVE_STRAIGHT();//Drive until you hit the yellow block
			sleep(1);
		}
	}
}

void scan_red()
{
	update();
}

#pragma endregion

int main()
{
	int time = 6;
	track_update();
	track_confidence(0,0);
	printf("Testing RED: %d, %d\n",track_confidence(0,0), track_size(0,0));
	sleep(time);
	
	track_update();
	printf("Testing YELLOW: %d, %d\n",track_confidence(1,0), track_size(1,0));
	sleep(time);
	
	track_update();
	printf("Testing BLUE: %d, %d\n",track_confidence(3,0), track_size(3,0));
	sleep(time);
	
}
