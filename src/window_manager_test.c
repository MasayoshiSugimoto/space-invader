#include "window_manager_test.h"


const char* _characters = "abcdefghijklmnopqrstuvwxyz0123456789 -.";
int _x = 0;
int _y = 0; 


static void _init(void) {
    _x = 0;
    _y = 0;
}


void _rand_string(char* buffer, int length) {
    int characters_length = strlen(_characters);
    for (int i = 0; i < length; i++) {
        buffer[i] = _characters[rand() % characters_length];
    }
    buffer[length] = 0;
}


int _rand_size(void) {
    return (rand() % 20) + 1;
}


int _rand_coordinates(void) {
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


struct VirtualWindow* _new_window(void) {
    struct VirtualWindow* window = window_manager_window_new(_rand_size(), _rand_size());
    window_manager_window_fill_character(window, '*');
    for (int i = 0; i < 500; i++) {
        struct VirtualPixel pixel = {_characters[rand() % strlen(_characters)], 0};
        window_manager_window_set_pixel(window, i % window->width, i / window->width, pixel);
    }
    window->offset_x = rand() % virtual_screen_get_width();
    window->offset_y = rand() % virtual_screen_get_height();
    window->has_border = true;
    return window;
}


void window_manager_test_random() {
    log_info("TEST: window_manager_test_random");

    window_manager_init();
    _init();
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
    forefront_window->is_transparent = true;
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
        event_on_render_start();
        frame_timer_on_frame_start();
        int dt = duration_as_milliseconds(frame_timer_get_elapsed_time(&timer)) / 50;
        for (int i = 0; i < window_max; i++) {
            struct VirtualWindow* window = windows[i];
            if (t != dt) {
                window->offset_x += dx[i];
                window->offset_y += dy[i];
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
        event_on_render_end();
    }

    window_manager_window_release_all();
}


void window_manager_test_alignment() {
    log_info("TEST: window_manager_test_alignment");

    window_manager_init();
    _init();
    curs_set(CURSOR_VISIBILITY_INVISIBLE);

    struct VirtualWindow* forefront_window = window_manager_window_new(virtual_screen_get_width(), virtual_screen_get_height());
    forefront_window->is_transparent = true;
    _print(forefront_window, "TESTING WINDOW MANAGER ALIGNMENT");
    _new_line(forefront_window);
    _print(forefront_window, "================================");
    _new_line(forefront_window);
    _print(forefront_window, "Testing different window alignment relative to the screen.");

    int width = 10;
    int height = 5;

    struct VirtualWindow* window_top_left = window_manager_window_new(width, height);
    window_top_left->has_border = true;
    window_manager_window_align_left_screen(window_top_left);
    window_manager_window_align_top_screen(window_top_left);

    struct VirtualWindow* window_top_center = window_manager_window_new(width, height);
    window_top_center->has_border = true;
    window_manager_window_center_screen_x(window_top_center);
    window_manager_window_align_top_screen(window_top_center);

    struct VirtualWindow* window_top_right = window_manager_window_new(width, height);
    window_top_right->has_border = true;
    window_manager_window_align_right_screen(window_top_right);
    window_manager_window_align_top_screen(window_top_right);

    struct VirtualWindow* window_center_left = window_manager_window_new(width, height);
    window_center_left->has_border = true;
    window_manager_window_align_left_screen(window_center_left);
    window_manager_window_center_screen_y(window_center_left);

    struct VirtualWindow* window_center_center = window_manager_window_new(width, height);
    window_center_center->has_border = true;
    window_manager_window_center_screen_x(window_center_center);
    window_manager_window_center_screen_y(window_center_center);

    struct VirtualWindow* window_center_right = window_manager_window_new(width, height);
    window_center_right->has_border = true;
    window_manager_window_align_right_screen(window_center_right);
    window_manager_window_center_screen_y(window_center_right);

    struct VirtualWindow* window_bottom_left = window_manager_window_new(width, height);
    window_bottom_left->has_border = true;
    window_manager_window_align_left_screen(window_bottom_left);
    window_manager_window_align_bottom_screen(window_bottom_left);

    struct VirtualWindow* window_bottom_center = window_manager_window_new(width, height);
    window_bottom_center->has_border = true;
    window_manager_window_center_screen_x(window_bottom_center);
    window_manager_window_align_bottom_screen(window_bottom_center);

    struct VirtualWindow* window_bottom_right = window_manager_window_new(width, height);
    window_bottom_right->has_border = true;
    window_manager_window_align_right_screen(window_bottom_right);
    window_manager_window_align_bottom_screen(window_bottom_right);

    event_on_render_start();
    window_manager_window_draw(window_top_left);
    window_manager_window_draw(window_top_center);
    window_manager_window_draw(window_top_right);
    window_manager_window_draw(window_center_left);
    window_manager_window_draw(window_center_center);
    window_manager_window_draw(window_center_right);
    window_manager_window_draw(window_bottom_left);
    window_manager_window_draw(window_bottom_center);
    window_manager_window_draw(window_bottom_right);
    window_manager_window_draw(forefront_window);
    virtual_screen_render();
    event_on_render_end();
    sleep(5);

    window_manager_window_release_all();
}


void window_manager_test() {
    window_manager_test_alignment();
    window_manager_test_random();
}
