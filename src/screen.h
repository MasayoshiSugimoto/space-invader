#ifndef SCREEN_H
#define SCREEN_H


#include "vector.h"
#include "sprite.h"
#include "terminal.h"
#include "consts.h"
#include "color.h"
#include "collision_manager.h"


#define SCREEN_WINDOW_MAX 100


typedef int ScreenCharacter;


struct ScreenWindow {
  struct Vector position;
  enum SpriteId sprite_id;
};


struct Screen;


enum ScreenHorizontalAlignment {
  SCREEN_HORIZONTAL_ALIGNMENT_NONE,
  SCREEN_HORIZONTAL_ALIGNMENT_LEFT,
  SCREEN_HORIZONTAL_ALIGNMENT_CENTER,
  SCREEN_HORIZONTAL_ALIGNMENT_RIGHT,
};


enum ScreenVerticalAlignment {
  SCREEN_VERTICAL_ALIGNMENT_NONE,
  SCREEN_VERTICAL_ALIGNMENT_TOP,
  SCREEN_VERTICAL_ALIGNMENT_CENTER,
  SCREEN_VERTICAL_ALIGNMENT_BOTTOM,
};


struct ScreenAlignment {
  enum ScreenVerticalAlignment vertical_alignment;
  enum ScreenHorizontalAlignment horizontal_alignment;
};


const struct ScreenAlignment SCREEN_ALIGNMENT_TOP_CENTER;
const struct ScreenAlignment SCREEN_ALIGNMENT_TOP_RIGHT;
const struct ScreenAlignment SCREEN_ALIGNMENT_CENTER_RIGHT;
const struct ScreenAlignment SCREEN_ALIGNMENT_BOTTOM_RIGHT;
const struct ScreenAlignment SCREEN_ALIGNMENT_BOTTOM_CENTER;
const struct ScreenAlignment SCREEN_ALIGNMENT_BOTTOM_LEFT;
const struct ScreenAlignment SCREEN_ALIGNMENT_CENTER_LEFT;
const struct ScreenAlignment SCREEN_ALIGNMENT_TOP_LEFT;
const struct ScreenAlignment SCREEN_ALIGNMENT_CENTER_CENTER;


struct Screen* screen_get_screen();
void screen_init(void);
void screen_release(void);


#endif
