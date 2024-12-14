#include "virtual_cursor_2.h"


void virtual_cursor_2_init_const(struct VirtualCursor2* cursor, const struct SpriteBuffer* sprite_buffer) {
    cursor->x = 0;
    cursor->y = 0;
    cursor->sprite_buffer_const = sprite_buffer;
    cursor->sprite_buffer = NULL;
}


void virtual_cursor_2_init(struct VirtualCursor2* cursor, struct SpriteBuffer* sprite_buffer) {
    cursor->x = 0;
    cursor->y = 0;
    cursor->sprite_buffer_const = sprite_buffer;
    cursor->sprite_buffer = sprite_buffer;
}


void virtual_cursor_2_text_center_x(struct VirtualCursor2* cursor, const char* text) {
    cursor->x = (cursor->sprite_buffer_const->width / 2) - (strlen(text) / 2);
}


void virtual_cursor_2_text_align_right(struct VirtualCursor2* cursor, const char* text) {
    cursor->x = cursor->sprite_buffer_const->width - strlen(text) - 1;
}


void virtual_cursor_2_text_print(struct VirtualCursor2* cursor, const char* text) {
    if (cursor->sprite_buffer == NULL) return;
    for (int i = 0; text[i] != 0; i++) {
        sprite_buffer_access(cursor->sprite_buffer, cursor->x, cursor->y)->character = text[i];
        virtual_cursor_2_next(cursor);
    }
}


void virtual_cursor_2_character_set(struct VirtualCursor2* cursor, char c, ColorPairId color_pair_id) {
    if (cursor->sprite_buffer == NULL) return;
    sprite_buffer_access(cursor->sprite_buffer, cursor->x, cursor->y)->character = c;
    sprite_buffer_access(cursor->sprite_buffer, cursor->x, cursor->y)->color_pair_id = color_pair_id;
}


void virtual_cursor_2_center_x(struct VirtualCursor2* cursor) {
    cursor->x = cursor->sprite_buffer_const->width / 2;
}


void virtual_cursor_2_center_y(struct VirtualCursor2* cursor) {
    cursor->y = cursor->sprite_buffer_const->height / 2;
}


void virtual_cursor_2_new_line(struct VirtualCursor2* cursor) {
    cursor->x = 0;
    cursor->y++;
}


void virtual_cursor_2_next(struct VirtualCursor2* cursor) {
    cursor->x++;
    if (cursor->x >= cursor->sprite_buffer_const->width) {
        cursor->x = 0;
        cursor->y++;
    }
}


void virtual_cursor_2_move_up(struct VirtualCursor2* cursor) {
    cursor->y = imax(cursor->y - 1, 0);
}


void virtual_cursor_2_move_right(struct VirtualCursor2* cursor) {
    cursor->x = imin(cursor->x + 1, cursor->sprite_buffer_const->width - 1);
}


void virtual_cursor_2_move_down(struct VirtualCursor2* cursor) {
    cursor->y = imin(cursor->y + 1, cursor->sprite_buffer_const->height - 1);
}


void virtual_cursor_2_move_left(struct VirtualCursor2* cursor) {
    cursor->x = imax(cursor->x - 1, 0);
}