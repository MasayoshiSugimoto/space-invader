#include "virtual_cursor_2_test.h"

#define BUFFER_LENGTH 512
static char _buf[BUFFER_LENGTH];
static const char* _characters = "abcdefghijlmnopqrstuvwxyz.,!?- ";


static void _random_string(char* buf, int length) {
    for (int i = 0; i < length; i++) {
        buf[i] = _characters[rand() % strlen(_characters)];
    }
    _buf[length] = 0;
}


void virtual_cursor_2_test() {
    log_info("TEST: virtual_cursor_2_test");

    struct SpriteBuffer sprite_buffer_0;
    sprite_buffer_allocate(&sprite_buffer_0, virtual_screen_get_width(), virtual_screen_get_height());
    sprite_buffer_clear(&sprite_buffer_0);
    struct VirtualCursor2 cursor_0;
    virtual_cursor_2_init(&cursor_0, &sprite_buffer_0);
    virtual_cursor_2_text_print(&cursor_0, "TESTING VIRTUAL CURSOR");
    virtual_cursor_2_new_line(&cursor_0);
    virtual_cursor_2_text_print(&cursor_0, "======================");
    virtual_cursor_2_new_line(&cursor_0);
    virtual_cursor_2_text_print(&cursor_0, "Will populate windows with different styling.");
    
    int width = 21;
    int height = 5;
    struct SpriteBuffer sprite_buffer_1;
    sprite_buffer_allocate(&sprite_buffer_1, width, height);
    sprite_buffer_clear(&sprite_buffer_1);
    struct VirtualCursor2 cursor_1;
    virtual_cursor_2_init(&cursor_1, &sprite_buffer_1);
    virtual_cursor_2_text_print(&cursor_1, "BIG STRING");
    virtual_cursor_2_new_line(&cursor_1);
    virtual_cursor_2_text_print(&cursor_1, "==========");
    virtual_cursor_2_new_line(&cursor_1);
    _random_string(_buf, BUFFER_LENGTH - 1);
    virtual_cursor_2_text_print(&cursor_1, _buf);

    struct SpriteBuffer sprite_buffer_2;
    sprite_buffer_allocate(&sprite_buffer_2, width, height);
    sprite_buffer_clear(&sprite_buffer_2);
    struct VirtualCursor2 cursor_2;
    virtual_cursor_2_init(&cursor_2, &sprite_buffer_2);
    virtual_cursor_2_text_center_x(&cursor_2, "CENTERED STRING");
    virtual_cursor_2_text_print(&cursor_2, "CENTERED STRING");
    virtual_cursor_2_new_line(&cursor_2);
    virtual_cursor_2_text_center_x(&cursor_2, "===============");
    virtual_cursor_2_text_print(&cursor_2, "===============");
    virtual_cursor_2_new_line(&cursor_2);
    _random_string(_buf, 10);
    virtual_cursor_2_text_center_x(&cursor_2, _buf);
    virtual_cursor_2_text_print(&cursor_2, _buf);
    virtual_cursor_2_new_line(&cursor_2);
    _random_string(_buf, 15);
    virtual_cursor_2_text_center_x(&cursor_2, _buf);
    virtual_cursor_2_text_print(&cursor_2, _buf);
    virtual_cursor_2_new_line(&cursor_2);

    struct SpriteBuffer sprite_buffer_3;
    sprite_buffer_allocate(&sprite_buffer_3, width, height);
    sprite_buffer_clear(&sprite_buffer_3);
    struct VirtualCursor2 cursor_3;
    virtual_cursor_2_init(&cursor_3, &sprite_buffer_3);
    virtual_cursor_2_text_align_right(&cursor_3, "RIGHT STRING");
    virtual_cursor_2_text_print(&cursor_3, "RIGHT STRING");
    virtual_cursor_2_new_line(&cursor_3);
    virtual_cursor_2_text_align_right(&cursor_3, "=============");
    virtual_cursor_2_text_print(&cursor_3, "=============");
    virtual_cursor_2_new_line(&cursor_3);
    _random_string(_buf, 10);
    virtual_cursor_2_text_align_right(&cursor_3, _buf);
    virtual_cursor_2_text_print(&cursor_3, _buf);
    virtual_cursor_2_new_line(&cursor_3);
    _random_string(_buf, 15);
    virtual_cursor_2_text_align_right(&cursor_3, _buf);
    virtual_cursor_2_text_print(&cursor_3, _buf);
    virtual_cursor_2_new_line(&cursor_3);

    struct VirtualWindow2 window0;
    window_manager_window_init(&window0);
    window0.buffer = &sprite_buffer_0;

    int margin = 2;
    int border = 2;
    int offset_y = 5;
    int offset_x = border;
    
    struct VirtualWindow2 window1;
    window_manager_window_init(&window1);
    window1.has_border = true;
    window1.buffer = &sprite_buffer_1;
    window1.offset_x = offset_x;
    window1.offset_y = offset_y;

    offset_x += border + margin + width;

    struct VirtualWindow2 window2;
    window_manager_window_init(&window2);
    window2.has_border = true;
    window2.buffer = &sprite_buffer_2;
    window2.offset_x = offset_x;
    window2.offset_y = offset_y;

    offset_x += border + margin + width;

    struct VirtualWindow2 window3;
    window_manager_window_init(&window3);
    window3.has_border = true;
    window3.buffer = &sprite_buffer_3;
    window3.offset_x = offset_x;
    window3.offset_y = offset_y;

    event_on_frame_start();
    event_on_render_start();

    window_manager_window_draw(&window0);
    window_manager_window_draw(&window1);
    window_manager_window_draw(&window2);
    window_manager_window_draw(&window3);

    virtual_screen_render();
    event_on_render_end();

    sleep(5);
}