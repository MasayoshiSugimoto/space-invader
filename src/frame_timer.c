#include "frame_timer.h"


static Instant _last_frame_start;
static Instant _frame_start;


Instant _now() {
  struct timespec start;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  return start.tv_sec * 1000000000 + start.tv_nsec;
}


void frame_timer_init(void) {
    _last_frame_start = _now();
    _frame_start = _last_frame_start;
;
}


void frame_timer_timer_init(struct FrameTimer* frame_timer) {
    memset(frame_timer, 0, sizeof(&frame_timer));
}


// Register time at frame start.
void frame_timer_on_frame_start(void) {
    _last_frame_start = _frame_start;
    _frame_start = _now();
}


bool frame_timer_is_done(struct FrameTimer* frame_timer) {
    return frame_timer->start + frame_timer->duration < _frame_start;
}


void frame_timer_start(struct FrameTimer* frame_timer, Duration duration) {
    frame_timer->start = _frame_start;
    frame_timer->duration = duration;
}


void frame_timer_stop(struct FrameTimer* frame_timer) {
    frame_timer->duration = 0;
}


float frame_timer_interpolate_linear_f(struct FrameTimer* frame_timer, float start, float end) {
    if (frame_timer->duration == 0.0f) return 0.0f;
    // We convert to millisecond to stay accurate in float range.
    uint64_t elapsed_time = imin(_frame_start - frame_timer->start, frame_timer->duration);
    elapsed_time = duration_as_milliseconds(elapsed_time);
    // uint64_t total_duration = duration_as_milliseconds(frame_timer->duration);
    return interpolation_linear_f(
        (float)duration_as_milliseconds(_frame_start),
        (float)duration_as_milliseconds(frame_timer->start),
        (float)duration_as_milliseconds(frame_timer->start + frame_timer->duration),
        start,
        end
    );
}


float frame_timer_interpolate_cos_f(struct FrameTimer* frame_timer, float start, float end) {
    if (frame_timer->duration == 0.0f) return 0.0f;
    // We convert to millisecond to stay accurate in float range.
    uint64_t elapsed_time = imin(_frame_start - frame_timer->start, frame_timer->duration);
    elapsed_time = duration_as_milliseconds(elapsed_time);
    // uint64_t total_duration = duration_as_milliseconds(frame_timer->duration);
    return interpolation_cos_f(
        (float)duration_as_milliseconds(_frame_start),
        (float)duration_as_milliseconds(frame_timer->start),
        (float)duration_as_milliseconds(frame_timer->start + frame_timer->duration),
        start,
        end
    );
}


Duration frame_timer_remaining_time(struct FrameTimer* frame_timer) {
    return imax(frame_timer->start + frame_timer->duration - _frame_start, 0);
}


Duration frame_timer_get_elapsed_time(struct FrameTimer* frame_timer) {
    return _frame_start - frame_timer->start;
}