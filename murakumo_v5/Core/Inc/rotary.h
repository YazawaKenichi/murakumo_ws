#ifndef __ROTARY_H__
#define __ROTARY_H__

#include "print.h"
#include "stm32f4xx_hal.h"

#define ROTARY_COUNT 16

typedef enum PLAYMODE
{
    calibration,            /*  0. キャリブレーション */
    search,                 /*  1. 探索走行 */
    accel,                  /*  2. 二次走行 */
    max_enable,             /*  3. 最速走行 */ 
    motor_free,             /*  4. モータの出力をしないまま動作させる */
    tracer_tuning,          /*  5. ライントレースのゲインチューニングが可能 */ 
    velotrace_tuning,
    velotrace_left_tuning,       /*  6. 速度制御のゲインチューニングが可能 */
    velotrace_right_tuning,       /*  6. 速度制御のゲインチューニングが可能 */
    velotrace_tuning_2,
    velotrace_left_tuning_2,     /*  7. 速度制御のゲインチューニングが可能 */
    velotrace_right_tuning_2,     /*  7. 速度制御のゲインチューニングが可能 */
    angletrace_tuning,      /*  8. 角度制御のゲインチューニングが可能 */
    kcm_tester, /* 9. KCM の実行 */
    banquet,                /*  10. 宴会芸 */
    tuning,                 /* 11. センサのチューニングをするときのモード*/
    flash_print = 15        /* 15. ROM の内容を標準出力 */
} PlayMode;

void rotary_init();
void rotary_start();
void rotary_stop();

void rotary_update();

uint8_t rotary_read();
PlayMode rotary_read_playmode();

void rotary_set_value();
void rotary_set_playmode();

void rotary_print_playmode();

#endif
