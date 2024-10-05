#include "event.h"


void event_on_start(void) {
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, true);
    notimeout(stdscr, true);
    keypad(stdscr, TRUE);
    srand(time(NULL));

    log_init();
    color_init();
    virtual_screen_init();
    virtual_screen_setup();
    frame_timer_init();
    timer_frame_init();
}


void event_on_frame_start(void) {
    frame_timer_on_frame_start();
}


void event_on_render_start(void) {
    color_update();
    virtual_screen_reset();
}