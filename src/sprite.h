#ifndef SPRITE_H
#define SPRITE_H


#include <stdio.h>
#include "log.h"
#include "consts.h"
#include "util.h"


enum SpriteId {
  SPRITE_ID_NONE,
  SPRITE_ID_SPACESHIP,
  SPRITE_ID_ALIEN,
  SPRITE_ID_SPACESHIP_BULLET,
  SPRITE_ID_MAX,
};


struct Sprite {
  enum SpriteId sprite_id;
  const char* file_name;
  const char* as_string;
  const char* const* as_matrix;
  int width;
  int height;
  int character_count;
};


void sprite_init();
const char* sprite_get_file_name(enum SpriteId);
const char* sprite_as_string(enum SpriteId);
const struct Sprite* sprite_get_sprite(enum SpriteId);


#endif

