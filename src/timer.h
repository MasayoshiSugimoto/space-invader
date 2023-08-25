/********************************************************************************
 * This file utility for a timer in milliseconds.
 *******************************************************************************/


#ifndef TIMER_H
#define TIMER_H


#include <time.h>
#include <stdint.h>
#include <stdbool.h>


typedef uint64_t Instant;
typedef uint64_t Duration;


struct Timer {
  Duration max;
  Duration current;
};


Instant timer_now();
void timer_init(struct Timer* timer, Duration max);
bool timer_update(struct Timer* timer, Duration delta_time);
void timer_reset(struct Timer* timer);

#endif
