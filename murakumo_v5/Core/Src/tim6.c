#include "tim6.h"

#if D_TIM6
float leftmotor, rightmotor;
#endif

SideSensorState tim6_markerstate_before;

void tim6_init()
{
    motor_init();
    // sidesensor_init();
    HAL_TIM_Base_Stop_IT(&htim6);
}

void tim6_start()
{
    #if D_TIM6
    leftmotor = 0;
    rightmotor = 0;
    #endif
    sidesensor_start();
    motor_start();
	HAL_TIM_Base_Start_IT(&htim6);	// PID
}

void tim6_stop()
{
    motor_stop();
	HAL_TIM_Base_Stop_IT(&htim6);
    sidesensor_stop();
    course_stop();
}

void tim6_main()
{
    #if !D_TIM6
    float leftmotor, rightmotor;
    #endif
    SideSensorState markerstate;
#if LEFT_MARKER_RADIUS
    SideSensorState markerstate_volatile;
#endif
    PlayMode playmode;

    playmode = rotary_read_playmode();

    //! コース状態の把握
    //! ここ以降 sidesensor_read_markerstate() / sidesensor_read_markerstate_volatile() で読みだせる
    sidesensor_main();
    //! 格納されるのは直前のマーカの状態であり、区間中はリセットされないことに注意すべし！
    markerstate = sidesensor_read_markerstate();
#if LEFT_MARKER_RADIUS
    //! 格納されるのは現在マーカを読んだか読んでないか、次に sidesensor_main() が来た時に変化することに注意
    markerstate_volatile = sidesensor_read_markerstate_volatile();
#endif

    if(motor_read_enable() && playmode != motor_free)
    {
        #if !(TRACER_TUNING || VELOTRACE_TUNING)
        switch(playmode)
        {
            case tracer_tuning:
                leftmotor   = 0 + tim7_read_left();
                rightmotor  = 0 + tim7_read_right();
                break;
            case velotrace_tuning:
                leftmotor   = tim10_read_left() + 0;
                rightmotor  = tim10_read_right() + 0;
                break;
            default:
                leftmotor   = tim10_read_left() + tim7_read_left();
                rightmotor  = tim10_read_right() + tim7_read_right();
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
    }

#if LEFT_MARKER_RADIUS
    //! 一定区間で切るプログラムにするときはいらなくなる処理
    //! 今度は tim10 とかに course_state_function() をいれる必要が出てくる
    if(markerstate_volatile == curve)
    {
        course_state_function();
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
            motor_set(leftmotor, rightmotor);
            break;
        default:
            motor_set(leftmotor, rightmotor);
            break;
    }

    tim6_markerstate_before = markerstate;
}

void tim6_d_print()
{
    #if D_TIM6
    printf("tim6.c > tim6_d_print() > leftmotor = %5.3f, rightmotor = %5.3f\r\n", leftmotor, rightmotor); 
    printf("tim6.c > tim6_d_print() > sidesensor_d_print() > ");
    #endif
    sidesensor_d_print();
}
