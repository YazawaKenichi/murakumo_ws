#ifndef __SLOW_H__
#define __SLOW_H__

#include "tim10.h"
#include "pid.h"

#define SLOW_LENGTH 300

#define THREE_SIGMA 0.9976f

#define SLOW_SIGMOID_X0 (SLOW_LENGTH / 2)
#define SLOW_SIGMOID_A  (13 / SLOW_LENGTH)

#endif
