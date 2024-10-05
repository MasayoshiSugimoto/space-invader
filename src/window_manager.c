#include "window_manager.h"


#define WINDOW_MANAGER_WINDOW_MAX 16
#define WINDOW_MANAGER_WIDTH_MAX 800
#define WINDOW_MANAGER_HEIGHT_MAX 600
#define WINDOW_MANAGER_WINDOW_PIXEL_MAX (WINDOW_MANAGER_WIDTH_MAX * WINDOW_MANAGER_HEIGHT_MAX)
#define WINDOW_MANAGER_PIXEL_MAX (WINDOW_MANAGER_WINDOW_PIXEL_MAX * WINDOW_MANAGER_WINDOW_MAX)


static struct VirtualWindow _windows[WINDOW_MANAGER_WINDOW_MAX];
static struct VirtualPixel _pixels[WINDOW_MANAGER_PIXEL_MAX];
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
  pixel->color_pair_id = COLOR_COLOR_PAIR_ID_DEFAULT;
}


int _window_pixels_get_offset(struct VirtualWindow* window) {
  return _get_window_index(window) * WINDOW_MANAGER_WINDOW_PIXEL_MAX;
}


void window_manager_init(void) {
  memset(&_windows, 0, sizeof(_windows));
  memset(&_pixels, 0, sizeof(_pixels));
  for (int i = 0; i < WINDOW_MANAGER_PIXEL_MAX; i++) {
    _pixels[i].color_pair_id = COLOR_COLOR_PAIR_ID_DEFAULT;
  }
  memset(&_window_is_active, 0, sizeof(_window_is_active));
}


struct VirtualWindow* window_manager_window_new(int width, int height) {
  int window_index = _get_next_free_window_index();
  assert(window_index >= 0, "No more available window.");
  _window_is_active[window_index] = true;
  struct VirtualWindow* window = &_windows[window_index];
  window->width = width;
  window->height = height;
  window->offset_x = 0;
  window->offset_y = 0;
  window->has_border = false;
  window_manager_window_clear(window);
  return window;
}


void window_manager_window_release(struct VirtualWindow* window) {
  int window_index = _get_window_index(window);
  assert(window_index >= 0, "Unknown window.");
  assert(_window_is_active[window_index], "Inconsistent active flag.");
  _window_is_active[window_index] = false;
}


void window_manager_window_release_all(void) {
  window_manager_init();
}


void window_manager_window_draw(struct VirtualWindow* window) {
  int pixel_offset = _window_pixels_get_offset(window);
  for (int i = 0; i < _pixels_get_length(window); i++) {
    int x = _pixels_get_x(window, i) + window->offset_x;
    int y = _pixels_get_y(window, i) + window->offset_y;
    struct VirtualPixel pixel = _pixels[pixel_offset + i];
    if (!window->is_transparent || pixel.character != ' ') {
      virtual_screen_set_char_and_color(x, y, pixel.character, pixel.color_pair_id);
    }
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
  int pixel_offset = _window_pixels_get_offset(window);
  for (int i = 0; i < _pixels_get_length(window); i++) {
    _pixel_clear(&_pixels[pixel_offset + i]);
  }
}


void window_manager_window_fill_character(struct VirtualWindow* window, chtype character) {
  int pixel_offset = _window_pixels_get_offset(window);
  for (int i = 0; i < _pixels_get_length(window); i++) {
    _pixels[pixel_offset + i].character = character;
  }
}


void window_manager_window_set_pixel(struct VirtualWindow* window, int x, int y, struct VirtualPixel pixel) {
  int pixel_offset = _window_pixels_get_offset(window);
  if (_pixel_is_inside(window, x, y)) {
    _pixels[pixel_offset + _pixels_get_index(window, x, y)] = pixel;
  }
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


bool window_manager_window_is_inside_screen(const struct VirtualWindow* window) {
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


bool window_manager_window_is_inside(const struct VirtualWindow* window, int x, int y) {
  return window->offset_x <= x && x < window->offset_x + window->width
    && window->offset_y <= y && y < window->offset_y + window->height;
}


struct VirtualWindow* window_manager_window_setup_from_sprite(const struct Sprite* sprite) {
  struct VirtualWindow* window = window_manager_window_new(sprite->width, sprite->height);
  window->has_border = false;
  for (int y = 0; y < sprite->height; y++) {
    for (int x = 0; x < sprite->width; x++) {
      struct VirtualPixel pixel = {sprite->as_matrix[y][x], COLOR_COLOR_PAIR_ID_DEFAULT};
      window_manager_window_set_pixel(window, x, y, pixel);
    }
  }
  return window;
}


void window_manager_window_center_screen_x(struct VirtualWindow* window) {
  window->offset_x = virtual_screen_center_x() - window->width / 2;
}


void window_manager_window_center_screen_y(struct VirtualWindow* window) {
  window->offset_y = virtual_screen_center_y() - window->height / 2;
}


void window_manager_window_align_top_screen(struct VirtualWindow* window) {
  window->offset_y = window->has_border ? 1 : 0;
}


void window_manager_window_align_right_screen(struct VirtualWindow* window) {
  window->offset_x = virtual_screen_get_width() - window->width - (window->has_border ? 1 : 0);
}


void window_manager_window_align_bottom_screen(struct VirtualWindow* window) {
  window->offset_y = virtual_screen_get_height() - window->height - (window->has_border ? 1 : 0);
}


void window_manager_window_align_left_screen(struct VirtualWindow* window) {
  window->offset_x = window->has_border ? 1 : 0;
}