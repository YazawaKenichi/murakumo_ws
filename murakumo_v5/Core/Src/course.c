#include "course.h"

uint16_t course_state_count;
float course_section_degree;
float course_curvature_radius;
float course_update_section_sampling_time_s;
unsigned int __debug_execute_count__;

void course_init(unsigned short int samplingtime_ms)
{
	imu_init();
	course_state_count = 0;
	course_set_update_section_freq_ms(samplingtime_ms);
}

void course_start()
{
	/* course_start */
	course_reset_section_degree();
	course_reset_flash();
	imu_start();
}

void course_stop()
{
	if(rotary_read_playmode() == search || rotary_read_playmode() == motor_free)
	{
		flash_write();
	}
	imu_stop();
}

/**
 * @fn course_update_section_degree()
 * @brief コースの角速度を加算していく
 * 好きな時に course_section_degree を読む
 * 好きな時に course_section_degree をリセットする
 * course_update_section_degree() は course_update_section_sampling_time_s の周期で常に実行され続ける
 * 
 */
void course_update_section_degree()
{
	float tmp;
	imu_update_gyro();
	#if D_COURSE_WHILE
	printf("imu_read_yaw() = %7.2lf, course_section_degree = %7.2lf\r\n", imu_read_yaw(), course_section_degree);
	#endif
	tmp = course_section_degree + imu_read_yaw() * course_update_section_sampling_time_s;
	course_section_degree = low_pass_filter(tmp, course_section_degree, 0);
}

void course_set_update_section_freq_ms(unsigned short int samplingtime_ms)
{
	course_update_section_sampling_time_s = samplingtime_ms / (float) 1000;
}

float course_read_section_degree()
{
	return course_section_degree;
}

void course_reset_section_degree()
{
	course_section_degree = 0;
}

void course_reset()
{
	course_reset_section_degree();
	length_reset();
}

float course_read_curvature_radius()
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
 * @return float 
 * @sa course_state_function()
 * @attention course_state_function() からのみ呼び出される
 * course_calclate_radius()			// 半径の計算
 * course_read_curvature_radius()	// 計算した半径を取得する
 * course_reset()					// 角度と長さ情報をリセットする
 * の順に呼び出す必要がある
 * 
 */
void course_calclate_radius()
{
    float curvature_radius;
	float section_degree, section_length;
	float section_radian;

    /* 長さを取得する */
	section_length = length_read();
	//! 角度を取得する
	section_degree = course_read_section_degree();

	/* 極率半径を計算する */
#if MODE_ENCODER_CALCLATE
	curvature_radius = (float) TREAD * (float) ((left_length) + (right_length)) / (float) ((left_length) - (right_length)) / (float) 2;
#endif

#if MODE_IMU_CALCLATE
	course_section_length = // course_section_length_from_imu
#endif

	section_radian = section_degree * M_PI / (float) 180;
	curvature_radius = section_length / section_radian;
	course_curvature_radius = curvature_radius;
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
	if(rotary_read_playmode() == search || rotary_read_playmode() == motor_free )
	{
		float radius;
#if USE_COURSE_STATE_COUNT
		course_increment_state_count();
#endif
		flashbuffer.course_state_count_max = course_read_state_count();
		course_calclate_radius();
		radius = course_read_curvature_radius();
		flashbuffer.radius[course_state_count] = radius;
		flashbuffer.speed[course_state_count] = course_radius2speed(radius);
		course_reset();
	}
	if(rotary_read_playmode() == accel)
	{
		float fixed_velocity_target;
		fixed_velocity_target = fixed_speed();
		velotrace_set_target_direct(fixed_velocity_target);
	}
	course_increment_state_count();
}

void course_d_print()
{
#if D_COURSE
	printf("length = %7.2lf, degree = %7.2lf, radius = %7.2lf\r\n", length_read(), course_read_section_degree(), course_read_curvature_radius());
	// printf("course_state_function の実行回数 = %d\r\n", __debug_eradiusecute_count__);
#endif
	encoder_d_print();
}

uint16_t course_radius2speed(float radius)
{
	uint16_t speed;
	if(radius < 0)
	{
		radius = - radius;
	}
	if(radius < 0.1f) speed = 1000;
    else if(radius < 0.25f) speed = 1000;
    else if(radius < 0.5f) speed = 1000;
    else if(radius < 0.75f) speed = 1250;
    else if(radius < 1.0f) speed = 1500;
    else if(radius < 1.5f) speed = 1750;
    else if(radius < 2.0f) speed = 2000;
    else speed = 3000;
	// speed = - (4238566523291511 * pow(radius, 5)) / (double) 633825300114114700748351602688 + (8582934509267735 * pow(radius, 4)) / (double) 77371252455336267181195264 - (1459060547913519 * pow(radius, 3)) / (double) 2361183241434822606848 + (2682365349594497 * pow(radius, 2)) / (double) 2305843009213693952 + (1737420468106149 * radius) / (double) 4503599627370496 + 7057670738269725 / (double) 8796093022208;
	return speed;
}

void course_print_flash()
{
	uint16_t course_state_size;
	course_state_size = COURSE_STATE_SIZE;
	//! print flash contents
	while(switch_read_enter())
	{
		if(course_state_size > 0)
		{
			uint16_t index;
			float print_data;
			index = COURSE_STATE_SIZE - course_state_size;
			switch(rotary_read_value())
			{
				case 15:
					print_data = flashbuffer.radius[index];
					break;
				case 14:
					print_data = flashbuffer.speed[index];
					break;
				default :
					print_data = flashbuffer.radius[index];
					break;
			}
			printf("%6d, %8lf\r\n", index, print_data);
			course_state_size = course_state_size - 1;
			HAL_Delay(100);
		}
		else
		{
			HAL_Delay(1000);
		}
	}
}

void course_reset_flash()
{
	for(uint16_t course_state_size = COURSE_STATE_SIZE; course_state_size > 0; course_state_size = course_state_size - 1)
	{
		uint16_t index;
		index = COURSE_STATE_SIZE - course_state_size;
		flashbuffer.radius[index] = COURSE_RADIUS_MAX;
		flashbuffer.speed[index] = COURSE_SPEED_DEFAULT;
	}
}
