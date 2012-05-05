/*
Author: Bryan Monti
Date: 5/4/2012
Time: 7:47:31 PM

Name: BlockStacker MK2

Description: This program is going to be used on the BlockStacker bot. This robot is equipped with a camera and a height adjustable claw to stack the colored blocks. The method for color tracking will be to directly look for the color then use the track_confidence() function to idenity the correct color in the sequence. It will first scan for the blue block then

TODO:

NOTES: If track confidence is above 50, use it.
*/

int BLUE_TRACK = 3; //Blue tracking is on track 3
int YELLOW_TRACK = 1; //Yellow tracking is on track 1
int RED_TRACK = 0; //Red tracking is on track 0

void update()
{
	track_update();
}

void scan_blue()
{
	update();
	int blue_confidence = track_confidence(BLUE_TRACK,1);
	printf("%d\n",blue_confidence)
}

void scan_yellow()
{
	update();
	
}

void scan_red()
{
	update();
}

int main()
{/* TESTING track_confidence()
	track_update();
	track_confidence(0,1);
	printf("Testing RED: %d\n",track_confidence(0,1));
	sleep(4);
	
	track_update();
	track_confidence(1,1);
	printf("Testing YELLOW: %d\n",track_confidence(1,1));
	sleep(4);
	
	track_update();
	track_confidence(3,1);
	printf("Testing BLUE: %d\n",track_confidence(3,1));
	sleep(4);
	*/
}
