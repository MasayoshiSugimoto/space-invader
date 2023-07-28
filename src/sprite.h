#ifndef SPRITE_H
#define SPRITE_H


#include <stdio.h>
#include "log.h"
#include "consts.h"
#include "util.h"


enum SpriteId {
  SPRITE_ID_SPACESHIP,
  SPRITE_ID_MAX,
};


void sprite_init();
const char* sprite_as_string(enum SpriteId);


#endif

