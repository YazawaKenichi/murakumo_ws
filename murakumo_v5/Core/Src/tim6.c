#include "tim6.h"

#if D_TIM6
double leftmotor, rightmotor;
#endif

void tim6_init()
{
    motor_init();
    // sidesensor_init();
    HAL_TIM_Base_Stop_IT(&htim6);
}

void tim6_start()
{
    printf("motor_start()\r\n");
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
}

void tim6_main()
{
    #if !D_TIM6
    double leftmotor, rightmotor;
    #endif
    SideSensorState markerstate;
    PlayMode playmode;

    playmode = rotary_read_playmode();

    //! コース状態の把握
    //! ここ以降 sidesensor_read_markerstate() で読みだせる
    sidesensor_main();
    //! 格納されるのは直前のマーカの状態であり、区間中はリセットされないことに注意すべし！
    markerstate = sidesensor_read_markerstate();

    if(motor_read_enable())
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

    if(playmode == motor_free)
    {
        leftmotor = 0;
        rightmotor = 0;
    }

    switch(markerstate)
    {
        case curve:
            course_state_function();
            break;
        case stop:
            switch_reset_enter();
            tim6_stop();
            motor_set(leftmotor, rightmotor);
            break;
        default:
            motor_set(leftmotor, rightmotor);
            break;
    }
}

void tim6_d_print()
{
    #if D_TIM6
    printf("tim6.c > tim6_d_print() > leftmotor = %5.3f, rightmotor = %5.3f\r\n", leftmotor, rightmotor); 
    printf("tim6.c > tim6_d_print() > sidesensor_d_print() > ");
    sidesensor_d_print();
    #endif
}
