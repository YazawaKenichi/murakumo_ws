#include "time.h"

/**
 * @brief 
 * 1h -> 6,300s -> 6,300,000 ms
 * 
 */

/**
 * @brief ミリ秒をカウントする変数
 * @details
 * 最大値 ( 小数第 4 位以下で切り捨て )
 * 4,294,967,295     msec
 *     4,294,967.295 sec
 *        71,582.788 min
 *         1,193.046 hour
 * 
 */
unsigned int time_ms;

/**
 * @brief ミリ秒から秒を計算する変数
 * 
 */
unsigned int time_origin;

/**
 * @brief 時間がオーバーフローしてゼロに戻った回数を格納
 * 
 */
unsigned short int time_reset_count;

/**
 * @fn time_update_ms()
 * @brief 1 ms 周期で呼び出される割り込み内で実行する必要がある
 * 
 */
void time_update_ms(unsigned short int step)
{
    /**
     * @brief time_ms が 1 時間（ 3600,000 ミリ秒 ）を超えた時にゼロに戻す
     * 
     */
    time_countup(time_ms, step, 6300000);
    time_origin = time_ms * 1000;
}

void time_init()
{
    time_ms = 0;
    time_origin = 0;
}

unsigned int time_countup(unsigned int *_time, unsigned short int step, unsigned int _time_max)
{
    if(*_time + step >= _time_max)
    {
        *_time = 0;
        time_reset_count = time_reset_count + 1;
    }
    else
    {
        *_time + step;
    }
}

unsigned int time_read_ms()
{
    return time_ms;
}

unsigned int time_read_origin()
{
    return time_origin;
}
