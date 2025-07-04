#include "window_manager.h"


enum BufferType {
  BUFFER_TYPE_SPRITE,
  BUFFER_TYPE_LOG,
  BUFFER_TYPE_MAX
};


static int _get_width(const struct VirtualWindow* window) {
  return sprite_buffer_get_width(window->buffer);
}


static int _get_height(const struct VirtualWindow* window) {
  return sprite_buffer_get_height(window->buffer);
}


void window_manager_window_init(struct VirtualWindow* window) {
  window->offset_x = 0;
  window->offset_y = 0;
  window->has_border = false;
  window->is_transparent = false;
  window->buffer = NULL;
  window->container = NULL;
  window->z = 0;
}


void window_manager_window_draw(struct VirtualWindow* window) {
  int width = _get_width(window);
  int height = _get_height(window);
  for (int x = 0; x < width; x++) {
    int x_abs = x + window->offset_x;
    for (int y = 0; y < height; y++) {
      int y_abs = y + window->offset_y;
      if (window->container != NULL && !window_manager_window_is_inside_absolute(window->container, x_abs, y_abs)) {
        continue;
      }
      struct VirtualPixel pixel = sprite_buffer_get(window->buffer, x, y);
      if (pixel.character == 0) continue;
      if (!window->is_transparent) {
        virtual_screen_set_char_and_color(x_abs, y_abs, pixel.character, pixel.color_pair_id);
      } else if (window->is_transparent && pixel.character != 0) {
        virtual_screen_set_char_and_color(x_abs, y_abs, pixel.character, pixel.color_pair_id);
      } 
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
    for (int x = window->offset_x; x < window->offset_x + width; x++) {
      virtual_screen_set_char(x, top, ACS_HLINE /*─*/);
      virtual_screen_set_char(x, bottom, ACS_HLINE /*─*/);
    }
    for (int y = window->offset_y; y < window->offset_y + height; y++) {
      virtual_screen_set_char(left, y, ACS_VLINE /*│*/);
      virtual_screen_set_char(right, y, ACS_VLINE /*│*/);
    }
  }
}


int window_manager_window_get_outer_offset_x(const struct VirtualWindow* window) {
  return window->offset_x - 1;
}


int window_manager_window_get_outer_offset_y(const struct VirtualWindow* window) {
  return window->offset_y - 1;
}


int window_manager_window_get_outer_width(const struct VirtualWindow* window) {
  return _get_width(window) + 2;
}


int window_manager_window_get_outer_height(const struct VirtualWindow* window) {
  return _get_height(window) + 2;
}


int window_manager_window_get_outer_left(const struct VirtualWindow* window) {
  int delta = window->has_border ? 1 : 0;
  return window->offset_x - delta;
}


int window_manager_window_get_outer_right(const struct VirtualWindow* window) {
  int delta = window->has_border ? 0 : 1;
  return window->offset_x + _get_width(window) - delta;
}


int window_manager_window_get_outer_top(const struct VirtualWindow* window) {
  int delta = window->has_border ? 1 : 0;
  return window->offset_y - delta;
}


int window_manager_window_get_outer_bottom(const struct VirtualWindow* window) {
  int delta = window->has_border ? 0 : 1;
  return window->offset_y + _get_height(window) - delta;
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


bool window_manager_window_is_inside_relative(const struct VirtualWindow* window, int x, int y) {
  return 0 <= x && x < _get_width(window)
    && 0 <= y && y < _get_height(window);
}


bool window_manager_window_is_inside_absolute(const struct VirtualWindow* window, int x, int y) {
  struct WindowVertex v = window_manager_vertex_get(window);
  return v.left <= x && x <= v.right
    && v.top <= y && y <= v.bottom;
}


bool window_manager_window_is_inside_window(const struct VirtualWindow* window_contained, const struct VirtualWindow* window_container) {
  struct WindowVertex contained_vertex = window_manager_vertex_get(window_contained);
  struct WindowVertex container_vertex = window_manager_vertex_get(window_container);
  return (
    (container_vertex.left <= contained_vertex.left && contained_vertex.left <= container_vertex.right)
    || (container_vertex.left <= contained_vertex.right && contained_vertex.right <= container_vertex.right)
  ) && (
    (container_vertex.top <= contained_vertex.top && contained_vertex.top <= container_vertex.bottom)
    || (container_vertex.top <= contained_vertex.bottom && contained_vertex.bottom <= container_vertex.bottom)
  );
}


bool window_manager_window_is_inside_window_completely(
  const struct VirtualWindow* window_contained, 
  const struct VirtualWindow* window_container
) {
  if (!window_manager_window_is_inside_absolute(
    window_container, 
    window_contained->offset_x, 
    window_contained->offset_y
  )) return false;
  if (!window_manager_window_is_inside_absolute(
    window_container, 
    window_contained->offset_x + _get_width(window_contained) - 1, 
    window_contained->offset_y
  )) return false;
  if (!window_manager_window_is_inside_absolute(
    window_container, 
    window_contained->offset_x + _get_width(window_contained) - 1, 
    window_contained->offset_y + _get_height(window_contained) - 1
  )) return false;
  if (!window_manager_window_is_inside_absolute(
    window_container, 
    window_contained->offset_x, 
    window_contained->offset_y + _get_height(window_contained) - 1
  )) return false;
  return true;
}


void window_manager_window_center_screen_x(struct VirtualWindow* window) {
  window->offset_x = virtual_screen_center_x() - _get_width(window) / 2;
}


void window_manager_window_center_screen_y(struct VirtualWindow* window) {
  window->offset_y = virtual_screen_center_y() - _get_height(window) / 2;
}


void window_manager_window_align_top_screen(struct VirtualWindow* window) {
  window->offset_y = window->has_border ? 1 : 0;
}


void window_manager_window_align_right_screen(struct VirtualWindow* window) {
  window->offset_x = virtual_screen_get_width() - _get_width(window) - (window->has_border ? 1 : 0);
}


void window_manager_window_align_bottom_screen(struct VirtualWindow* window) {
  window->offset_y = virtual_screen_get_height() - _get_height(window) - (window->has_border ? 1 : 0);
}


void window_manager_window_align_left_screen(struct VirtualWindow* window) {
  window->offset_x = window->has_border ? 1 : 0;
}


struct WindowVertex window_manager_vertex_get(const struct VirtualWindow* window) {
  struct WindowVertex v = {
    .top = window->offset_y,
    .right = imax(window->offset_x + _get_width(window) - 1, 0),
    .bottom = imax(window->offset_y + _get_height(window) - 1, 0),
    .left = window->offset_x,
  };
  return v;
}


void window_manager_cursor_show(struct VirtualWindow* window, int x, int y) {
  int absolute_x = window->offset_x + x;
  int absolute_y = window->offset_y + y;
  if (window_manager_window_is_inside_relative(window, x, y) && virtual_screen_is_inside(absolute_x, absolute_y)) {
    move(absolute_y, absolute_x);
    curs_set(CURSOR_VISIBILITY_NORMAL);
  } else {
    curs_set(CURSOR_VISIBILITY_INVISIBLE);
  }
}


void window_manager_cursor_blink(struct VirtualWindow* window, int x, int y) {
  int absolute_x = window->offset_x + x;
  int absolute_y = window->offset_y + y;
  if (window_manager_window_is_inside_relative(window, x, y) && virtual_screen_is_inside(absolute_x, absolute_y)) {
    move(absolute_y, absolute_x);
    curs_set(CURSOR_VISIBILITY_HIGH_VISIBILITY);
  } else {
    curs_set(CURSOR_VISIBILITY_INVISIBLE);
  }
}


void window_manager_cursor_hide() {
  curs_set(CURSOR_VISIBILITY_INVISIBLE);
}