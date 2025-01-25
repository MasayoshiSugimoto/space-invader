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
#include "virtual_window.h"
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


void window_manager_window_init(struct VirtualWindow* window);
void window_manager_window_draw(struct VirtualWindow* window);
int window_manager_window_get_outer_offset_x(const struct VirtualWindow* window);
int window_manager_window_get_outer_offset_y(const struct VirtualWindow* window);
int window_manager_window_get_outer_width(const struct VirtualWindow* window);
int window_manager_window_get_outer_height(const struct VirtualWindow* window);
int window_manager_window_get_outer_left(const struct VirtualWindow* window);
int window_manager_window_get_outer_right(const struct VirtualWindow* window);
int window_manager_window_get_outer_top(const struct VirtualWindow* window);
int window_manager_window_get_outer_bottom(const struct VirtualWindow* window);
bool window_manager_window_is_inside_screen(const struct VirtualWindow* window);
bool window_manager_window_is_inside_relative(const struct VirtualWindow* window, int x, int y);
bool window_manager_window_is_inside_absolute(const struct VirtualWindow* window, int x, int y);
bool window_manager_window_is_inside_window(const struct VirtualWindow* window_contained, const struct VirtualWindow* window_container);
bool window_manager_window_is_inside_window_completely(const struct VirtualWindow* window_contained, const struct VirtualWindow* window_container);
void window_manager_window_center_screen_x(struct VirtualWindow* window);
void window_manager_window_center_screen_y(struct VirtualWindow* window);
void window_manager_window_align_top_screen(struct VirtualWindow* window);
void window_manager_window_align_right_screen(struct VirtualWindow* window);
void window_manager_window_align_bottom_screen(struct VirtualWindow* window);
void window_manager_window_align_left_screen(struct VirtualWindow* window);
struct WindowVertex window_manager_vertex_get(const struct VirtualWindow* window);
void window_manager_cursor_show(struct VirtualWindow* window, int x, int y);
void window_manager_cursor_blink(struct VirtualWindow* window, int x, int y);
void window_manager_cursor_hide();


#endif
