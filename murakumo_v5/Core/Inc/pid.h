#ifndef __PID_H__
#define __PID_H__

typedef struct
{
    float target;
    float kp;
    float ki;
    float kd;
} PID;

#endif
