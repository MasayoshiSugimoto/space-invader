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
    for (int i = 0; i < strlen(text); i++) {
        struct VirtualPixel pixel = {text[i], COLOR_COLOR_PAIR_ID_DEFAULT};
        window_manager_window_set_pixel(cursor->window, cursor->x, cursor->y, pixel);
        virtual_cursor_next(cursor);
    }
}


void virtual_cursor_character_set(struct VirtualCursor* cursor, char c, ColorPairId color_pair_id) {
    struct VirtualPixel pixel = {c, color_pair_id};
    window_manager_window_set_pixel(cursor->window, cursor->x, cursor->y, pixel);
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


void virtual_cursor_move_up(struct VirtualCursor* cursor) {
    cursor->y = imax(cursor->y - 1, 0);
}


void virtual_cursor_move_right(struct VirtualCursor* cursor) {
    cursor->x = imin(cursor->x + 1, cursor->window->width - 1);
}


void virtual_cursor_move_down(struct VirtualCursor* cursor) {
    cursor->y = imin(cursor->y + 1, cursor->window->height - 1);
}


void virtual_cursor_move_left(struct VirtualCursor* cursor) {
    cursor->x = imax(cursor->x - 1, 0);
}


void virtual_cursor_show(struct VirtualCursor* cursor) {
    struct VirtualWindow* window = cursor->window;
    int x = window->offset_x + cursor->x;
    int y = window->offset_y + cursor->y;
    if (window_manager_window_is_inside(window, x, y)) {
        move(y, x);  // Set virtual cursor position
        curs_set(CURSOR_VISIBILITY_HIGH_VISIBILITY);
    } else {
        curs_set(CURSOR_VISIBILITY_INVISIBLE);
    }
}


void virtual_cursor_show_2(struct VirtualCursor* cursor) {
    struct VirtualWindow* window = cursor->window;
    int x = window->offset_x + cursor->x;
    int y = window->offset_y + cursor->y;
    if (window_manager_window_is_inside(window, x, y)) {
        move(y, x);  // Set virtual cursor position
        curs_set(CURSOR_VISIBILITY_NORMAL);
    } else {
        curs_set(CURSOR_VISIBILITY_INVISIBLE);
    }
}


void virtual_cursor_hide(struct VirtualCursor* cursor) {
    curs_set(CURSOR_VISIBILITY_INVISIBLE);
}