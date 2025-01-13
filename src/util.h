#ifndef UTIL_H
#define UTIL_H


#include <time.h>
#include <stdint.h>


#define PI 3.14159265359


#define array_size(arr) (sizeof(arr) / sizeof(arr[0]))

#define boolean_as_string(b) b ? "true" : "false"

#define imin(a, b) a < b ? a : b
#define imax(a, b) a < b ? b : a
#define iclamp(low, value, high) value < low ? low : (value > high ? high : value)


uint64_t get_current_millisecond();


float interpolate_linear(float current, float max, float start, float end);


#endif