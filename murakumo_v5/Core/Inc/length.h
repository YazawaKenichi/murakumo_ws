#include "encoder.h"

void length_set_sampling_time_s(double _sampling_time_s);
void length_init(double _sampling_time_s);
void length_start();
void length_stop();
void length_fin();
double length_read();
double length_read_left();
double length_read_right();
double velocity_read();
void length_update();
