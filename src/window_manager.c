#include "window_manager.h"


#define WINDOW_MANAGER_WINDOW_MAX 16


static struct VirtualWindow _windows[WINDOW_MANAGER_WINDOW_MAX];
static bool _window_is_active[WINDOW_MANAGER_WINDOW_MAX];


size_t _pixels_get_length(struct VirtualWindow* window) {
  return window->width * window->height;
}


unsigned int _pixels_get_x(struct VirtualWindow* window, int i) {
  return i % window->width;
}


unsigned int _pixels_get_y(struct VirtualWindow* window, int i) {
  return i / window->width;
}


int _pixels_get_index(struct VirtualWindow* window, int x, int y) {
  return window->width * y + x;
}


int _get_next_free_window_index() {
  for (int i = 0; i < WINDOW_MANAGER_WINDOW_MAX; i++) {
    if (!_window_is_active[i]) {
      return i;
    }
  }
  return -1;
}


int _get_window_index(struct VirtualWindow* window) {
  for (int i = 0; i < WINDOW_MANAGER_WINDOW_MAX; i++) {
    if (window == &_windows[i]) return i;
  }
  return -1;
}


bool _pixel_is_inside(struct VirtualWindow* window, int x, int y) {
  return 0 <= x && x < window->width && 0 <= y && y < window->height;
}


void _pixel_clear(struct VirtualPixel* pixel) {
  pixel->character = ' ';
  pixel->color_pair_id = 0;
}


void window_manager_init() {
  memset(&_windows, 0, sizeof(_windows));
}


struct VirtualWindow* window_manager_window_new(int width, int height) {
  int window_index = _get_next_free_window_index();
  assert(window_index >= 0, "No more available window.");
  _window_is_active[window_index] = true;
  struct VirtualWindow* window = &_windows[window_index];
  assert(window->pixels == NULL, "Window is already allocated.");
  window->width = width;
  window->height = height;
  window->offset_x = 0;
  window->offset_y = 0;
  window->has_border = false;
  window->pixels = malloc(sizeof(*window->pixels) * width * height);
  return window;
}


void window_manager_window_release(struct VirtualWindow* window) {
  assert(window->pixels != NULL, "`window->pixels` already deleted.");
  int window_index = _get_window_index(window);
  assert(window_index >= 0, "Unknown window.");
  assert(_window_is_active[window_index], "Inconsistent active flag.");
  free(window->pixels);
  window->pixels = NULL;
  _window_is_active[window_index] = false;
}


void window_manager_window_draw(struct VirtualWindow* window) {
  for (int i = 0; i < _pixels_get_length(window); i++) {
    int x = _pixels_get_x(window, i) + window->offset_x;
    int y = _pixels_get_y(window, i) + window->offset_y;
    struct VirtualPixel* pixel = &window->pixels[i];
    virtual_screen_set_char_and_color(x, y, pixel->character, pixel->color_pair_id);
  }

  if (window->has_border) {
      int top = window_manager_window_get_outer_top(window);
      int right = window_manager_window_get_outer_right(window);
      int bottom = window_manager_window_get_outer_bottom(window);
      int left = window_manager_window_get_outer_left(window);
      virtual_screen_set_char(left, top, ACS_ULCORNER /*┌*/);
      virtual_screen_set_char(right, top, ACS_URCORNER /*┐*/);
      virtual_screen_set_char(right, bottom, ACS_LRCORNER /*┘*/);
      virtual_screen_set_char(left, bottom, ACS_LLCORNER /*└*/);
      for (int x = window->offset_x; x < window->offset_x + window->width; x++) {
        virtual_screen_set_char(x, top, ACS_HLINE /*─*/);
        virtual_screen_set_char(x, bottom, ACS_HLINE /*─*/);
      }
      for (int y = window->offset_y; y < window->offset_y + window->height; y++) {
        virtual_screen_set_char(left, y, ACS_VLINE /*│*/);
        virtual_screen_set_char(right, y, ACS_VLINE /*│*/);
      }
  }
}


void window_manager_window_clear(struct VirtualWindow* window) {
  assert(window->pixels != NULL, "`window->pixels` already deleted.");
  for (int i = 0; i < _pixels_get_length(window); i++) {
    _pixel_clear(&window->pixels[i]);
  }
}


void window_manager_window_fill_character(struct VirtualWindow* window, chtype character) {
  assert(window->pixels != NULL, "`window->pixels` already deleted.");
  for (int i = 0; i < _pixels_get_length(window); i++) {
    struct VirtualPixel* pixel = &window->pixels[i];
    pixel->character = character;
  }
}


void window_manager_window_set_offset_x(struct VirtualWindow* window, int offset_x) {
  window->offset_x = offset_x;
}


void window_manager_window_set_offset_y(struct VirtualWindow* window, int offset_y) {
  window->offset_y = offset_y;
}


void window_manager_window_set_border(struct VirtualWindow* window, bool has_border) {
  window->has_border = has_border;
}


void window_manager_window_set_pixel(struct VirtualWindow* window, int x, int y, struct VirtualPixel pixel) {
  if (_pixel_is_inside(window, x, y)) {
    window->pixels[_pixels_get_index(window, x, y)] = pixel;
  }
}


int window_manager_window_get_width(const struct VirtualWindow* window) {
  return window->width;
}


int window_manager_window_get_height(const struct VirtualWindow* window) {
  return window->height;
}


int window_manager_window_get_offset_x(const struct VirtualWindow* window) {
  return window->offset_x;
}


int window_manager_window_get_offset_y(const struct VirtualWindow* window) {
  return window->offset_y;
}


int window_manager_window_get_outer_offset_x(const struct VirtualWindow* window) {
  return window->offset_x - 1;
}


int window_manager_window_get_outer_offset_y(const struct VirtualWindow* window) {
  return window->offset_y - 1;
}


int window_manager_window_get_outer_width(const struct VirtualWindow* window) {
  return window->width + 2;
}


int window_manager_window_get_outer_height(const struct VirtualWindow* window) {
  return window->height + 2;
}


int window_manager_window_get_outer_left(const struct VirtualWindow* window) {
  int delta = window->has_border ? 1 : 0;
  return window->offset_x - delta;
}


int window_manager_window_get_outer_right(const struct VirtualWindow* window) {
  int delta = window->has_border ? 0 : 1;
  return window->offset_x + window->width - delta;
}


int window_manager_window_get_outer_top(const struct VirtualWindow* window) {
  int delta = window->has_border ? 1 : 0;
  return window->offset_y - delta;
}


int window_manager_window_get_outer_bottom(const struct VirtualWindow* window) {
  int delta = window->has_border ? 0 : 1;
  return window->offset_y + window->height - delta;
}


int window_manager_window_is_inside_screen(const struct VirtualWindow* window) {
  if (window_manager_window_get_outer_left(window) >= virtual_screen_get_width()) {
    return false;
  } else if (window_manager_window_get_outer_right(window) < 0) {
    return false;
  } else if (window_manager_window_get_outer_bottom(window) < 0) {
    return false;
  } else if (window_manager_window_get_outer_top(window) >= virtual_screen_get_height()) {
    return false;
  }
  return true;
}


