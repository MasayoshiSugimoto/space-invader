#ifndef FRAME_TIMER_H
#define FRAME_TIMER_H


#include "timer.h"
#include <curses.h>
#include <ncurses.h>
#include "interpolation.h"


#define DURATION_ONE_DAY (milliseconds_as_duration(1000 * 60 * 60 * 24))


struct FrameTimer {
    Instant start;
    Duration duration;
};


void frame_timer_init(void);
void frame_timer_timer_init(struct FrameTimer* frame_timer);
void frame_timer_on_frame_start(void);  // Register time at frame start.
bool frame_timer_is_done(struct FrameTimer* frame_timer);
void frame_timer_start(struct FrameTimer* frame_timer, Duration duration);
void frame_timer_stop(struct FrameTimer* frame_timer);
float frame_timer_interpolate_linear_f(struct FrameTimer* frame_timer, float start, float end);
float frame_timer_interpolate_cos_f(struct FrameTimer* frame_timer, float start, float end);
Duration frame_timer_remaining_time(struct FrameTimer* frame_timer);
Duration frame_timer_get_elapsed_time(struct FrameTimer* frame_timer);


#endif
