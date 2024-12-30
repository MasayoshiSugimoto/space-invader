#include "sprite_buffer.h"


static const struct VirtualPixel _pixel_empty;
static struct VirtualPixel _pixel_bad_access;  // Used to handle wrong buffer access silently.


void sprite_buffer_init(struct SpriteBuffer* sprite_buffer) {
    sprite_buffer->buffer = NULL;
    sprite_buffer->width = 0;
    sprite_buffer->height = 0;
    sprite_buffer->file_name = "uninitialized.dat";
}


void sprite_buffer_allocate(struct SpriteBuffer* sprite_buffer, int width, int height) {
    sprite_buffer->buffer = malloc(sizeof(struct VirtualPixel*) * width * height);
    sprite_buffer->width = width;
    sprite_buffer->height = height;
}


void sprite_buffer_free(struct SpriteBuffer* sprite_buffer) {
    if (sprite_buffer->buffer != NULL) {
        free(sprite_buffer->buffer);
        sprite_buffer->buffer = NULL;
    }
}


void sprite_buffer_resize(struct SpriteBuffer* sprite_buffer, int width, int height) {
    sprite_buffer_free(sprite_buffer);
    sprite_buffer_allocate(sprite_buffer, width, height);
}


bool sprite_buffer_is_inside(const struct SpriteBuffer* sprite_buffer, int x, int y) {
    return 0 <= x && x < sprite_buffer->width && 0 <= y && y < sprite_buffer->height;
}


void sprite_buffer_clear(struct SpriteBuffer* sprite_buffer) {
    int length = sprite_buffer->width * sprite_buffer->height;
    for (int i = 0; i < length; i++) {
        sprite_buffer->buffer[i].character = 0;
        sprite_buffer->buffer[i].color_pair_id = COLOR_COLOR_PAIR_ID_DEFAULT;
    }
}


void sprite_buffer_fill(struct SpriteBuffer* sprite_buffer, chtype c) {
    int length = sprite_buffer->width * sprite_buffer->height;
    for (int i = 0; i < length; i++) {
        sprite_buffer->buffer[i].character = c;
    }
}


int sprite_buffer_get_width(const struct SpriteBuffer* sprite_buffer) {
    return sprite_buffer->width;
}


int sprite_buffer_get_height(const struct SpriteBuffer* sprite_buffer) {
    return sprite_buffer->height;
}


struct VirtualPixel sprite_buffer_get(const struct SpriteBuffer* sprite_buffer, int x, int y) {
    if (sprite_buffer_is_inside(sprite_buffer, x, y)) {
        return sprite_buffer->buffer[y * sprite_buffer->width + x];
    } else {
        return _pixel_empty;
    }
}


struct VirtualPixel* sprite_buffer_access(struct SpriteBuffer* sprite_buffer, int x, int y) {
    if (sprite_buffer_is_inside(sprite_buffer, x, y)) {
        return &sprite_buffer->buffer[y * sprite_buffer->width + x];
    } else {
        memset(&_pixel_bad_access, 0, sizeof(_pixel_bad_access));
        return &_pixel_bad_access;
    }
}


void sprite_buffer_extract_characters(char* buffer, const struct SpriteBuffer* sprite_buffer) {
    int counter = 0;
    for (int y = 0; y < sprite_buffer->height; y++) {
        for (int x = 0; x < sprite_buffer->width; x++) {
            if (sprite_buffer_get(sprite_buffer, x, y).character != 0) {
                buffer[counter++] = sprite_buffer_get(sprite_buffer, x, y).character;
            } else {
                buffer[counter++] = ' ';
            }
        }
        buffer[counter++] = '\n';
    }
}


void sprite_buffer_as_string(const struct SpriteBuffer* sprite_buffer, char* out_buffer) {
    int offset = 0;
    offset += sprintf(out_buffer, "%s\n", sprite_buffer->file_name);
    offset += sprintf(out_buffer + offset, "  width: %d\n", sprite_buffer->width);
    offset += sprintf(out_buffer + offset, "  height: %d\n", sprite_buffer->height);
    offset += sprintf(out_buffer + offset, "  buffer.characters:");
    for (int y = 0; y < sprite_buffer->height; y++) {
        offset += sprintf(out_buffer + offset, "\n    - ");
        for (int x = 0; x < sprite_buffer->width; x++) {
            offset += sprintf(out_buffer + offset, "%c", sprite_buffer_get(sprite_buffer, x, y).character);
        }
    }
    offset += sprintf(out_buffer + offset, "\n  buffer.color_pair_ids:");
    for (int y = 0; y < sprite_buffer->height; y++) {
        offset += sprintf(out_buffer + offset, "\n    - ");
        for (int x = 0; x < sprite_buffer->width; x++) {
            offset += sprintf(out_buffer + offset, "%03d", sprite_buffer_get(sprite_buffer, x, y).color_pair_id);
        }
    }
}