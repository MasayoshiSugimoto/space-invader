#include "window_manager_test.h"


const char* _characters = "abcdefghijklmnopqrstuvwxyz0123456789 -.";
int _x = 0;
int _y = 0; 


void _rand_string(char* buffer, int length) {
    int characters_length = strlen(_characters);
    for (int i = 0; i < length; i++) {
        buffer[i] = _characters[rand() % characters_length];
    }
    buffer[length] = 0;
}


int _rand_size() {
    return (rand() % 20) + 1;
}


int _rand_coordinates() {
    return (rand() % 20) + 1;
}


void _print(struct VirtualWindow* window, const char* text) {
    for (int i = 0; text[i] != 0; i++) {
        struct VirtualPixel pixel = {text[i], 0};
        window_manager_window_set_pixel(window, _x++, _y, pixel);
    }
}


void _new_line(struct VirtualWindow* window) {
    _x = 0;
    _y++;
}


struct VirtualWindow* _new_window() {
    struct VirtualWindow* window = window_manager_window_new(_rand_size(), _rand_size());
    window_manager_window_fill_character(window, '*');
    int width = window_manager_window_get_width(window);
    for (int i = 0; i < 500; i++) {
        struct VirtualPixel pixel = {_characters[rand() % strlen(_characters)], 0};
        window_manager_window_set_pixel(window, i % width, i / width, pixel);
    }
    window_manager_window_set_offset_x(window, rand() % virtual_screen_get_width());
    window_manager_window_set_offset_y(window, rand() % virtual_screen_get_height());
    window_manager_window_set_border(window, true);
    return window;
}


void window_manager_test() {
    log_info("TEST: window_manager_test");

    curs_set(CURSOR_VISIBILITY_INVISIBLE);

    int window_max = 16 - 1;
    struct VirtualWindow* windows[window_max];
    int dx[window_max];
    int dy[window_max];
    for (int i = 0; i < window_max; i++) {
        windows[i] = _new_window();
        dx[i] = (rand() % 4) - 2;
        dy[i] = (rand() % 4) - 2;
    }

    struct VirtualWindow* forefront_window = window_manager_window_new(virtual_screen_get_width(), virtual_screen_get_height());
    virtual_window_set_transparency(forefront_window, true);
    _print(forefront_window, "TESTING WINDOW MANAGER");
    _new_line(forefront_window);
    _print(forefront_window, "======================");
    _new_line(forefront_window);
    _print(forefront_window, "Window will move around randomly.");

    struct FrameTimer timer;
    frame_timer_init();
    frame_timer_timer_init(&timer);
    frame_timer_start(&timer, milliseconds_as_duration(5000));
    
    int t = 0;
    while (!frame_timer_is_done(&timer)) {
        frame_timer_on_frame_start();
        int dt = duration_as_milliseconds(frame_timer_get_elapsed_time(&timer)) / 50;
        for (int i = 0; i < window_max; i++) {
            struct VirtualWindow* window = windows[i];
            if (t != dt) {
                window_manager_window_set_offset_x(window, window_manager_window_get_offset_x(window) + dx[i]);
                window_manager_window_set_offset_y(window, window_manager_window_get_offset_y(window) + dy[i]);
            }
            window_manager_window_draw(window);
            if (!window_manager_window_is_inside_screen(window)) {
                window_manager_window_release(window);
                windows[i] = _new_window();
            }
        }
        if (t != dt) {
            t = dt;
        }
        
        window_manager_window_draw(forefront_window);
        virtual_screen_render();
    }
}
