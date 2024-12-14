#ifndef VIRTUAL_CURSOR_2_H
#define VIRTUAL_CURSOR_2_H


#include "color.h"
#include "virtual_screen.h"
#include "cursor.h"
#include "window_manager.h"
#include "util.h"
#include "sprite_buffer.h"


struct VirtualCursor2 {
    int x;  // Coordinate relative to window.
    int y;  // Coordinate relative to window.
    ColorPairId color_pair_id;
    const struct SpriteBuffer* sprite_buffer_const;
    struct SpriteBuffer* sprite_buffer;
};


void virtual_cursor_2_init_const(struct VirtualCursor2* cursor, const struct SpriteBuffer* sprite_buffer);
void virtual_cursor_2_init(struct VirtualCursor2* cursor, struct SpriteBuffer* sprite_buffer);
void virtual_cursor_2_text_center_x(struct VirtualCursor2* cursor, const char* text);
void virtual_cursor_2_text_align_right(struct VirtualCursor2* cursor, const char* text);
void virtual_cursor_2_text_print(struct VirtualCursor2* cursor, const char* text);
void virtual_cursor_2_character_set(struct VirtualCursor2* cursor, char c, ColorPairId color_pair_id);
void virtual_cursor_2_center_x(struct VirtualCursor2* cursor);
void virtual_cursor_2_center_y(struct VirtualCursor2* cursor);
void virtual_cursor_2_new_line(struct VirtualCursor2* cursor);
void virtual_cursor_2_next(struct VirtualCursor2* cursor);
void virtual_cursor_2_move_up(struct VirtualCursor2* cursor);
void virtual_cursor_2_move_right(struct VirtualCursor2* cursor);
void virtual_cursor_2_move_down(struct VirtualCursor2* cursor);
void virtual_cursor_2_move_left(struct VirtualCursor2* cursor);


#endif