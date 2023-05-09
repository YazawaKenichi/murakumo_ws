#include "course.h"

float data_speed[COURSE_STATE_SIZE];
uint16_t course_state_count;
uint16_t course_sampling_count;
float course_section_degree;
//! float course_section_length;
float course_section_radius;
float course_update_section_sampling_time_s;
float course_accel_max;
float __course_debug_target_speed__;

void course_init(unsigned short int samplingtime_ms) {
  imu_init();
  course_state_count = 0;
  course_set_update_section_freq_ms(samplingtime_ms);
}

void course_start() {
  /* course_start */
  course_state_count = 0;
  course_accel_max = accel_max_calc(rotary_read_value());
  course_reset_section_degree();
  if (rotary_read_playmode() == search ||
      rotary_read_playmode() == motor_free) {
    //! speed radius right left に初期値を与える
    course_reset_flash();
  }
  if (rotary_read_playmode() == accel) {
    //! coursedata だけでいい
    flash_read(FLASH_SECTOR_11);
    //! 走る前に速度を計算して書き込んでからスタートする ( 使うのは coursedataのみ )
    // course_fixing_radius2speed();
    //! 一旦速度一定で KCM
    kcm();
    //! FLASH_SECTOR_11 is CourseData
    flash_write(FLASH_SECTOR_11);
  }
  imu_start();
}

void course_stop() {
  if (rotary_read_playmode() == search ||
      rotary_read_playmode() == motor_free) {
    flash_write(FLASH_SECTOR_9);
    flash_write(FLASH_SECTOR_10);
    flash_write(FLASH_SECTOR_11);
  }
  if (rotary_read_playmode() == accel) {
    flash_write(FLASH_SECTOR_11);
  }
  imu_stop();
}

/**
 * @fn course_update_section_degree()
 * @brief コースの角速度を加算していく
 * 好きな時に course_section_degree を読む
 * 好きな時に course_section_degree をリセットする
 * course_update_section_degree() は course_update_section_sampling_time_s
 * の周期で常に実行され続ける
 *
 */
void course_update_section_degree() {
  float tmp;
  imu_update_gyro();
#if D_COURSE_WHILE
  printf("imu_read_yaw() = %7.2lf, course_section_degree = %7.2lf\r\n",
         imu_read_yaw(), course_section_degree);
#endif
  course_sampling_count = course_sampling_count + 1;
  tmp = course_section_degree +
        imu_read_yaw() * course_update_section_sampling_time_s;
  course_section_degree = low_pass_filter(tmp, course_section_degree, 0);
}

void course_set_update_section_freq_ms(unsigned short int samplingtime_ms) {
  course_update_section_sampling_time_s = samplingtime_ms / (float)1000;
}

float course_read_section_degree() { return course_section_degree; }

void course_reset_section_degree() {
  course_sampling_count = 0;
  course_section_degree = 0;
}

void course_reset() {
  course_reset_section_degree();
  section_length_reset();
}

float course_read_curvature_radius() { return course_section_radius; }

uint16_t course_read_state_count() { return course_state_count; }

uint16_t course_read_sampling_count() { return course_sampling_count; }

void course_increment_state_count() { course_state_count++; }

/**
 * @fn course_calclate_radius()
 * @brief 区間の半径を計測する
 * @return float
 * @sa course_state_function()
 * @attention course_state_function() からのみ呼び出される
 * course_calclate_radius()			// 半径の計算
 * course_read_curvature_radius()	// 計算した半径を取得する
 * course_reset()					//
 * 角度と長さ情報をリセットする の順に呼び出す必要がある
 *
 */
void course_calclate_radius() {
  float curvature_radius;
  float section_degree, section_length;
  float section_radian;

  //! 現在の区間長を取得する
  section_length = section_length_read();
  //! 必要な情報をバッファに保存する
  course_data_saving();
  //! 現在点を次の区間開始点に設定する。値のリセットは別でやる
  section_length_set_buffer();
  //! 角度を取得するだけ、値のアップデートやリセットは別で行われる
  section_degree = course_read_section_degree();
  //! 角度を保存する
  course_imu_data_saving();
  //! 長さ情報と角度情報をいっぺんにリセットする
  course_reset();

  /* 極率半径を計算する */
#if MODE_ENCODER_CALCLATE
  curvature_radius = (float)TREAD * (float)((left_length) + (right_length)) /
                     (float)((left_length) - (right_length)) / (float)2;
#endif

#if MODE_IMU_CALCLATE
  course_section_length = // course_section_length_from_imu
#endif

      section_radian = section_degree * M_PI / (float)180;
  curvature_radius = section_length / (float)section_radian;
  course_section_radius = curvature_radius;
}

