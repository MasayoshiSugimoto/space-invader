#include "screen.h"


struct Screen {
  int width;
  int height;
  ScreenCharacter* screen_buffer; 
  struct ScreenWindow windows[SCREEN_WINDOW_MAX]; 
};


const struct ScreenAlignment SCREEN_ALIGNMENT_TOP_CENTER = {SCREEN_VERTICAL_ALIGNMENT_TOP, SCREEN_HORIZONTAL_ALIGNMENT_CENTER};
const struct ScreenAlignment SCREEN_ALIGNMENT_TOP_RIGHT = {SCREEN_VERTICAL_ALIGNMENT_TOP, SCREEN_HORIZONTAL_ALIGNMENT_RIGHT};
const struct ScreenAlignment SCREEN_ALIGNMENT_CENTER_RIGHT = {SCREEN_VERTICAL_ALIGNMENT_CENTER, SCREEN_HORIZONTAL_ALIGNMENT_RIGHT};
const struct ScreenAlignment SCREEN_ALIGNMENT_BOTTOM_RIGHT = {SCREEN_VERTICAL_ALIGNMENT_BOTTOM, SCREEN_HORIZONTAL_ALIGNMENT_RIGHT};
const struct ScreenAlignment SCREEN_ALIGNMENT_BOTTOM_CENTER = {SCREEN_VERTICAL_ALIGNMENT_BOTTOM, SCREEN_HORIZONTAL_ALIGNMENT_CENTER};
const struct ScreenAlignment SCREEN_ALIGNMENT_BOTTOM_LEFT = {SCREEN_VERTICAL_ALIGNMENT_BOTTOM, SCREEN_HORIZONTAL_ALIGNMENT_LEFT};
const struct ScreenAlignment SCREEN_ALIGNMENT_CENTER_LEFT = {SCREEN_VERTICAL_ALIGNMENT_CENTER, SCREEN_HORIZONTAL_ALIGNMENT_LEFT};
const struct ScreenAlignment SCREEN_ALIGNMENT_TOP_LEFT = {SCREEN_VERTICAL_ALIGNMENT_TOP, SCREEN_HORIZONTAL_ALIGNMENT_LEFT};
const struct ScreenAlignment SCREEN_ALIGNMENT_CENTER_CENTER = {SCREEN_VERTICAL_ALIGNMENT_CENTER, SCREEN_HORIZONTAL_ALIGNMENT_CENTER};


struct Screen l_screen;


struct Screen* screen_get_screen() {
  return &l_screen;
}


void screen_init(struct Screen* screen) {
  int width = SCREEN_WIDTH;
  int height = SCREEN_HEIGHT;

  screen->width = width;
  screen->height = height;
  screen->screen_buffer = malloc(sizeof(ScreenCharacter) * width * height);
  for (int i = 0; i < array_size(screen->windows); i++) {
    screen->windows[i].position = VZERO;
    screen->windows[i].sprite_id = SPRITE_ID_NONE;
  }
}


struct RenderingUnit {
  const struct Sprite* sprite;
  EntityId entity_id;
  struct VirtualWindow* window;
  int x;
  int y;
};


void screen_set_entity_alignment(const struct Screen* screen, struct EntitySystem* entity_system, EntityId entity_id, const struct ScreenAlignment screen_alignment) {
  const struct Sprite* sprite = sprite_get_sprite(sprite_component_get_sprite_id(entity_id));

  struct Vector v = entity_system_get_coordinates(entity_system, entity_id);
  switch (screen_alignment.vertical_alignment) {
    case SCREEN_VERTICAL_ALIGNMENT_NONE:
      // Keep y as is.
      break;
    case SCREEN_VERTICAL_ALIGNMENT_TOP:
      v.y = 0;
      break;
    case SCREEN_VERTICAL_ALIGNMENT_CENTER:
      v.y = screen->height / 2 - sprite->height / 2;
      break;
    case SCREEN_VERTICAL_ALIGNMENT_BOTTOM:
      v.y = screen->height - sprite->height;
      break;
  }

  switch (screen_alignment.horizontal_alignment) {
    case SCREEN_HORIZONTAL_ALIGNMENT_NONE:
      // Keep as is.
      break;
    case SCREEN_HORIZONTAL_ALIGNMENT_LEFT:
      v.x = 0;
      break;
    case SCREEN_HORIZONTAL_ALIGNMENT_CENTER:
      v.x = screen->width / 2 - sprite->width / 2;
      break;
    case SCREEN_HORIZONTAL_ALIGNMENT_RIGHT:
      v.x = screen->width - sprite->width;
      break;
  }

  entity_system_set_coordinates(entity_system, entity_id, v);
}
