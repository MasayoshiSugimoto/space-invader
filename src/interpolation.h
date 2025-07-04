#ifndef INTERPOLATION_H
#define INTERPOLATION_H


#include <math.h>
#include <stdint.h>
#include "util.h"


float interpolation_linear_f(float input_current, float input_start, float input_end, float output_start, float output_end);
float interpolation_cos_f(float input_current, float input_start, float input_end, float output_start, float output_end);


#endif