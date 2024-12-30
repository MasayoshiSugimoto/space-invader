#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H


#include <stdio.h>
#include "sprite_buffer.h"


void sprite_loader_init(void);
void sprite_loader_save(const struct SpriteBuffer* sprite);
void sprite_loader_load_sprite_set(const char* sprite_set_file_name);
struct SpriteBuffer* sprite_loader_sprite_get(const char* file_name);


#endif