#include "course.h"

uint16_t course_state_count;
double course_by_state_length_left, course_by_state_length_right;
double course_section_degree;
double course_curvature_radius;
double course_update_section_sampling_time_s;
/**
 * @name course_by_state_time_ms
 * @brief 現在の区間の開始マーカを読んだ時の時間を格納
 * 
 */
unsigned int course_by_state_time_ms;
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
	imu_start();
}

void course_stop()
{
	if(rotary_read_playmode() == search)
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
	double tmp;
	imu_update_gyro();
	#if D_COURSE_WHILE
	printf("imu_read_yaw() = %7.2lf, course_section_degree = %7.2lf\r\n", imu_read_yaw(), course_section_degree);
	#endif
	tmp = course_section_degree + imu_read_yaw() * course_update_section_sampling_time_s;
	course_section_degree = low_pass_filter(tmp, course_section_degree, 0);
}

void course_set_update_section_freq_ms(unsigned short int samplingtime_ms)
{
	course_update_section_sampling_time_s = samplingtime_ms / (double) 1000;
}

double course_read_section_degree()
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
 * course_calclate_radius()			// 半径の計算
 * course_read_curvature_radius()	// 計算した半径を取得する
 * course_reset()					// 角度と長さ情報をリセットする
 * の順に呼び出す必要がある
 * 
 */
void course_calclate_radius()
{
    double curvature_radius;
	double section_degree, section_length;
	double section_radian;

    /* 長さを取得する */
	section_length = length_read();
	section_degree = course_read_section_degree();

	/* 極率半径を計算する */
#if MODE_ENCODER_CALCLATE
	curvature_radius = (double) TREAD * (double) ((left_length) + (right_length)) / (double) ((left_length) - (right_length)) / (double) 2;
#endif

#if MODE_IMU_CALCLATE
	course_section_length = // course_section_length_from_imu
#endif

	section_radian = section_degree * M_PI / (double) 180;
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
#if USE_COURSE_STATE_COUNT
		course_increment_state_count();
#endif
		flashbuffer.course_state_count_max = course_read_state_count();
//			my_gyro.z = theta * RADPERDEG;
//			my_gyro.z *= RADPERDEG;
		course_calclate_radius();
		flashbuffer.radius[course_state_count] = course_read_curvature_radius();
		course_reset();
//			my_gyro.z = 0;
	}
	if(rotary_read_playmode() == accel)
	{
//		velocity_control_switch_function();
#if USE_COURSE_STATE_COUNT
		course_increment_state_count();
#endif
	}
	course_increment_state_count();
}

void course_d_print()
{
#if D_COURSE
	printf("length = %7.2lf, degree = %7.2lf, radius = %7.2lf\r\n",
		length_read(), course_read_section_degree(), course_read_curvature_radius());
	// printf("course_state_function の実行回数 = %d\r\n", __debug_eradiusecute_count__);
#endif
}

uint16_t course_radius2speed(float radius)
{
	uint16_t speed;
	if(radius < 0.1f) speed = 1000;
    else if(radius < 0.25f) speed = 1250;
    else if(radius < 0.5f) speed = 1500;
    else if(radius < 0.75f) speed = 1750;
    else if(radius < 1.0f) speed = 2000;
    else if(radius < 1.5f) speed = 2500;
    else if(radius < 2.0f) speed = 3000;
    else speed = 3000;
	// speed = - (4238566523291511 * pow(radius, 5)) / (double) 633825300114114700748351602688 + (8582934509267735 * pow(radius, 4)) / (double) 77371252455336267181195264 - (1459060547913519 * pow(radius, 3)) / (double) 2361183241434822606848 + (2682365349594497 * pow(radius, 2)) / (double) 2305843009213693952 + (1737420468106149 * radius) / (double) 4503599627370496 + 7057670738269725 / (double) 8796093022208;
	return speed;
}
