#ifndef VIRTUAL_CURSOR_H
#define VIRTUAL_CURSOR_H


#include "color.h"


struct VirtualCursor {
    int x;
    int y;
    ColorPairId color_pair_id;
    
};


void virtual_cursor_set_coordinates(struct VirtualCursor* cursor, int x, int y);
void virtual_cursor_text_center_x(struct VirtualCursor* cursor, const char* text);
void virtual_cursor_center_x(struct VirtualCursor* cursor);
void virtual_cursor_center_y(struct VirtualCursor* cursor);
void virtual_cursor_new_line(struct VirtualCursor* cursor);
void virtual_cursor_next(struct VirtualCursor* cursor);
void virtual_cursor_print_text(struct VirtualCursor* cursor, const char* text);


#endif