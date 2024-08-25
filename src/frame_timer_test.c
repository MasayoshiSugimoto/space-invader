#include "frame_timer_test.h"


static char _print_buf[512];


static void _print(const char* text) {
  for (const char* c = text; *c != 0; c++) {
    addch(*c);
  }
}


void frame_timer_test() {
    log_info("Testing frame_timer...");

    frame_timer_init();

    struct FrameTimer frame_timer;
    frame_timer_timer_init(&frame_timer);
    frame_timer_start(&frame_timer, milliseconds_as_duration(20000));

    while (true) {
        frame_timer_on_frame_start();

        if (frame_timer_is_done(&frame_timer)) {
            break;
        }

        Duration remaining_timer = frame_timer_remaining_time(&frame_timer);
        float completion_pourcentage = frame_timer_interpolate_linear_f(&frame_timer, 0.0f, 100.0f);

        erase();
        _print("TESTING FRAME TIMER\n");
        _print("===================\n");
        _print("\n");
        sprintf(_print_buf, "This screen will close in %ld seconds.\n", duration_as_second(remaining_timer));
        _print(_print_buf);
        sprintf(_print_buf, "Completion pourcentage: %f.\n", completion_pourcentage);
        _print(_print_buf);
        _print("\n");
        refresh();
    }
}