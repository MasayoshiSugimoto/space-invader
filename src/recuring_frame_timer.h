#ifndef RECURING_FRAME_TIMER_H
#define RECURING_FRAME_TIMER_H


#include "timer.h"
#include "frame_timer.h"


#define RECURING_FRAME_TIMER_RESET_DURATION (milliseconds_as_duration(1000 * 60 * 60 * 24))  // One day


/*
Frequency Must be greater than a frame considering the update is called each frame.
*/
struct RecuringFrameTimer {
    struct FrameTimer timer;
    void (*on_time_out)(void*);
    void* param;
    Duration frequency;
    int divisor;
};


void recurring_frame_timer_set(struct RecuringFrameTimer* timer, void (*on_time_out)(void*), void* param, Duration frequency);
void recurring_frame_timer_update(struct RecuringFrameTimer* timer);


#endif