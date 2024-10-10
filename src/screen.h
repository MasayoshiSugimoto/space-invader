#ifndef SCREEN_H
#define SCREEN_H


#include "vector.h"
#include "sprite.h"
#include "terminal.h"
#include "consts.h"
#include "color.h"
#include "collision_manager.h"
#include "window_manager.h"


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


struct Vector screen_get_offset(const struct Screen* screen);
struct Screen* screen_get_screen();
void screen_init(struct Screen* screen);
void screen_render(struct Screen* screen, struct EntitySystem* entity_system);
void screen_set_entity_alignment(const struct Screen* screen, struct EntitySystem* entity_system, EntityId entity_id, const struct ScreenAlignment screen_alignment);
int screen_get_width();
int screen_get_height();
void screen_entities_to_window(const struct EntitySystem* entity_system);
void screen_render_in_game(const struct EntitySystem* entity_system);
void screen_setup(void);


#endif
