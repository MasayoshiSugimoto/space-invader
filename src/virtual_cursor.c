#include "virtual_cursor.h"


void virtual_cursor_init(struct VirtualCursor* cursor) {
    memset(cursor, 0, sizeof *cursor);
}


void virtual_cursor_text_center_x(struct VirtualCursor* cursor, const char* text) {
    cursor->x = (cursor->window->width / 2) - (strlen(text) / 2);
}


void virtual_cursor_text_align_right(struct VirtualCursor* cursor, const char* text) {
    struct VirtualWindow* window = cursor->window;
    cursor->x = window->width - strlen(text) - 1;
}


void virtual_cursor_text_print(struct VirtualCursor* cursor, const char* text) {
    struct VirtualWindow* window = cursor->window;
    for (int i = 0; i < strlen(text); i++) {
        struct VirtualPixel pixel = {text[i], 0};
        window_manager_window_set_pixel(window, cursor->x, cursor->y, pixel);
        virtual_cursor_next(cursor);
    }
}


void virtual_cursor_center_x(struct VirtualCursor* cursor) {
    cursor->x = cursor->window->width / 2;
}


void virtual_cursor_center_y(struct VirtualCursor* cursor) {
    cursor->y = cursor->window->height / 2;
}


void virtual_cursor_new_line(struct VirtualCursor* cursor) {
    cursor->x = 0;
    cursor->y++;
}


void virtual_cursor_next(struct VirtualCursor* cursor) {
    cursor->x++;
    if (cursor->x >= cursor->window->width) {
        cursor->x = 0;
        cursor->y++;
    }
}


void virtual_cursor_show(struct VirtualCursor* cursor) {
    if (window_manager_window_is_inside(cursor->window, cursor->x, cursor->y)) {
        move(cursor->window->offset_y + cursor->y, cursor->window->offset_x + cursor->x);  // Set virtual cursor position
        curs_set(CURSOR_VISIBILITY_HIGH_VISIBILITY);
    } else {
        curs_set(CURSOR_VISIBILITY_INVISIBLE);
    }
}