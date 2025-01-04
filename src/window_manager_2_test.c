#include "window_manager_2_test.h"


#define WINDOW_MANAGER_TEST_SPRITE_BUFFER_COUNT 16
#define WINDOW_MANAGER_TEST_FOREFRONT_INDEX WINDOW_MANAGER_TEST_SPRITE_BUFFER_COUNT
#define WINDOW_MANAGER_TEST_TOTAL_WINDOW_COUNT (WINDOW_MANAGER_TEST_SPRITE_BUFFER_COUNT + 1)


static const char* _characters = "abcdefghijklmnopqrstuvwxyz0123456789 -.";
static struct SpriteBuffer _sprite_buffers[WINDOW_MANAGER_TEST_TOTAL_WINDOW_COUNT];
static struct VirtualWindow2 _windows[WINDOW_MANAGER_TEST_TOTAL_WINDOW_COUNT];
static int _x;
static int _y;
static char _debug_buffer[2048];


static int _rand_size(void) {
    return (rand() % 20) + 1;
}


static void _init(void) {
    _x = 0;
    _y = 0;
}


static void _release(void) {
    for (int i = 0; i < WINDOW_MANAGER_TEST_TOTAL_WINDOW_COUNT; i++) {
        sprite_buffer_free(&_sprite_buffers[i]);
    }
}


static void _print_ln(struct SpriteBuffer* sprite_buffer, const char* text) {
    for (int i = 0; text[i] != 0; i++) {
        struct VirtualPixel* pixel = sprite_buffer_access(sprite_buffer, i, _y);
        pixel->character = text[i];
        pixel->color_pair_id = COLOR_COLOR_PAIR_ID_DEFAULT;
    }
    _y++;
}


static void _random_fill(struct SpriteBuffer* sprite_buffer) {
    int length = strlen(_characters);
    for (int x = 0; x < sprite_buffer_get_width(sprite_buffer); x++) {
        for (int y = 0; y < sprite_buffer_get_height(sprite_buffer); y++) {
            sprite_buffer_access(sprite_buffer, x, y)->character = _characters[rand() % length];
        }
    }
}


static void _set_random_position(struct VirtualWindow2* window) {
    window->offset_x = rand() % virtual_screen_get_width();
    window->offset_y = rand() % virtual_screen_get_height();
}


static void window_manager_test_random() {
    log_info("TEST: window_manager_test_2_random");

    _init();

    struct SpriteBuffer* forefront_sprite_buffer = &_sprite_buffers[WINDOW_MANAGER_TEST_FOREFRONT_INDEX];
    sprite_buffer_allocate(forefront_sprite_buffer, virtual_screen_get_width(), virtual_screen_get_height());
    sprite_buffer_clear(forefront_sprite_buffer);
    _print_ln(forefront_sprite_buffer, "TESTING WINDOW MANAGER");
    _print_ln(forefront_sprite_buffer, "======================");
    _print_ln(forefront_sprite_buffer, "Window will move around randomly.");

    sprite_buffer_extract_characters(_debug_buffer, forefront_sprite_buffer);

    int dx[WINDOW_MANAGER_TEST_SPRITE_BUFFER_COUNT];
    int dy[WINDOW_MANAGER_TEST_SPRITE_BUFFER_COUNT];
    for (int i = 0; i < WINDOW_MANAGER_TEST_SPRITE_BUFFER_COUNT; i++) {
        struct SpriteBuffer* sprite_buffer = &_sprite_buffers[i];
        sprite_buffer_allocate(sprite_buffer, _rand_size(), _rand_size());
        sprite_buffer_clear(sprite_buffer);
        _random_fill(sprite_buffer);
        dx[i] = (rand() % 5) - 2;
        dy[i] = (rand() % 5) - 2;
        struct VirtualWindow2* window = &_windows[i];
        window_manager_window_2_init(window);
        window->buffer = sprite_buffer;
        window->has_border = true;
        _set_random_position(window);
    }

    struct FrameTimer timer;
    frame_timer_init();
    frame_timer_timer_init(&timer);
    frame_timer_start(&timer, milliseconds_as_duration(5000));

    int t = 0;
    while (!frame_timer_is_done(&timer)) {
        event_on_frame_start();
        event_on_render_start();
        int dt = duration_as_milliseconds(frame_timer_get_elapsed_time(&timer)) / 50;

        for (int i = 0; i < WINDOW_MANAGER_TEST_SPRITE_BUFFER_COUNT; i++) {
            struct VirtualWindow2* window = &_windows[i];
            if (t != dt) {
                window->offset_x += dx[i];
                window->offset_y += dy[i];
            }
            window_manager_window_draw_2(window);
            if (!window_manager_window_is_inside_screen_2(window)) {
                _set_random_position(window);
            }
        }

        struct VirtualWindow2* forefront_window = &_windows[WINDOW_MANAGER_TEST_FOREFRONT_INDEX];
        window_manager_window_2_init(forefront_window);
        forefront_window->buffer = forefront_sprite_buffer;
        window_manager_window_draw_2(forefront_window);

        if (t != dt) {
            t = dt;
        }

        virtual_screen_render();
        event_on_render_end();
    }

    _release();
}


