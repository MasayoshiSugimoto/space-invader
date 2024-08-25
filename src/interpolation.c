#include "interpolation.h"

// f(-1) = p[0]
// f(0) = p[1]
// f(1) = p[2]
// f(2) = p[3]
static double _cubicInterpolate(double p[4], double x) {
	return p[1] + 0.5 * x*(p[2] - p[0] + x*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + x*(3.0*(p[1] - p[2]) + p[3] - p[0])));
}


float interpolation_linear_f(float input_current, float input_start, float input_end, float output_start, float output_end) {
    return output_start + ((input_current - input_start) / (input_end - input_start)) * (output_end - output_start);
}


float interpolation_cubic_f(float input_current, float input_start, float input_end, float output_start, float output_end) {
    double p[4] = {output_start, output_start, output_start + (output_end - output_start) / 2.0f, output_end};
    double v = -1.0l + ((input_current - input_start) / (input_end - input_start) * 3.0f);
    return _cubicInterpolate(p, v);
}