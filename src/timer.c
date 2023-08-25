#include "timer.h"


Instant timer_now() {
  struct timespec start;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  return start.tv_sec * 1000 + start.tv_nsec / 1000000;
}


void timer_init(struct Timer* timer, Duration max) {
  timer->max = max;
  timer->current = 0;
}


bool timer_update(struct Timer* timer, Duration delta_time) {
  timer->current += delta_time;
  if (timer->current < timer->max) return false;
  timer->current = 0;
  return true;
}
