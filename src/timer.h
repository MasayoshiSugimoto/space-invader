/********************************************************************************
 * This file utility for a timer in milliseconds.
 *******************************************************************************/


#ifndef TIMER_H
#define TIMER_H


#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include "log.h"


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


#endif
