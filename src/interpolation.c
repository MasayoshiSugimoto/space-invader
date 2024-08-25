#include "interpolation.h"

// f(-1) = p[0]
// f(0) = p[1]
// f(1) = p[2]
// f(2) = p[3]
// static double _cubicInterpolate(double p[4], double x) {
// 	return p[1] + 0.5 * x*(p[2] - p[0] + x*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + x*(3.0*(p[1] - p[2]) + p[3] - p[0])));
// }


float interpolation_linear_f(float input_current, float input_start, float input_end, float output_start, float output_end) {
    return output_start + ((input_current - input_start) / (input_end - input_start)) * (output_end - output_start);
}


float interpolation_cos_f(float input_current, float input_start, float input_end, float output_start, float output_end) {
    float input_interval = input_end - input_start;
    float input_current_ratio = ((input_current - input_start) / input_interval);
    float output_ratio = (cosf(PI + (input_current_ratio * PI)) + 1.0f) / 2.0f;
    return output_start + output_ratio * (output_end - output_start);
}