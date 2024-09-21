#include "window_manager_test.h"


const char* _characters = "abcdefghijklmnopqrstuvwxyz0123456789 -.";


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

    int window_max = 16;
    struct VirtualWindow* windows[window_max];
    int dx[window_max];
    int dy[window_max];
    for (int i = 0; i < window_max; i++) {
        windows[i] = _new_window();
        dx[i] = (rand() % 4) - 2;
        dy[i] = (rand() % 4) - 2;
    }
    
    // for (int i = 0; i < 1000; i++) {
    while (true) {
        for (int i = 0; i < window_max; i++) {
            struct VirtualWindow* window = windows[i];
            window_manager_window_set_offset_x(window, window_manager_window_get_offset_x(window) + dx[i]);
            window_manager_window_set_offset_y(window, window_manager_window_get_offset_y(window) + dy[i]);
            window_manager_window_draw(window);
            if (!window_manager_window_is_inside_screen(window)) {
                window_manager_window_release(window);
                windows[i] = _new_window();
            }
        }
        virtual_screen_render();
        // sleep(1);
    }
    
    // sleep(5);
}
