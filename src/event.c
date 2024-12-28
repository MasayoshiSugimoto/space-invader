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
    color_color_set_default();
    virtual_screen_init();
    virtual_screen_setup();
    frame_timer_init();
    timer_frame_init();

    sprite_init();
    screen_init(screen_get_screen());

    main_system_mode_set(&g_game_main_system_mode);
    main_system_mode_set(&g_start_screen_main_system_mode);
}


void event_on_frame_start(void) {
    terminal_check_minimum_size();
    frame_timer_on_frame_start();
}


void event_on_render_start(void) {
    color_update();
    virtual_screen_reset();
    erase();
}


void event_on_render_end(void) {
    refresh();
}