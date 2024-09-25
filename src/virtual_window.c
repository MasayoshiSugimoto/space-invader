#include "virtual_window.h"


static size_t buffer_length(const struct VirtualWindow* window) {
  return window->width * window->height;
}


static chtype buffer_index(const struct VirtualWindow* window, int x, int y) {
  return y * window->width + x;
}



static void virtual_window_set_buffer(struct VirtualWindow* window, int i, chtype ch) {
  if (i < buffer_length(window)) {
    window->pixels[i].character = ch;
  }
}


void virtual_window_init(struct VirtualWindow* window) {
  window->pixels = NULL;
  window->width = 0;
  window->height = 0;
  window->offset_x = 0;
  window->offset_y = 0;
  window->has_border = true;
  window->is_transparent = false;
}


void virtual_window_setup(struct VirtualWindow* window, int width, int height, int offset_x, int offset_y) {
  if (window->pixels != NULL) {
    free(window->pixels);
  }
  int length = width * height;
  window->pixels = malloc(sizeof(*window->pixels) * length);
  window->width = width;
  window->height = height;
  window->offset_x = offset_x;
  window->offset_y = offset_y;
  window->has_border = true;
  window->is_transparent = false;
  for (int i = 0; i < buffer_length(window); i++) {
    window->pixels[i].character = ' ';
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
  free(window->pixels);
}


void virtual_window_set_string(struct VirtualWindow* window, const char* string, int x, int y) {
  for (int i = 0; i < strlen(string); i++) {
    virtual_window_set_buffer(window, buffer_index(window, x, y) + i, string[i]);
  }
}


int virtual_window_center_x(const struct VirtualWindow* window, const char* string) {
  return (window->width - strlen(string)) / 2;
}


int virtual_window_center_y(const struct VirtualWindow* window) {
  return window->height / 2;
}


void virtual_window_clear(struct VirtualWindow* window, chtype clear_character) {
  for (int i = 0; i < buffer_length(window); i++) {
    window->pixels[i].character = clear_character;
  }
}


void virtual_window_set(struct VirtualWindow* window, int x, int y, chtype character) {
  window->pixels[buffer_index(window, x, y)].character = character;
}


void virtual_window_set_transparency(struct VirtualWindow* window, bool is_transparent) {
  window->is_transparent = is_transparent;
}


bool virtual_window_get_transparency(struct VirtualWindow* window) {
  return window->is_transparent;
}