#ifndef VIRTUAL_CURSOR_H
#define VIRTUAL_CURSOR_H


#include "color.h"
#include "virtual_screen.h"
#include "cursor.h"
#include "util.h"
#include "sprite_buffer.h"


struct VirtualCursor {
    int x;  // Coordinate relative to window.
    int y;  // Coordinate relative to window.
    ColorPairId color_pair_id;
    const struct SpriteBuffer* sprite_buffer_const;
    struct SpriteBuffer* sprite_buffer;
};


void virtual_cursor_init_const(struct VirtualCursor* cursor, const struct SpriteBuffer* sprite_buffer);
void virtual_cursor_init(struct VirtualCursor* cursor, struct SpriteBuffer* sprite_buffer);
void virtual_cursor_text_center_x(struct VirtualCursor* cursor, const char* text);
void virtual_cursor_text_align_right(struct VirtualCursor* cursor, const char* text);
void virtual_cursor_text_print(struct VirtualCursor* cursor, const char* text);
void virtual_cursor_character_set(struct VirtualCursor* cursor, char c, ColorPairId color_pair_id);
void virtual_cursor_center_x(struct VirtualCursor* cursor);
void virtual_cursor_center_y(struct VirtualCursor* cursor);
void virtual_cursor_new_line(struct VirtualCursor* cursor);
void virtual_cursor_next(struct VirtualCursor* cursor);
void virtual_cursor_move_up(struct VirtualCursor* cursor);
void virtual_cursor_move_right(struct VirtualCursor* cursor);
void virtual_cursor_move_down(struct VirtualCursor* cursor);
void virtual_cursor_move_left(struct VirtualCursor* cursor);


#endif