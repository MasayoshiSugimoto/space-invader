#ifndef SPRITE_BUFFER_H
#define SPRITE_BUFFER_H


#include <stdio.h>
#include "virtual_pixel.h"


struct SpriteBuffer {
    struct VirtualPixel* buffer;
    const char* file_name;
    int width;
    int height;
};


void sprite_buffer_init(struct SpriteBuffer* sprite_buffer);
void sprite_buffer_allocate(struct SpriteBuffer* sprite_buffer, int width, int height);
void sprite_buffer_free(struct SpriteBuffer* sprite_buffer);
void sprite_buffer_resize(struct SpriteBuffer* sprite_buffer, int width, int height);
bool sprite_buffer_is_inside(const struct SpriteBuffer* sprite_buffer, int x, int y);
void sprite_buffer_clear(struct SpriteBuffer* sprite_buffer);
void sprite_buffer_fill(struct SpriteBuffer* sprite_buffer, chtype c);
int sprite_buffer_get_width(const struct SpriteBuffer* sprite_buffer);
int sprite_buffer_get_height(const struct SpriteBuffer* sprite_buffer);
struct VirtualPixel sprite_buffer_get(const struct SpriteBuffer* sprite_buffer, int x, int y);
struct VirtualPixel* sprite_buffer_access(struct SpriteBuffer* sprite_buffer, int x, int y);
void sprite_buffer_extract_characters(char* buffer, const struct SpriteBuffer* sprite_buffer);
void sprite_buffer_as_string(const struct SpriteBuffer* sprite_buffer, char* out_buffer);


#endif
