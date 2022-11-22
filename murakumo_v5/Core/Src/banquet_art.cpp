#if false

#define <banquet_art.hpp>

PID::PID()
{
	before = 0;
	target = 0;
	offset = 0;
	period = 1;
}

template <typename Type>
PID::PID(Type _before = 0, Type _target = 0, Type _offset = 0, Type _period = 1)
{
	before = _before;
	target = _target;
	offset = _offset;
	period = _period;
}

template <typename Type>
double PID::result(Type _current)
{
	before = current;
	current = _current;
	error_before = error;
	error = current - before;
	error_integral += error;

	return (double) kp * error + (double) kd * (error - error_before) / period + (double) ki * error_integral * period;
}

void PID::set_gain(double _kp = 0, double _kd = 0, double _ki = 0)
{
	kp = _kp;
	kd = _kd;
	ki = _ki;
}

#endif
