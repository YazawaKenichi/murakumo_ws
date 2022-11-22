#ifndef __PID_H__
#define __PID_H__

typedef struct
{
    double target;
    double kp;
    double ki;
    double kd;
} PID;

#endif
