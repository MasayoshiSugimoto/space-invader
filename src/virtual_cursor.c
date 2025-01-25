#include "virtual_cursor.h"


void virtual_cursor_init_const(struct VirtualCursor* cursor, const struct SpriteBuffer* sprite_buffer) {
    cursor->x = 0;
    cursor->y = 0;
    cursor->sprite_buffer_const = sprite_buffer;
    cursor->sprite_buffer = NULL;
}


void virtual_cursor_init(struct VirtualCursor* cursor, struct SpriteBuffer* sprite_buffer) {
    cursor->x = 0;
    cursor->y = 0;
    cursor->sprite_buffer_const = sprite_buffer;
    cursor->sprite_buffer = sprite_buffer;
}


void virtual_cursor_text_center_x(struct VirtualCursor* cursor, const char* text) {
    cursor->x = (cursor->sprite_buffer_const->width / 2) - (strlen(text) / 2);
}


void virtual_cursor_text_align_right(struct VirtualCursor* cursor, const char* text) {
    cursor->x = cursor->sprite_buffer_const->width - strlen(text) - 1;
}


void virtual_cursor_text_print(struct VirtualCursor* cursor, const char* text) {
    if (cursor->sprite_buffer == NULL) return;
    for (int i = 0; text[i] != 0; i++) {
        sprite_buffer_access(cursor->sprite_buffer, cursor->x, cursor->y)->character = text[i];
        virtual_cursor_next(cursor);
    }
}


void virtual_cursor_character_set(struct VirtualCursor* cursor, char c, ColorPairId color_pair_id) {
    if (cursor->sprite_buffer == NULL) return;
    sprite_buffer_access(cursor->sprite_buffer, cursor->x, cursor->y)->character = c;
    sprite_buffer_access(cursor->sprite_buffer, cursor->x, cursor->y)->color_pair_id = color_pair_id;
}


void virtual_cursor_center_x(struct VirtualCursor* cursor) {
    cursor->x = cursor->sprite_buffer_const->width / 2;
}


void virtual_cursor_center_y(struct VirtualCursor* cursor) {
    cursor->y = cursor->sprite_buffer_const->height / 2;
}


void virtual_cursor_new_line(struct VirtualCursor* cursor) {
    cursor->x = 0;
    cursor->y++;
}


void virtual_cursor_next(struct VirtualCursor* cursor) {
    cursor->x++;
    if (cursor->x >= cursor->sprite_buffer_const->width) {
        cursor->x = 0;
        cursor->y++;
    }
}


void virtual_cursor_move_up(struct VirtualCursor* cursor) {
    cursor->y = imax(cursor->y - 1, 0);
}


void virtual_cursor_move_right(struct VirtualCursor* cursor) {
    cursor->x = imin(cursor->x + 1, cursor->sprite_buffer_const->width - 1);
}


void virtual_cursor_move_down(struct VirtualCursor* cursor) {
    cursor->y = imin(cursor->y + 1, cursor->sprite_buffer_const->height - 1);
}


void virtual_cursor_move_left(struct VirtualCursor* cursor) {
    cursor->x = imax(cursor->x - 1, 0);
}