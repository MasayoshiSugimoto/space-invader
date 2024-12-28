#ifndef SPRITE_H
#define SPRITE_H


#include <stdio.h>
#include <curses.h>
#include "log.h"
#include "consts.h"
#include "util.h"


enum SpriteId {
  SPRITE_ID_NONE,
  SPRITE_ID_SPACESHIP,
  SPRITE_ID_ALIEN,
  SPRITE_ID_SPACESHIP_BULLET,
  SPRITE_ID_EXPLOSION_1,
  SPRITE_ID_EXPLOSION_2,
  SPRITE_ID_EXPLOSION_3,
  SPRITE_ID_TITLE,
  SPRITE_ID_CREDITS,
  SPRITE_ID_MAX,
};


struct Sprite {
  enum SpriteId sprite_id;
  const char* file_name;
  const char* as_string;
  const char* const* as_matrix;
  const chtype* buffer;
  int buffer_length;
  int width;
  int height;
  int character_count;
};


int sprite_buffer_x(const struct Sprite* sprite, int index);
int sprite_buffer_y(const struct Sprite* sprite, int index);
void sprite_init();
void sprite_init_sprite(struct Sprite* sprite, int width, int height);
void sprite_free(struct Sprite* sprite);
const char* sprite_get_file_name(enum SpriteId);
const struct Sprite* sprite_get_sprite(enum SpriteId);


#endif