/**
 * @fn course_state_function()
 * @brief
 * @details
 * 左センサを読んだら、あるいは、一定区間進んだら course_state_function()
 * を実行するようにプログラムする 探索か二次走行かは course_state_function()
 * 関数内で判断する必要がある
 *
 */
void course_state_function() {
  PlayMode pm;
  pm = rotary_read_playmode();
  if (pm == search || pm == motor_free) {
    coursedata.course_state_count_max = course_read_state_count();
    //! 区間長を計算して現在点を次の区間開始点に設定する。区間の角度を取り出す。これら２つから区間半径を計算する。
    course_calclate_radius();
    //! 計算された半径を格納するだけ。アップデートやリセットは別でやる。
    coursedata.radius[course_state_count] = course_read_curvature_radius();
    //! マーカを読んだ場所の記録だけする。値のアップデートやリセットは他でやる。
    coursedata.marker[course_state_count] = length_read();
  }
  if (pm == accel) {
    float fixed_velocity_target;
    // course_calclate_radius() を呼び出していないのでリセットする必要がある
    //! 現在地を区間開始点にする
    section_length_set_buffer();
    fixed_velocity_target = data_speed[course_state_count];
    __course_debug_target_speed__ = fixed_velocity_target;
    velotrace_set_target_direct(fixed_velocity_target);
  }
  course_increment_state_count();
}

void course_d_print() {
#if D_COURSE
  printf("__course_debug_target_speed__ = %2.5f\r\n",
         __course_debug_target_speed__);
#endif
  encoder_d_print();
}

float course_radius2speed(float radius) {
  float speed;
  radius = fabs(radius);
  if (radius < 0.075f)
    speed = 1.000f;
  else if (radius < 0.125f)
    speed = 1.200f;
  else if (radius < 0.175f)
    speed = 1.500f;
  else if (radius < 0.45f)
    speed = 2.00f;
  else if (radius < 0.8f)
    speed = 2.500f;
  else if (radius < 1.5f)
    speed = 2.500f;
  else if (radius < 2.5f)
    speed = 2.500f;
  else
    speed = 2.50f;
  // speed = - (4238566523291511 * pow(radius, 5)) / (double)
  // 633825300114114700748351602688 + (8582934509267735 * pow(radius, 4)) /
  // (double) 77371252455336267181195264 - (1459060547913519 * pow(radius, 3)) /
  // (double) 2361183241434822606848 + (2682365349594497 * pow(radius, 2)) /
  // (double) 2305843009213693952 + (1737420468106149 * radius) / (double)
  // 4503599627370496 + 7057670738269725 / (double) 8796093022208;
  return speed;
}

