#include "virtual_screen.h"


size_t buffer_length(const struct VirtualWindow* window) {
  return window->width * window->height;
}


chtype buffer_index(const struct VirtualWindow* window, int x, int y) {
  return y * window->width + x;
}


void virtual_window_init(struct VirtualWindow* window) {
  window->buffer = NULL;
  window->width = 0;
  window->height = 0;
}


void virtual_window_setup(struct VirtualWindow* window, int width, int height) {
  window->buffer = malloc(sizeof(chtype) * width * height);
  window->width = width;
  window->height = height;
  memset(window->buffer, ' ', buffer_length(window));
}


void virtual_window_delete(struct VirtualWindow* window) {
  free(window->buffer);
}


void virtual_window_set_string(struct VirtualWindow* window, const char* string, int x, int y) {
  for (int i = 0; i < buffer_length(window); i++) {
    window->buffer[buffer_index(window, x, y) + i] = string[i];
  }
}


void virtual_window_draw(const struct VirtualWindow* window) {

}


chtype private_index(int x, int y) {
  return (y * g_virtual_screen.width) + x;
}


size_t private_screen_length() {
  return g_virtual_screen.width * g_virtual_screen.height;
}


int private_get(int x, int y) {
  return g_virtual_screen.screen[private_index(x, y)];
}


void private_screen_clear() {
  for (int i = 0; i < private_screen_length(); i++) {
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
  g_virtual_screen.screen[private_index(x, y)] = ch;
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
