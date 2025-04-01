#include "virtual_screen.h"


static struct VirtualScreen {
  struct VirtualPixel* screen;
  int width;
  int height;
} _virtual_screen;


bool virtual_screen_is_inside(int x, int y) {
  return 0 <= x && x < _virtual_screen.width && 0 <= y && y < _virtual_screen.height;
}


chtype screen_index(int x, int y) {
  assert_f(virtual_screen_is_inside(x, y), "Invalid screen coordinates: {x: %d, y: %d}", x, y);
  return (y * _virtual_screen.width) + x;
}


size_t screen_buffer_length(void) {
  return _virtual_screen.width * _virtual_screen.height;
}


int private_get(int x, int y) {
  return _virtual_screen.screen[screen_index(x, y)].character;
}


void private_screen_clear(void) {
  for (int i = 0; i < screen_buffer_length(); i++) {
    _virtual_screen.screen[i].character = ' ';
    _virtual_screen.screen[i].color_pair_id = COLOR_COLOR_PAIR_ID_DEFAULT;
  }
}


void virtual_screen_init(void) {
  _virtual_screen.screen = NULL;
  _virtual_screen.width = 0;
  _virtual_screen.height = 0;
}


void virtual_screen_allocate(void) {
  struct Terminal terminal;
  terminal_init(&terminal);
  _virtual_screen.width = terminal.width;
  _virtual_screen.height = terminal.height;
  _virtual_screen.screen = malloc(sizeof(*_virtual_screen.screen) * terminal.width * terminal.height);
  private_screen_clear();
}


void virtual_screen_release(void) {
  assert(_virtual_screen.screen != NULL, "Virtual screen already freed.");
  free(_virtual_screen.screen);
  virtual_screen_init();
}


void virtual_screen_reset(void) {
  if (_virtual_screen.screen != NULL) {
    free(_virtual_screen.screen);
    _virtual_screen.screen = NULL;
  }
  virtual_screen_allocate();
}


void virtual_screen_clear(void) {
  for (int i = 0; i < screen_buffer_length(); i++) {
    _virtual_screen.screen[i].character = ' ';
    _virtual_screen.screen[i].color_pair_id = COLOR_COLOR_PAIR_ID_DEFAULT;
  }
}


void virtual_screen_set_char(int x, int y, const chtype ch) {
  if (virtual_screen_is_inside(x, y)) {
    _virtual_screen.screen[screen_index(x, y)].character = ch;
  }
}


void virtual_screen_set_char_and_color(int x, int y, const chtype ch, ColorPairId color_pair_id) {
  if (virtual_screen_is_inside(x, y)) {
    struct VirtualPixel* pixel = &_virtual_screen.screen[screen_index(x, y)];
    pixel->character = ch;
    pixel->color_pair_id = color_pair_id;
  }
}


void virtual_screen_set_string(int x, int y, const char* string) {
  for (int i = 0; i < strlen(string); i++) {
    virtual_screen_set_char(x + i, y, string[i]);
  }
}


void virtual_screen_render(void) {
  int color_pair = 0;
  for (int x = 0; x < _virtual_screen.width; x++) {
    for (int y = 0; y < _virtual_screen.height; y++) {
      if (!DEBUG_NO_SCREEN_OUTPUT) {
        struct VirtualPixel* pixel = &_virtual_screen.screen[screen_index(x, y)];
        assert(pixel->color_pair_id != 0, "Invalid color.");
        if (COLOR_PAIR(pixel->color_pair_id) != color_pair) {
          color_pair = COLOR_PAIR(pixel->color_pair_id);
          attron(color_pair);
        }
        mvaddch(y, x, pixel->character);
      }
    }
  }
  private_screen_clear();
}


int virtual_screen_center_x(void) {
  return _virtual_screen.width / 2;
}


int virtual_screen_center_y(void) {
  return _virtual_screen.height / 2;
}


int virtual_screen_get_width(void) {
  return _virtual_screen.width;
}


int virtual_screen_get_height(void) {
  return _virtual_screen.height;
}