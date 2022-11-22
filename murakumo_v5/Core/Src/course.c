#include "course.h"

uint16_t course_state_time;
double course_length;

void course_init()
{
	course_state_time = 0;
	course_length = 0;
}

void course_start()
{
	/* course_start */
}

void course_end()
{
	if(rotary_read_playmode() == search)
	{
		flash_write();
	}
}

double course_read_length()
{
	return course_length;
}

double course_add_length(double length)
{
	course_length += length;
	return course_read_length();
}

uint16_t course_read_state_time()
{
    return course_state_time;
}

void course_increment_state_time()
{
    course_state_time++;
}

double course_calclate_radius()
{
    short int left_length, right_length;
	left_length = tim10_read_length_left();
	right_length = tim10_read_length_right();
	tim10_length_init();
    return (double) TREAD * (double) ((left_length) + (right_length)) / (double) ((left_length) - (right_length)) / (double) 2;
}

void course_state_function()
{
	if(rotary_read_playmode() == search)
	{
		if(course_read_state_time() + 1 >= COURSE_STATE_SIZE)	// sizeof(flash_buffer.radius) / sizeof(flash_buffer.radius[0]))
		{
            motor_enable(0);
		}
		else
		{
#if USE_COURSE_STATE_TIME
			course_increment_state_time();
#endif
			flashbuffer.course_state_time_max = course_read_state_time();
//			my_gyro.z = theta * RADPERDEG;
//			my_gyro.z *= RADPERDEG;
			flashbuffer.radius[course_state_time] = course_calclate_radius();
			course_length = 0;
//			my_gyro.z = 0;
		}
	}
	if(rotary_read_playmode() == accel)
	{
//		velocity_control_switch_function();
		if(course_read_state_time() + 1 >= COURSE_STATE_SIZE)	// sizeof(flash_buffer.radius) / sizeof(flash_buffer.radius[0]))
		{
			motor_enable(0);
		}
		else
		{
#if USE_COURSE_STATE_TIME
			course_increment_state_time();
#endif
		}
	}
}

