#include "log_buffer_test.h"


static struct VirtualWindow2 window;
static struct SpriteBuffer sprite_buffer;
static struct LogBuffer log_buffer;
static int log_buffer_size = 1024 * 50;
static const char* _characters = "abcdefghijklmnopqrstuvwxyz0123456789 -.";


static void _add_random_line(struct SpriteBuffer* sprite_buffer, int length) {
    int random_length = strlen(_characters);
    log_buffer_add_char(&log_buffer, '"');
    for (int i = 1; i < length - 1; i++) {
         log_buffer_add_char(&log_buffer, _characters[rand() % random_length]);
    }
    log_buffer_add_char(&log_buffer, '"');
    log_buffer_add_char(&log_buffer, '\n');
}


void log_buffer_test(void) {
    log_info("TEST: log_buffer_test");
    window_manager_window_2_init(&window);
    sprite_buffer_allocate(&sprite_buffer, virtual_screen_get_width(), virtual_screen_get_height());
    window.buffer = &sprite_buffer;
    log_buffer_init(&log_buffer);
    log_buffer_allocate(&log_buffer, log_buffer_size);

    struct FrameTimer timer;
    frame_timer_timer_init(&timer);
    frame_timer_start(&timer, milliseconds_as_duration(5000));

    int t = 0;
    int count = 0;
    while (!frame_timer_is_done(&timer)) {
        event_on_frame_start();
        event_on_render_start();
        int dt = duration_as_milliseconds(frame_timer_get_elapsed_time(&timer)) / 25;

        if (t != dt) {
            _add_random_line(&sprite_buffer, count++);
            log_buffer_draw_to_sprite_buffer(&log_buffer, &sprite_buffer);
            t = dt;
        }

        window_manager_window_draw_2(&window);

        virtual_screen_render();
        event_on_render_end();
    }
}