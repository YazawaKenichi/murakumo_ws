#include "slow.h"

PID slow_pid;
PID slow_default_pid;
float slowinglength;
float slow_velocity;
uint8_t slow_enable;
//! スロースタートを始めた点の世界長
float slow_start_point_global_length;
uint8_t slow_started;

void slow_init()
{
    /* slow_init */
    slow_started = 0;
}

void slow_start()
{
    /* slow_start */

    /* 初期設定されている値を一旦保存する */
    PID *slow_default_pid_pointer;
    slow_default_pid_pointer = velotrace_read_values();
    slow_default_pid.target = slow_default_pid_pointer -> target;
    slow_default_pid_pointer = tracer_read_values();
    slow_default_pid.kp = slow_default_pid_pointer->kp;
    slow_default_pid.ki = slow_default_pid_pointer->ki;
    slow_default_pid.kd = slow_default_pid_pointer->kd;

    /* slow 実行時の PID パラメータ */
    slow_pid.target = SLOW_VELOTRACE_TARGET;
    slow_pid.kp = SLOW_TRACE_KP;
    slow_pid.ki = SLOW_TRACE_KI;
    slow_pid.kd = SLOW_TRACE_KD;

    /* 初期化 */
    length_start();
    tracer_start();
    velotrace_start();
    slowinglength = 0;
    slow_enable = 1;
    //! スロースタートを始めたタイミングでの世界長を取り出す
    slow_start_point_global_length = length_read();
}

void slow_stop()
{
    /* slow_stop */
    tracer_stop();
    velotrace_stop();
}

void slow_fin()
{
    /* slow_fin */
}

/**
 * @fn slow_main()
 * @brief 
 * tim10_update() で呼び出される関数
 * これ一つを tim10_update() で実行するだけで slow start / slow stop するようにしたい
 * 
 */
void slow_main()
{
    if(slow_read_enable())
    {
        /* スロースタートに設定した PID パラメータにする */
        slow_set_values(&slow_pid);
        if(length_read() - slow_start_point_global_length >= SLOW_LENGTH)
        {
            /* スロー距離が一定を超えた時 */
            /* 元々指定されていた PID 値に戻す */
            slow_set_values(&slow_default_pid);
            /* スロースタートに設定した PID パラメータに設定されないようにする */
            slow_set_enable(0);
        }
    }
    else
    {
        if(sidesensor_read_markerstate() == stop)
        {
            /* コース終了コードが指定されたとき */
            /* 元々指定されていた PID 値を全てゼロに偽装する */
            slow_default_pid.target = 0;
            slow_default_pid.kp = 0;
            slow_default_pid.ki = 0;
            slow_default_pid.kd = 0;
            /* スロースタートに設定した PID パラメータにする */
            slow_set_enable(1);
        }
    }
}

uint8_t slow_read_enable()
{
    return slow_enable;
}

void slow_set_enable(uint8_t enable_)
{
    /* slow_set_enable */
    slow_enable = enable_ ? 1 : 0;
}

void slow_set_values(PID *_pid)
{
    /* slow_set_values */
    velotrace_set_target_direct(_pid->target);
    tracer_set_gain_direct(_pid->kp, _pid->ki, _pid->kd);
}

float slow_sigmoid(float x)
{
    return sigmoid(x, SLOW_SIGMOID_A, SLOW_LENGTH / 2);
}

void slow_print_default_pid()
{
#if D_SLOW
    // printf("slow > kp = %7.2f, ki = %7.2f, kd = %7.2f\r\n", slow_default_pid.kp, slow_default_pid.ki, slow_default_pid.kd);
    printf("slow > target = %7.2f\r\n", slow_default_pid.target);
#endif
}


