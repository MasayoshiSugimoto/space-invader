#include "timer.h"


Instant g_frame_start = 0;
Duration g_frame_duration = 0;


Instant timer_now() {
  struct timespec start;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  return start.tv_sec * 1000000000 + start.tv_nsec;
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


void timer_update_once(struct Timer* timer, Duration delta_time) {
  timer->current += delta_time;
}


bool timer_is_done(struct Timer* timer) {
  return timer->current >= timer->max;
}


void timer_on_frame_start() {
  Instant now = timer_now();
  g_frame_duration = now - g_frame_start;
  g_frame_start = timer_now();
}


void timer_frame_init() {
  g_frame_duration = 0;
  g_frame_start = timer_now();
}


Instant timer_get_frame_start() {
  return g_frame_start;
}


Duration timer_get_frame_duration() {
  return g_frame_duration;
}


void timer_print(const struct Timer* timer) {
  log_info_f("current: %ld, max: %ld", timer->current, timer->max);
}


float timer_interpolate_linear(const struct Timer* timer, float start, float end) {
  return interpolate_linear(timer->current, timer->max, start, end);
}
