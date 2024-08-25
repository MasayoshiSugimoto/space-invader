#include "util.h"


uint64_t get_current_millisecond() {
  struct timespec start;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  return start.tv_sec * 1000 + start.tv_nsec / 1000000;
}


float interpolate_linear(float current, float max, float start, float end) {
  if (max == 0.0f) {
    return end;
  }
  return start + (current / max) * (end - start);
}
