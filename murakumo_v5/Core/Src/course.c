#include "course.h"

uint16_t course_state_count;
double course_length;
double course_by_state_length_left, course_by_state_length_right;
double course_section_degree;
double course_curvature_radius;
/**
 * @name course_by_state_time_ms
 * @brief 現在の区間の開始マーカを読んだ時の時間を格納
 * 
 */
unsigned int course_by_state_time_ms;

void course_init()
{
	course_state_count = 0;
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

/**
 * @fn course_update_section_degree()
 * @brief コースの角速度を加算していく
 * 
 */
void course_update_section_degree()
{
	if(time_read_ms() - course_by_state_time_ms == 0)
	{
		imu_update_gyro();
		course_section_degree = course_section_degree + imu_read_yaw() * (time_read_ms() - course_by_state_time_ms);
	}
}

double course_read_section_degree()
{
	return course_section_degree;
}

void course_reset_section_degree()
{
	course_section_degree = 0;
}

double course_read_length()
{
	return course_length;
}

double course_read_curvature_radius()
{
	return course_curvature_radius;
}

uint16_t course_read_state_count()
{
    return course_state_count;
}

void course_increment_state_count()
{
    course_state_count++;
}

/**
 * @fn course_calclate_radius()
 * @brief 区間の半径を計測する
 * @return double 
 * @sa course_state_function()
 * @attention course_state_function() からのみ呼び出される
 * 
 */
double course_calclate_radius()
{
    int left_length, right_length;
    double curvature_radius;
	double section_degree, section_length;

    /* 前センサからの長さを記録する */
	left_length = length_read_left() - course_by_state_length_left;
	right_length = length_read_right() - course_by_state_length_right;
	section_length = (left_length + right_length) / 2;
	section_degree = course_read_section_degree();

	//! 半径を計算した絶対時間を格納する
	course_by_state_time_ms = time_read_ms();

	/* 極率半径を計算する */
#if MODE_ENCODER_CALCLATE
	curvature_radius = (double) TREAD * (double) ((left_length) + (right_length)) / (double) ((left_length) - (right_length)) / (double) 2;
#endif

#if MODE_IMU_CALCLATE
	course_section_length = // course_section_length_from_imu
#endif

	curvature_radius = section_length / section_degree;
	course_curvature_radius = curvature_radius;
	course_reset_section_degree();

    return curvature_radius;
}

/**
 * @fn course_state_function()
 * @brief 
 * @details
 * 左センサを読んだら、あるいは、一定区間進んだら course_state_function() を実行するようにプログラムする
 * 探索か二次走行かは course_state_function() 関数内で判断する必要がある
 * 
 */
void course_state_function()
{
	if(rotary_read_playmode() == search)
	{
#if USE_COURSE_STATE_COUNT
		course_increment_state_count();
#endif
		flashbuffer.course_state_count_max = course_read_state_count();
//			my_gyro.z = theta * RADPERDEG;
//			my_gyro.z *= RADPERDEG;
		flashbuffer.radius[course_state_count] = course_calclate_radius();
//		course_length = 0;
//			my_gyro.z = 0;
	}
	if(rotary_read_playmode() == accel)
	{
//		velocity_control_switch_function();
#if USE_COURSE_STATE_COUNT
		course_increment_state_count();
#endif
	}
}

void course_d_print()
{
#if D_COURSE
	printf("length = %7.2lf, degree = %7.2lf, radius = %7.2lf", length_read(), course_read_section_degree(), course_read_curvature_radius());
#endif
}
