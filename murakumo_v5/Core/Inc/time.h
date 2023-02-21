#ifndef __TIME_H__
#define __TIME_H__

void time_update_ms(unsigned short int step);
void time_init();
void time_countup(unsigned int *_time, unsigned short int step, unsigned int _time_max);
unsigned int time_read_ms();
unsigned int time_read_origin();

#endif
