#include "virtual_screen.h"


size_t buffer_length(const struct VirtualWindow* window) {
  return window->width * window->height;
}


bool buffer_is_inside(const struct VirtualWindow* window, int i) {
  return i < buffer_length(window);
}


chtype buffer_index(const struct VirtualWindow* window, int x, int y) {
  return y * window->width + x;
}


int buffer_x(const struct VirtualWindow* window, int i) {
  return i % window->width;
}


int buffer_y(const struct VirtualWindow* window, int i) {
  return i / window->width;
}


bool virtual_screen_is_inside(int x, int y) {
  return 0 <= x && x < g_virtual_screen.width && 0 <= y && y < g_virtual_screen.height;
}


bool virtual_window_is_inside(const struct VirtualWindow* window, int x, int y) {
  return 0 <= x && x < window->width && 0 <= y && y < window->height;
}


void virtual_window_set_buffer(struct VirtualWindow* window, int i, chtype ch) {
  if (i < buffer_length(window)) {
    window->pixels[i].character = ch;
  }
}


void virtual_window_draw_char(const struct VirtualWindow* window, int x, int y, const chtype ch) {
  int abs_x = window->offset_x + x;
  int abs_y = window->offset_y + y;
  if (!virtual_screen_is_inside(abs_x, abs_y) || !virtual_window_is_inside(window, x, y)) {
    return;
  }
  virtual_screen_set_char(abs_x, abs_y, ch);
}


void virtual_window_draw(const struct VirtualWindow* window) {
  int width = window->width;
  int height = window->height;
  log_info_f("width=%d,height=%d", width, height);
  for (int i = 0; i < buffer_length(window); i++) {
    int x = buffer_x(window, i);
    int y = buffer_y(window, i);
    if (window->has_border) {
      if (x == 0 && y == 0) {
        virtual_window_draw_char(window, x, y, ACS_ULCORNER);  // '┌'
      } else if (x == 0 && y == height - 1) {
        virtual_window_draw_char(window, x, y, ACS_LLCORNER);  // '└'
      } else if (x == width - 1 && y == 0) {
        virtual_window_draw_char(window, x, y, ACS_URCORNER);  // '┐'
      } else if (x == width - 1 && y == height - 1) {
        virtual_window_draw_char(window, x, y, ACS_LRCORNER);  // '┘'
      } else if (x == 0 || x == width - 1) {
        virtual_window_draw_char(window, x, y, ACS_VLINE);  // '│'
      } else if (y == 0 || y == height - 1) {
        virtual_window_draw_char(window, x, y, ACS_HLINE);  // '─'
      } else {
        virtual_window_draw_char(window, x, y, window->pixels[i].character);
      }
    } else {
      virtual_window_draw_char(window, x, y, window->pixels[i].character);
    }
  }
}


void virtual_window_center(struct VirtualWindow* window) {
  window->offset_x = (g_virtual_screen.width - window->width) / 2;
  window->offset_y = (g_virtual_screen.height - window->height) / 2;
}


chtype screen_index(int x, int y) {
  assert_f(virtual_screen_is_inside(x, y), "Invalid screen coordinates: {x: %d, y: %d}", x, y);
  return (y * g_virtual_screen.width) + x;
}


size_t screen_buffer_length() {
  return g_virtual_screen.width * g_virtual_screen.height;
}


int private_get(int x, int y) {
  return g_virtual_screen.screen[screen_index(x, y)].character;
}


void private_screen_clear() {
  for (int i = 0; i < screen_buffer_length(); i++) {
    g_virtual_screen.screen[i].character = ' ';
    g_virtual_screen.screen[i].color_pair_id = 0;
  }
}


void virtual_screen_init() {
  g_virtual_screen.screen = NULL;
  g_virtual_screen.width = 0;
  g_virtual_screen.height = 0;
}


void virtual_screen_setup() {
  struct Terminal terminal;
  terminal_init(&terminal);
  g_virtual_screen.width = terminal.width;
  g_virtual_screen.height = terminal.height;
  g_virtual_screen.screen = malloc(sizeof(*g_virtual_screen.screen) * terminal.width * terminal.height);
  private_screen_clear();
}


void virtual_screen_reset() {
  if (g_virtual_screen.screen != NULL) {
    free(g_virtual_screen.screen);
  }
  virtual_screen_setup();
}


void virtual_screen_set_char(int x, int y, const chtype ch) {
  if (virtual_screen_is_inside(x, y)) {
    g_virtual_screen.screen[screen_index(x, y)].character = ch;
  }
}


void virtual_screen_set_char_and_color(int x, int y, const chtype ch, ColorPairId color_pair_id) {
  if (virtual_screen_is_inside(x, y)) {
    struct VirtualPixel* pixel = &g_virtual_screen.screen[screen_index(x, y)];
    pixel->character = ch;
    pixel->color_pair_id = color_pair_id;
  }
}


void virtual_screen_set_string(int x, int y, const char* string) {
  for (int i = 0; i < strlen(string); i++) {
    virtual_screen_set_char(x + i, y, string[i]);
  }
}


void virtual_screen_render() {
  erase();
  for (int x = 0; x < g_virtual_screen.width; x++) {
    for (int y = 0; y < g_virtual_screen.height; y++) {
      struct VirtualPixel* pixel = &g_virtual_screen.screen[screen_index(x, y)];
      int color_pair = COLOR_PAIR(pixel->color_pair_id);
      attron(color_pair);
      mvaddch(y, x, pixel->character);
      attroff(color_pair);
    }
  }
  refresh();
  private_screen_clear();
}


int virtual_screen_center_x() {
  return g_virtual_screen.width / 2;
}


int virtual_screen_center_y() {
  return g_virtual_screen.height / 2;
}


int virtual_screen_get_width() {
  return g_virtual_screen.width;
}


int virtual_screen_get_height() {
  return g_virtual_screen.height;
}