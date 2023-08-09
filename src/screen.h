#ifndef SCREEN_H
#define SCREEN_H


#include "vector.h"
#include "sprite.h"
#include "terminal.h"
#include "game.h"
#include "consts.h"
#include "color.h"
#include "collision_manager.h"


#define SCREEN_WINDOW_MAX 100


typedef int ScreenCharacter;


struct ScreenWindow {
  struct Vector position;
  enum SpriteId sprite_id;
};


struct Screen {
  int width;
  int height;
  ScreenCharacter* screen_buffer; 
  struct ScreenWindow windows[SCREEN_WINDOW_MAX]; 
};


struct Vector screen_get_offset(const struct Screen* screen, const struct Terminal* terminal);
void screen_init(struct Screen* screen);
void screen_render(struct Screen* screen, struct Terminal* terminal, struct Game* game);


#endif
