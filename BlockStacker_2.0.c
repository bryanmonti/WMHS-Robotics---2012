/*
Author: Bryan Monti
Date: 5/4/2012
Time: 7:47:31 PM

Name: BlockStacker MK2

Description: This program is going to be used on the BlockStacker bot. This robot is equipped with a camera and a height adjustable claw to stack the colored blocks. The method for color tracking will be to directly look for the color then use the track_confidence() function to idenity the correct color in the sequence. It will first scan for the blue block then

TODO: Figure out how to stack blocks in MPA without losing track of location

NOTES: If track confidence is above 50, use it.
*/

/* Motor ports */
int LEFT_MOTOR = 0;
int RIGHT_MOTOR = 3;
int PULLEY_MOTOR = 1;

/* Track setups here */
int BLUE_TRACK = 3; //Blue tracking is on track 3
int YELLOW_TRACK = 1; //Yellow tracking is on track 1
int RED_TRACK = 0; //Red tracking is on track 0

void DRIVE_STRAIGHT()
{
	
}

void TURN_RIGHT()
{
	mav(LEFT_MOTOR,500);
	mav(RIGHT_MOTOR,-500);//This negative may have to be flipped
}

void TURN_LEFT()
{
	mav(LEFT_MOTOR,-500);
	mav(RIGHT_MOTOR,500);//Change the negative if needed
}

void update()//Because I wanted it shorter.
{
	track_update();
}

void scan_blue()
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
		DRIVE_STRAIGHT();//Drive until you hit the yellow block
	}
	
}

void scan_red()
{
	update();
}

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
