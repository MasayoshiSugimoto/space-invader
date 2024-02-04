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
    window->buffer[i] = ch;
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


void virtual_window_init(struct VirtualWindow* window) {
  window->buffer = NULL;
  window->width = 0;
  window->height = 0;
  window->offset_x = 0;
  window->offset_y = 0;
  window->has_border = true;
}


void virtual_window_setup(struct VirtualWindow* window, int width, int height, int offset_x, int offset_y) {
  if (window->buffer != NULL) {
    free(window->buffer);
  }
  int length = width * height;
  window->buffer = malloc(sizeof(chtype) * length);
  window->width = width;
  window->height = height;
  window->offset_x = offset_x;
  window->offset_y = offset_y;
  window->has_border = true;
  for (int i = 0; i < buffer_length(window); i++) {
    window->buffer[i] = ' ';
  }
}


void virtual_window_setup_from_sprite(struct VirtualWindow* window, const struct Sprite* sprite) {
  virtual_window_setup(window, sprite->width, sprite->height, 0, 0);
  window->has_border = false;
  for (int y = 0; y < sprite->height; y++) {
    for (int x = 0; x < sprite->width; x++) {
      if (sprite->as_matrix[y][x] != ' ') {
        virtual_window_set_buffer(window, y * sprite->width + x, sprite->as_matrix[y][x]);
      }
    }
  }
}


void virtual_window_delete(struct VirtualWindow* window) {
  free(window->buffer);
}


void virtual_window_set_string(struct VirtualWindow* window, const char* string, int x, int y) {
  for (int i = 0; i < strlen(string); i++) {
    virtual_window_set_buffer(window, buffer_index(window, x, y) + i, string[i]);
  }
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
        virtual_window_draw_char(window, x, y, window->buffer[i]);
      }
    } else {
      virtual_window_draw_char(window, x, y, window->buffer[i]);
    }
  }
}


int virtual_window_center_x(const struct VirtualWindow* window, const char* string) {
  return (window->width - strlen(string)) / 2;
}


int virtual_window_center_y(const struct VirtualWindow* window) {
  return window->height / 2;
}


void virtual_window_center(struct VirtualWindow* window) {
  window->offset_x = (g_virtual_screen.width - window->width) / 2;
  window->offset_y = (g_virtual_screen.height - window->height) / 2;
}


chtype screen_index(int x, int y) {
  return (y * g_virtual_screen.width) + x;
}


size_t screen_buffer_length() {
  return g_virtual_screen.width * g_virtual_screen.height;
}


int private_get(int x, int y) {
  return g_virtual_screen.screen[screen_index(x, y)];
}


void private_screen_clear() {
  for (int i = 0; i < screen_buffer_length(); i++) {
    g_virtual_screen.screen[i] = ' ';
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
  g_virtual_screen.screen = malloc(sizeof(chtype) * terminal.width * terminal.height);
  private_screen_clear();
}


void virtual_screen_reset() {
  if (g_virtual_screen.screen != NULL) {
    free(g_virtual_screen.screen);
  }
  virtual_screen_setup();
}


void virtual_screen_set_char(int x, int y, const chtype ch) {
  g_virtual_screen.screen[screen_index(x, y)] = ch;
}


void virtual_screen_set_string(int x, int y, const char* string) {
  for (int i = 0; i < strlen(string); i++) {
    virtual_screen_set_char(x + i, y, string[i]);
  }
}


void virtual_screen_render() {
  for (int x = 0; x < g_virtual_screen.width; x++) {
    for (int y = 0; y < g_virtual_screen.height; y++) {
      mvaddch(y, x, private_get(x, y));
    }
  }
}


int virtual_screen_center_x() {
  return g_virtual_screen.width / 2;
}


int virtual_screen_center_y() {
  return g_virtual_screen.height / 2;
}