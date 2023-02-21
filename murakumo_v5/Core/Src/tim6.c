#include "tim6.h"

#if D_TIM6
float leftmotor, rightmotor;
#endif

SideSensorState tim6_markerstate_before;
uint8_t debug_num;

void tim6_init()
{
    motor_init();
    virtual_marker_init();
    HAL_TIM_Base_Stop_IT(&htim6);
    debug_num = 0;
}

void tim6_start()
{
#if D_TIM6
    leftmotor = 0;
    rightmotor = 0;
#endif
    virtual_marker_start();
    fixed_section_start();
    motor_start();
	HAL_TIM_Base_Start_IT(&htim6);	// PID
    debug_num += 0b1;
}

void tim6_stop()
{
    motor_stop();
	HAL_TIM_Base_Stop_IT(&htim6);
    course_stop();
    virtual_marker_stop();
    debug_num += 0b10;
}

void tim6_main()
{
    #if !D_TIM6
    float leftmotor, rightmotor;
    #endif
    SideSensorState markerstate;
    SideSensorState markerstate_volatile;
    PlayMode playmode;

    playmode = rotary_read_playmode();

    //! コース状態の把握
    //! ここ以降 virtual_marker_read_markerstate() / virtual_marker_read_markerstate_volatile() で読みだせる
    virtual_marker_main();
    //! 格納されるのは直前のマーカの状態であり、区間中はリセットされないことに注意すべし！
    markerstate = virtual_marker_read_markerstate();
    //! 格納されるのは現在マーカを読んだか読んでないか、次に virtual_marker_main() が来た時に変化することに注意
    markerstate_volatile = virtual_marker_read_markerstate_volatile();

    debug_num = 0;
    debug_num += 0b100;
    if(motor_read_enable() && playmode != motor_free)
    {
        #if !(TRACER_TUNING || VELOTRACE_TUNING)
        switch(playmode)
        {
            case tracer_tuning:
                leftmotor   = 0 + tim7_read_left();
                rightmotor  = 0 + tim7_read_right();
                debug_num += 0b1000;
                break;
            case velotrace_tuning:
                leftmotor   = tim10_read_left() + 0;
                rightmotor  = tim10_read_right() + 0;
                debug_num += 0b10000;
                break;
            default:
                leftmotor   = tim10_read_left() + tim7_read_left();
                rightmotor  = tim10_read_right() + tim7_read_right();
                debug_num += 0b100000;
                break;
        }
        #else
        #if TRACER_TUNING
        leftmotor  =  tim7_read_left();
        rightmotor = tim7_read_right();
        #endif
        #if VELOTRACE_TUNING
        leftmotor  =  tim10_read_left();
        rightmotor = tim10_read_right();
        #endif
        #if VELOTRACE_TUNING && TRACER_TUNING
        leftmotor  =  tim10_read_left() +  tim7_read_left();
        rightmotor = tim10_read_right() + tim7_read_right();
        #endif
		#endif	/* !(TRACER_TUNING || VELOTRACE_TUNING) */
    }
    else
    {
        leftmotor = 0;
        rightmotor = 0;
        debug_num += 0b1000000;
    }

#if LEFT_MARKER_RADIUS
    //! 一定区間で切るプログラムにするときはいらなくなる処理
    //! 今度は tim10 とかに course_state_function() をいれる必要が出てくる
    if(playmode == search)
    {
        if(markerstate_volatile == curve || markerstate_volatile == stop || markerstate_volatile == cross)
        {
            course_state_function();
        }
    }
    else if(playmode == accel)
    {
        uint16_t marker_state_tmp;
        marker_state_tmp = course_read_state_count();
        if(flashbuffer.marker[marker_state_tmp] - length_read() <= CURVE_MARGIN_LENGTH)
        {
            if(analog_sensor_get(14) <= CURVE_MARGIN_THRESHOLD && analog_sensor_get(15) <= CURVE_MARGIN_THRESHOLD)
            {
                //! ストレートに入ったとき
                course_state_function();
            }
            else
            {
                /* ストレートに入ってない間 */
            }
        }
    }
#else
    //! 距離が COURSE_SAMPLING_LENGTH になっていたら course_state_function() を実行する関数
    fixed_section_main();
#endif

    switch(markerstate)
    {
        case stop:
            switch_reset_enter();
            tim6_stop();
            motor_set(0, 0);
            break;
        default:
            debug_num += 0b10000000;
            motor_set(leftmotor, rightmotor);
            break;
    }

    tim6_markerstate_before = markerstate;
}

void tim6_d_print()
{
    #if D_TIM6
    printf("tim6.c > debug_num = ");
    print_bin(debug_num);
    printf("\r\n");
    printf("tim6.c > tim6_d_print() > motor_enable = %1d, leftmotor = %5.3f, rightmotor = %5.3f\r\n", motor_read_enable(), leftmotor, rightmotor); 
    #endif
    virtual_marker_d_print();
}
