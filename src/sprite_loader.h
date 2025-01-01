#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H


#include <stdio.h>
#include "sprite_buffer.h"


#define SPRITE_LOADER_FILE_NAME_SPACESHIP_BULLET "spaceship_bullet.dat"
#define SPRITE_LOADER_FILE_NAME_TITLE "title.dat"
#define SPRITE_LOADER_FILE_NAME_CREDITS "credits.dat"


void sprite_loader_init(void);
void sprite_loader_save(const struct SpriteBuffer* sprite);
void sprite_loader_one_sprite_load(const char* sprite_file_name);
void sprite_loader_load_sprite_set(const char* sprite_set_file_name);
struct SpriteBuffer* sprite_loader_sprite_get(const char* file_name);
void sprite_loader_release(void);


#endif