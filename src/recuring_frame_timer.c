#include "recuring_frame_timer.h"


void recurring_frame_timer_set(struct RecuringFrameTimer* timer, void (*on_time_out)(void*), void* param, Duration frequency) {
    frame_timer_timer_init(&timer->timer);
    frame_timer_start(&timer->timer, RECURING_FRAME_TIMER_RESET_DURATION);
    timer->on_time_out = on_time_out;
    timer->param = param;
    timer->frequency = frequency;
    timer->divisor = 0;
}


void recurring_frame_timer_update(struct RecuringFrameTimer* timer) {
    int divisor = 
        timer->frequency != 0
        ? frame_timer_get_elapsed_time(&timer->timer) / timer->frequency
        : 0;
    if (divisor != timer->divisor) {
        timer->on_time_out(timer->param);
        timer->divisor = divisor;
    }
}