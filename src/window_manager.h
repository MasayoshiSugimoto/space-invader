#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H


#include <stdbool.h>
#include <curses.h>
#include <ncurses.h>
#include "color.h"
#include "virtual_screen.h"


void window_manager_init(void);
struct VirtualWindow* window_manager_window_new(int width, int height);
void window_manager_window_release(struct VirtualWindow* window);
void window_manager_window_release_all(void);
void window_manager_window_draw(struct VirtualWindow* window);
void window_manager_window_clear(struct VirtualWindow* window);
void window_manager_window_fill_character(struct VirtualWindow* window, chtype character);
void window_manager_window_set_offset_x(struct VirtualWindow* window, int offset_x);
void window_manager_window_set_offset_y(struct VirtualWindow* window, int offset_y);
void window_manager_window_set_border(struct VirtualWindow* window, bool has_border);
void window_manager_window_set_pixel(struct VirtualWindow* window, int x, int y, struct VirtualPixel pixel);
int window_manager_window_get_width(const struct VirtualWindow* window);
int window_manager_window_get_height(const struct VirtualWindow* window);
int window_manager_window_get_offset_x(const struct VirtualWindow* window);
int window_manager_window_get_offset_y(const struct VirtualWindow* window);
int window_manager_window_get_outer_offset_x(const struct VirtualWindow* window);
int window_manager_window_get_outer_offset_y(const struct VirtualWindow* window);
int window_manager_window_get_outer_width(const struct VirtualWindow* window);
int window_manager_window_get_outer_height(const struct VirtualWindow* window);
int window_manager_window_get_outer_left(const struct VirtualWindow* window);
int window_manager_window_get_outer_right(const struct VirtualWindow* window);
int window_manager_window_get_outer_top(const struct VirtualWindow* window);
int window_manager_window_get_outer_bottom(const struct VirtualWindow* window);
bool window_manager_window_is_inside_screen(const struct VirtualWindow* window);
bool window_manager_window_is_inside(const struct VirtualWindow* window, int x, int y);


#endif
