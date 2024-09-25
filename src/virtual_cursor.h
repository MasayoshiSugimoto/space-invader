#ifndef VIRTUAL_CURSOR_H
#define VIRTUAL_CURSOR_H


#include "color.h"
#include "virtual_screen.h"
#include "cursor.h"
#include "window_manager.h"


struct VirtualCursor {
    int x;
    int y;
    struct VirtualWindow* window;
    ColorPairId color_pair_id;
};


void virtual_cursor_init(struct VirtualCursor* cursor);
void virtual_cursor_text_center_x(struct VirtualCursor* cursor, const char* text);
void virtual_cursor_text_align_right(struct VirtualCursor* cursor, const char* text);
void virtual_cursor_text_print(struct VirtualCursor* cursor, const char* text);
void virtual_cursor_center_x(struct VirtualCursor* cursor);
void virtual_cursor_center_y(struct VirtualCursor* cursor);
void virtual_cursor_new_line(struct VirtualCursor* cursor);
void virtual_cursor_next(struct VirtualCursor* cursor);
void virtual_cursor_show(struct VirtualCursor* cursor);


#endif