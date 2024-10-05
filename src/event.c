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

    // start_screen_init();
    screen_setup();
}


void event_on_frame_start(void) {
    frame_timer_on_frame_start();
}


void event_on_render_start(void) {
    color_update();
    virtual_screen_reset();
}


void event_on_game_state_change(enum GameState game_state) {
    switch (game_state) {
        case GAME_STATE_IN_GAME_2:
            screen_setup();
            break;
        case GAME_STATE_START_SCREEN:
            start_screen_init();
            break;
        default:
            // Do nothing
            break;
    }
}