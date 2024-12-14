#include "virtual_cursor_test.h"

#define BUFFER_LENGTH 512
static char _buf[BUFFER_LENGTH];
static const char* _characters = "abcdefghijlmnopqrstuvwxyz.,!?- ";


void _random_string(char* buf, int length) {
    for (int i = 0; i < length; i++) {
        buf[i] = _characters[rand() % strlen(_characters)];
    }
    _buf[length] = 0;
}


void virtual_cursor_test() {
    log_info("TEST: virtual_cursor_test");

    window_manager_init();

    struct VirtualWindow* window0 = window_manager_window_new(virtual_screen_get_width(), virtual_screen_get_height());
    struct VirtualCursor cursor0;
    virtual_cursor_init(&cursor0);
    cursor0.window = window0;

    virtual_cursor_text_print(&cursor0, "TESTING VIRTUAL CURSOR");
    virtual_cursor_new_line(&cursor0);
    virtual_cursor_text_print(&cursor0, "======================");
    virtual_cursor_new_line(&cursor0);
    virtual_cursor_text_print(&cursor0, "Will populate windows with different styling.");

    int offset_y = 5;

    struct VirtualWindow* window1 = window_manager_window_new(21, 5);
    window1->has_border = true;
    window1->offset_x = 2;
    window1->offset_y = offset_y;
    struct VirtualCursor cursor1;
    virtual_cursor_init(&cursor1);
    cursor1.window = window1;
    virtual_cursor_text_print(&cursor1, "BIG STRING");
    virtual_cursor_new_line(&cursor1);
    virtual_cursor_text_print(&cursor1, "==========");
    virtual_cursor_new_line(&cursor1);
    _random_string(_buf, BUFFER_LENGTH - 1);
    virtual_cursor_text_print(&cursor1, _buf);
    
    struct VirtualWindow* window2 = window_manager_window_new(21, 5);
    window2->has_border = true;
    window2->offset_x = 26;
    window2->offset_y = offset_y;
    struct VirtualCursor cursor2;
    virtual_cursor_init(&cursor2);
    cursor2.window = window2;
    virtual_cursor_text_center_x(&cursor2, "CENTERED STRING");
    virtual_cursor_text_print(&cursor2, "CENTERED STRING");
    virtual_cursor_new_line(&cursor2);
    virtual_cursor_text_center_x(&cursor2, "===============");
    virtual_cursor_text_print(&cursor2, "===============");
    virtual_cursor_new_line(&cursor2);
    _random_string(_buf, 10);
    virtual_cursor_text_center_x(&cursor2, _buf);
    virtual_cursor_text_print(&cursor2, _buf);
    virtual_cursor_new_line(&cursor2);
    _random_string(_buf, 15);
    virtual_cursor_text_center_x(&cursor2, _buf);
    virtual_cursor_text_print(&cursor2, _buf);
    virtual_cursor_new_line(&cursor2);

    struct VirtualWindow* window3 = window_manager_window_new(21, 5);
    window3->has_border = true;
    window3->offset_x = 50;
    window3->offset_y = offset_y;
    struct VirtualCursor cursor3;
    virtual_cursor_init(&cursor3);
    cursor3.window = window3;
    virtual_cursor_text_align_right(&cursor3, "RIGHT ALIGNED");
    virtual_cursor_text_print(&cursor3, "RIGHT ALIGNED");
    virtual_cursor_new_line(&cursor3);
    virtual_cursor_text_align_right(&cursor3, "=============");
    virtual_cursor_text_print(&cursor3, "=============");
    virtual_cursor_new_line(&cursor3);
    _random_string(_buf, 10);
    virtual_cursor_text_align_right(&cursor3, _buf);
    virtual_cursor_text_print(&cursor3, _buf);
    virtual_cursor_new_line(&cursor3);
    _random_string(_buf, 15);
    virtual_cursor_text_align_right(&cursor3, _buf);
    virtual_cursor_text_print(&cursor3, _buf);
    virtual_cursor_new_line(&cursor3);

    window_manager_window_draw(window0);
    window_manager_window_draw(window1);
    window_manager_window_draw(window2);
    window_manager_window_draw(window3);
    virtual_screen_render();
    virtual_cursor_show(&cursor3);
    refresh();
    sleep(5);

    window_manager_window_release_all();
}