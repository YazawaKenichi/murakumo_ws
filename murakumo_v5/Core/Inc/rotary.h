#ifndef __ROTARY_H__
#define __ROTARY_H__

#include "print.h"
#include "stm32f4xx_hal.h"

#define ROTARY_COUNT 16

typedef enum PLAYMODE
{
    /**
     * 0. キャリブレーション
     * 1. 探索
     * 2. ショートカット
     * 3. 加減速
     * 4. モータフリー
     * F. 標準出力
     */
    pm_calibration,
    pm_explore,
    pm_shortcut,
    pm_accel,
    pm_free,
    pm_print = 15
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
