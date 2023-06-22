/**
 * @file twistlist.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-12
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#include "twistlist.h"

Twist twistlist[COURSE_STATE_SIZE];

/**
 * @brief twistlist を生成する
 * 
 */
void generate_twistlist()
{
    for(int index = 0; index < COURSE_STATE_SIZE; index++)
    {
        //! 単位 [ m / s ]
        float v = 1;
        //! 単位 [ rad / s ]
        float w = 0;
        Twist q;
        static const uint8_t desk_sec = 10;
        static const float desk_course_length = 2 * 60 / (float) 5 * M_PI * 1 / (float) 4 * 2;
        v = desk_course_length / (float) desk_sec;
        w = 2 * M_PI * 3 / 4 / (float) desk_sec;
        if(desk_course_length / 2 <= COURSE_SAMPLING_LENGTH * index)
        {
            w *= -1;
        }
        else if(desk_course_length < COURSE_SAMPLING_LENGTH * index)
        {
            v = 0;
            w = 0;
        }
        q.linear.x = v;
        q.linear.y = 0;
        q.linear.z = 0;
        q.angular.x = 0;
        q.angular.y = 0;
        q.angular.z = w;
        twistlist[index] = q;
    }
}

Twist get_twistlist()
{
    return twistlist[course_read_state_count()];
}

