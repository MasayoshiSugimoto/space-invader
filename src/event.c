#include "event.h"


void event_on_program_start(void) {
    log_init();
    log_info("Executing program initialization sequence.");
    srand(time(NULL));
    if (!DEBUG_NO_SCREEN_OUTPUT) {
        initscr();
        noecho();
        cbreak();
        nodelay(stdscr, true);
        notimeout(stdscr, true);
        keypad(stdscr, TRUE);
        color_init();
    }

    main_system_mode_set(&g_game_main_system_mode);
    // main_system_mode_set(&g_start_screen_main_system_mode);
    // main_system_mode_set(&g_main_system_mode_sprite_editor_2);
    // main_system_mode_set(&g_collision_manager_test);
    // main_system_mode_set(&g_entity_spaceship_test);
    // main_system_mode_set(&g_animation_test);
    main_system_mode_set(&g_main_system_sequence);
}


void event_on_system_start(void) {
    log_info("Executing system initialization sequence.");
    color_color_set_default();
    virtual_screen_init();
    virtual_screen_allocate();
    frame_timer_init();
    timer_frame_init();
    
    sprite_loader_init();

    collision_manager_init();
    collision_manager_allocate(SCREEN_WIDTH, SCREEN_HEIGHT);
}


void event_on_frame_start(void) {
    terminal_check_minimum_size();
    frame_timer_on_frame_start();
}


void event_on_render_start(void) {
    color_update();
    erase();
}


void event_on_render_end(void) {
    refresh();
}


void event_on_system_release(void) {
    log_info("Executing system release sequence.");
    collision_manager_release();
    sprite_loader_release();
    virtual_screen_release();
}


void event_on_program_shutdown(void) {
    log_info("Executing program shutdown sequence.");
    if (!DEBUG_NO_SCREEN_OUTPUT) {
        endwin();  // End ncurses.
    }
}