#ifndef __ROTARY_H__
#define __ROTARY_H__

#include "print.h"
#include "defines.h"

#define ROTARY_COUNT 16

typedef enum PLAYMODE
{
    calibration,            /* キャリブレーション */
    search,                 /* 探索走行 */
    accel,                  /* 二次走行 */
    max_enable,             /* 最速走行 */ 
    motor_free,             /* モータの出力をしないまま動作させる */
    tracer_tuning,          /* ライントレースのゲインチューニングが可能 */ 
    velotrace_tuning,       /* 速度制御のゲインチューニングが可能 */
    banquet,                /* 宴会芸 */
    flash_print = 15        /* ROM の内容を標準出力 */
} PlayMode;

void rotary_init();
void rotary_set_playmode();
PlayMode rotary_read_playmode();
void rotary_set_value();
uint8_t rotary_read_value();
uint8_t rotary_read();
void rotary_print_playmode();

#endif
