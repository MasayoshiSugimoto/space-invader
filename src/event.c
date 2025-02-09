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
    arena_frame_create();

    main_system_mode_set(&g_main_system_sequence);
    if (TEST_MODE == TEST_MODE_GAME_MODE_SEQUENCE) {
        main_system_mode_set(&g_main_system_sequence);
    } else if (TEST_MODE == TEST_MODE_SPRITE_EDITOR) {
        main_system_mode_set(&g_main_system_mode_sprite_editor_2);
    }
}


void event_on_system_start(void) {
    log_info("Executing system initialization sequence.");
    arena_system_create();
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
    arena_frame_reset();
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
    arena_system_release();
}


void event_on_program_shutdown(void) {
    log_info("Executing program shutdown sequence.");
    arena_frame_release();
    if (!DEBUG_NO_SCREEN_OUTPUT) {
        endwin();  // End ncurses.
    }
}