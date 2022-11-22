#include "function.h"

double low_pass_filter(double val, double pre_val, double gamma)
{
	return (double) (gamma * (double) pre_val
			+ (double) (1 - gamma) * (double) val);
}

#ifndef __OBSOLETE_MATH
double pow(double a, double b) {
	double r;
	r = 1;
	// printf("pow(%5.3f, %5.3f)\r\n", a, b);
	if(b < 0)
	{
		for(int i = -b; i > 0; i--) // xx b != int xx
		{
			r = (double) r / a;
		}
	}
	else
	{
		for(int i = b; i > 0; i--)
		{
			r = (double) r * a;
		}
	}

	return r;
}

double exp(double a)
{
	// printf("exponential(%5.3f)\r\n", a);
	return pow(E, a);
}
#endif

double sigmoid(double x, double a, double x0) {
	// printf("pow(%5.3f, %5.3f, %5.3f)\r\n", x, a, x0);
	return 1 / (double) (1 + exp(-a * (x - x0)));
}

