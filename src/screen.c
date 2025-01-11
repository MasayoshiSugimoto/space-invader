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


void screen_init(void) {
  int width = SCREEN_WIDTH;
  int height = SCREEN_HEIGHT;

  l_screen.width = width;
  l_screen.height = height;
  l_screen.screen_buffer = malloc(sizeof(ScreenCharacter) * width * height);
  for (int i = 0; i < array_size(l_screen.windows); i++) {
    l_screen.windows[i].position = VZERO;
    l_screen.windows[i].sprite_id = SPRITE_ID_NONE;
  }
}


void screen_release(void) {
  assert(l_screen.screen_buffer != NULL, "Screen buffer is NULL.");
  free(l_screen.screen_buffer);
  l_screen.width = 0;
  l_screen.height = 0;
  l_screen.screen_buffer = NULL;
  for (int i = 0; i < array_size(l_screen.windows); i++) {
    l_screen.windows[i].position = VZERO;
    l_screen.windows[i].sprite_id = SPRITE_ID_NONE;
  }
}


struct RenderingUnit {
  const struct Sprite* sprite;
  EntityId entity_id;
  struct VirtualWindow* window;
  int x;
  int y;
};
