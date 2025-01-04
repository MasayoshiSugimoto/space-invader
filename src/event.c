#include "event.h"


void event_on_start(void) {
    log_init();
    log_info("Launching program initialization sequence...");
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, true);
    notimeout(stdscr, true);
    keypad(stdscr, TRUE);
    srand(time(NULL));

    color_init();
    color_color_set_default();
    virtual_screen_init();
    virtual_screen_allocate();
    frame_timer_init();
    timer_frame_init();

    sprite_init();
    sprite_loader_init();
    sprite_loader_load_sprite_set(SPRITE_LOADER_SPRITE_SET_LEVEL_1);
    screen_init(screen_get_screen());

    collision_manager_init();
    collision_manager_allocate(SCREEN_WIDTH, SCREEN_HEIGHT);

    main_system_mode_set(&g_game_main_system_mode);
    // main_system_mode_set(&g_start_screen_main_system_mode);
    // main_system_mode_set(&g_main_system_mode_sprite_editor_2);
    main_system_mode_set(&g_collision_manager_test);
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


void event_on_end(void) {
    log_info("Launching ending sequence...");
    endwin();  // End ncurses.
}