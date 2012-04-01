// Created on Fri Mar 30 2012

#include <stdio.h>
void startup()
{
	shut_down_in(115);//We get 120 seconds, but its nice to be on the safe side
	//if using this, make sure to use ao()
}

void stop_all()
{
	ao();
	//set_servo_position(servo_a, /*Make this pointing in the 0 degree angle*/);
	//set_servo_position(servo_b, /*Same as above*/);
}

void ease_dual(int servo_a, int servo_b, int new_position, int interval)//ease bracket up into 90 degree position, then make function for flinging it into the beach
{
	int current_pos_a = get_servo_position(servo_a);
	int current_pos_b = get_servo_position(servo_b);
	
	current_pos_a = new_position - current_pos_a;//how far we have to travel-- FIX THIS SHIT
	current_pos_b = new_position - current_pos_b + 100;//plus 100 because this servo is always off by a margin
	
	while(current_pos_a < new_position)
	{
		//int travel_distance_b = travel_distance - 100;
		set_servo_position(servo_a,87);
		set_servo_position(servo_b,897);
		sleep(interval);
		current_pos_a++;
		current_pos_a++;
		sleep(interval);
		
	}
	printf("FUCK YEAH IT WORKED\n");
}
int sleep_time = 30;

int main() 
{
	//startup();
	set_servo_position(0,1230);
	set_servo_position(3,1330);
	mav(3,500);
	mav(0,500);
	sleep(2.8);
	ao();
	enable_servos();
	set_servo_position(0,60);//90 degrees
	set_servo_position(3,160);
	sleep(sleep_time);
	
	return 0;
}