void course_fixing_radius2speed() {
  float accel_length;
  uint16_t imax;
  imax = coursedata.course_state_count_max;
  /* まず矩形グラフを作成する */
  for (uint16_t course_state_size = imax; course_state_size > 0;
       course_state_size = course_state_size - 1) {
    uint16_t index;
    index = imax - course_state_size;
    data_speed[index] = course_radius2speed(coursedata.radius[index]);
#if D_COURSE
    printf("course_fixing_radius2speed() > rect 矩形グラフ\r\n");
#endif
  }

  float accel_glaph[COURSE_STATE_SIZE];
  float decel_glaph[COURSE_STATE_SIZE];

  accel_glaph[0] = 1;
  decel_glaph[imax] = 20;

  accel_length = (float)COURSE_SAMPLING_LENGTH * course_accel_max;

  /* 加速方向でのこぎりグラフを作成する */
  for (uint16_t course_state_size = imax; course_state_size > 0;
       course_state_size = course_state_size - 1) {
    uint16_t index;
    float v1, v2, vref;
    index = imax - course_state_size;
    v1 = accel_glaph[index];
    v2 = data_speed[index + 1];
    if (v2 > v1) {
      if (accel_length >= pow(v2 - v1, 2)) {
        vref = v2;
      } else {
        vref = sqrt(accel_length) + v1;
      }
    } else {
      vref = v2;
    }
    accel_glaph[index + 1] = vref;
#if D_COURSE
    printf("course_fixing_radius2speed() > accel 加速グラフ\r\n");
#endif
  }

  /* 減速方向でのこぎりグラフを作成する */
  for (uint16_t course_state_size = imax; course_state_size > 0;
       course_state_size = course_state_size - 1) {
    uint16_t index;
    float v2, v3, vref;
    index = course_state_size;
    v3 = decel_glaph[index];
    v2 = data_speed[index - 1];
    if (v2 > v3) {
      if (accel_length >= pow(v3 - v2, 2)) {
        vref = v2;
      } else {
        vref = sqrt(accel_length) + v3;
      }
    } else {
      vref = v2;
    }
    decel_glaph[index - 1] = vref;
#if D_COURSE
    printf("course_fixing_radius2speed() > decel 減速グラフ\r\n");
#endif
  }

  /* 加速方向と減速方向で遅い方の速度を速度値として記憶させる */
  for (uint16_t course_state_size = imax; course_state_size > 0;
       course_state_size = course_state_size - 1) {
    uint16_t index;
    index = imax - course_state_size;
    data_speed[index] = (accel_glaph[index] > decel_glaph[index])
                            ? decel_glaph[index]
                            : accel_glaph[index];
#if D_COURSE
    printf("course_fixing_radius2speed() > speed 速度グラフ\r\n");
    printf("%4d, %7.3f, %7.3f\r\n", index, accel_glaph[index],
           decel_glaph[index]);
#endif
  }
}

void course_print_flash() {
  uint16_t course_state_size;
  course_state_size = COURSE_STATE_SIZE;
  //! print flash contents
  while (switch_read_enter()) {
    if (course_state_size > 0) {
      uint16_t index;
      float print_data_a, print_data_b;
      index = COURSE_STATE_SIZE - course_state_size;
      switch (rotary_read_value()) {
      case 15:
        //! CourseData
        print_data_a = data_speed[index];
        print_data_b = coursedata.radius[index];
        break;
      case 14:
        //! ImuData
        print_data_a = imudata.yaw[index];
        print_data_b = 0.000f;
        break;
      case 13:
        //! EncoderData
        print_data_a = encoderdata.left[index];
        print_data_b = encoderdata.right[index];
        break;
      case 12:
        //! CourseData
        print_data_a = coursedata.marker[index];
        print_data_a = coursedata.course_state_count_max;
      default:
        break;
      }
      printf("%6d, %8lf, %8lf\r\n", index, print_data_a, print_data_b);
      course_state_size = course_state_size - 1;
      HAL_Delay(100);
    } else {
      HAL_Delay(1000);
    }
  }
}

void course_reset_flash() {
  for (uint16_t course_state_size = COURSE_STATE_SIZE; course_state_size > 0;
       course_state_size = course_state_size - 1) {
    uint16_t index;
    index = COURSE_STATE_SIZE - course_state_size;
    data_speed[index] = COURSE_SPEED_DEFAULT;
    coursedata.radius[index] = COURSE_RADIUS_DEFAULT;
    encoderdata.left[index] = 8.888f;
    encoderdata.right[index] = 7.777f;
    imudata.yaw[index] = 6.666f;
  }
}

float accel_max_calc(uint8_t i) {
  return ACCEL_MAX_MAX - ((ACCEL_STEP_SIZE - 1) - i) *
                             (float)(ACCEL_MAX_MAX - ACCEL_MAX_MIN) /
                             (float)(ACCEL_STEP_SIZE - 1);
}

void course_data_saving() {
  uint16_t index;
  index = course_read_state_count();
  encoderdata.left[index] = section_length_read_left();
  encoderdata.right[index] = section_length_read_right();
}

void course_imu_data_saving() {
  uint16_t index;
  index = course_read_state_count();
  imudata.yaw[index] = course_read_section_degree();
}