static void window_manager_test_alignment() {
    log_info("TEST: window_manager_test_alignment");

    _init();

    struct SpriteBuffer* forefront_sprite_buffer = &_sprite_buffers[WINDOW_MANAGER_TEST_FOREFRONT_INDEX];
    sprite_buffer_allocate(forefront_sprite_buffer, virtual_screen_get_width(), virtual_screen_get_height());
    sprite_buffer_clear(forefront_sprite_buffer);
    _print_ln(forefront_sprite_buffer, "TESTING WINDOW MANAGER ALIGNMENT");
    _print_ln(forefront_sprite_buffer, "================================");
    _print_ln(forefront_sprite_buffer, "Testing different window alignment relative to the screen.");

    struct VirtualWindow2* forefront_window = &_windows[WINDOW_MANAGER_TEST_FOREFRONT_INDEX];
    window_manager_window_2_init(forefront_window);
    forefront_window->buffer = forefront_sprite_buffer;

    int width = 10;
    int height = 5;
    int window_count = 0;

    struct SpriteBuffer* sprite_buffer = &_sprite_buffers[0];
    sprite_buffer_allocate(sprite_buffer, width, height);
    sprite_buffer_clear(sprite_buffer);

    struct VirtualWindow2* window_top_left = &_windows[window_count++];
    window_top_left->buffer = sprite_buffer;
    window_top_left->has_border = true;
    window_manager_window_align_left_screen_2(window_top_left);
    window_manager_window_align_top_screen_2(window_top_left);

    struct VirtualWindow2* window_top_center = &_windows[window_count++];
    window_top_center->buffer = sprite_buffer;
    window_top_center->has_border = true;
    window_manager_window_center_screen_x_2(window_top_center);
    window_manager_window_align_top_screen_2(window_top_center);

    struct VirtualWindow2* window_top_right = &_windows[window_count++];
    window_top_right->buffer = sprite_buffer;
    window_top_right->has_border = true;
    window_manager_window_align_right_screen_2(window_top_right);
    window_manager_window_align_top_screen_2(window_top_right);

    struct VirtualWindow2* window_center_left = &_windows[window_count++];
    window_center_left->buffer = sprite_buffer;
    window_center_left->has_border = true;
    window_manager_window_align_left_screen_2(window_center_left);
    window_manager_window_center_screen_y_2(window_center_left);

    struct VirtualWindow2* window_center_center = &_windows[window_count++];
    window_center_center->buffer = sprite_buffer;
    window_center_center->has_border = true;
    window_manager_window_center_screen_x_2(window_center_center);
    window_manager_window_center_screen_y_2(window_center_center);

    struct VirtualWindow2* window_center_right = &_windows[window_count++];
    window_center_right->buffer = sprite_buffer;
    window_center_right->has_border = true;
    window_manager_window_align_right_screen_2(window_center_right);
    window_manager_window_center_screen_y_2(window_center_right);

    struct VirtualWindow2* window_bottom_left = &_windows[window_count++];
    window_bottom_left->buffer = sprite_buffer;
    window_bottom_left->has_border = true;
    window_manager_window_align_left_screen_2(window_bottom_left);
    window_manager_window_align_bottom_screen_2(window_bottom_left);

    struct VirtualWindow2* window_bottom_center = &_windows[window_count++];
    window_bottom_center->buffer = sprite_buffer;
    window_bottom_center->has_border = true;
    window_manager_window_center_screen_x_2(window_bottom_center);
    window_manager_window_align_bottom_screen_2(window_bottom_center);

    struct VirtualWindow2* window_bottom_right = &_windows[window_count++];
    window_bottom_right->buffer = sprite_buffer;
    window_bottom_right->has_border = true;
    window_manager_window_align_right_screen_2(window_bottom_right);
    window_manager_window_align_bottom_screen_2(window_bottom_right);

    event_on_frame_start();
    event_on_render_start();

    for (int i = 0; i < window_count; i++) {
        window_manager_window_draw_2(&_windows[i]);
    }

    window_manager_window_draw_2(forefront_window);

    virtual_screen_render();
    event_on_render_end();
    sleep(5);

    _release();
}


void window_manager_2_test() {
    window_manager_test_random();
    window_manager_test_alignment();
}
