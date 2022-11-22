#if false

#ifndef __BANQUET_ART_HPP__
#define __BANQUET_ART_HPP__

template <typename Type>
class PID
{
	Type current;
	Type before;
	Type target;
	Type error;
	double error_before;
	double error_integral;
	Type offset;
	uint16_t period;

	double kp;
	double kd;
	double ki;

	PID();
	PID(Type, Type, Type, Type);

	double result(Type _current);
};

#endif
#endif
