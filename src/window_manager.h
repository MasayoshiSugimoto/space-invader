#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H


#include <stdbool.h>
#include <curses.h>
#include <ncurses.h>
#include "color.h"
#include "virtual_screen.h"
#include "virtual_pixel.h"
#include "sprite_buffer.h"
#include "cursor.h"
#include "virtual_window_2.h"
#include "array_virtual_window.h"


#define WINDOW_MANAGER_WIDTH_MAX 800
#define WINDOW_MANAGER_HEIGHT_MAX 600


// Structure containing the vertices of a window. All vertices are inside the window.
struct WindowVertex {
  int top;
  int right;
  int bottom;
  int left;
};


void window_manager_window_init(struct VirtualWindow2* window);
void window_manager_window_draw(struct VirtualWindow2* window);
int window_manager_window_get_outer_offset_x(const struct VirtualWindow2* window);
int window_manager_window_get_outer_offset_y(const struct VirtualWindow2* window);
int window_manager_window_get_outer_width(const struct VirtualWindow2* window);
int window_manager_window_get_outer_height(const struct VirtualWindow2* window);
int window_manager_window_get_outer_left(const struct VirtualWindow2* window);
int window_manager_window_get_outer_right(const struct VirtualWindow2* window);
int window_manager_window_get_outer_top(const struct VirtualWindow2* window);
int window_manager_window_get_outer_bottom(const struct VirtualWindow2* window);
bool window_manager_window_is_inside_screen(const struct VirtualWindow2* window);
bool window_manager_window_is_inside_relative(const struct VirtualWindow2* window, int x, int y);
bool window_manager_window_is_inside_absolute(const struct VirtualWindow2* window, int x, int y);
bool window_manager_window_is_inside_window(const struct VirtualWindow2* window_contained, const struct VirtualWindow2* window_container);
bool window_manager_window_is_inside_window_completely(const struct VirtualWindow2* window_contained, const struct VirtualWindow2* window_container);
void window_manager_window_center_screen_x(struct VirtualWindow2* window);
void window_manager_window_center_screen_y(struct VirtualWindow2* window);
void window_manager_window_align_top_screen(struct VirtualWindow2* window);
void window_manager_window_align_right_screen(struct VirtualWindow2* window);
void window_manager_window_align_bottom_screen(struct VirtualWindow2* window);
void window_manager_window_align_left_screen(struct VirtualWindow2* window);
struct WindowVertex window_manager_vertex_get(const struct VirtualWindow2* window);
void window_manager_cursor_show(struct VirtualWindow2* window, int x, int y);
void window_manager_cursor_blink(struct VirtualWindow2* window, int x, int y);
void window_manager_cursor_hide();


#endif
