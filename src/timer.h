/********************************************************************************
 * This file utility for a timer in milliseconds.
 *******************************************************************************/


#ifndef TIMER_H
#define TIMER_H


#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include "log.h"
#include "util.h"


#define duration_as_milliseconds(d) ((d) / 1000000ul)
#define duration_as_second(d) (duration_as_milliseconds(d) / 1000ul)
#define milliseconds_as_duration(m) ((m) * 1000000ul)
#define seconds_as_duration(s) ((s) * 1000000000ul)
#define DURATION_ONE_SECOND milliseconds_as_duration(1000)


typedef uint64_t Instant;
typedef uint64_t Duration;


struct Timer {
  Duration max;
  Duration current;
};


Instant timer_now();
void timer_init(struct Timer* timer, Duration max);
bool timer_update(struct Timer* timer, Duration delta_time);
void timer_update_once(struct Timer* timer, Duration delta_time);
bool timer_is_done(struct Timer* timer);
void timer_reset(struct Timer* timer);
void timer_on_frame_start();
void timer_frame_init();
Duration timer_get_frame_start();
Duration timer_get_frame_duration();
void timer_print(const struct Timer* timer);
float timer_interpolate_linear(const struct Timer* timer, float start, float end);
float timer_interpolate_cos_f(const struct Timer* timer, float start, float end);
void timer_done(struct Timer* timer);


#endif
