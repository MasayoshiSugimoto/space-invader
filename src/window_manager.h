#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H


#include <stdbool.h>
#include <curses.h>
#include <ncurses.h>
#include "color.h"
#include "virtual_screen.h"


#define WINDOW_MANAGER_WIDTH_MAX 800
#define WINDOW_MANAGER_HEIGHT_MAX 600


struct VirtualPixel {
  chtype character;
  ColorPairId color_pair_id;
};


struct VirtualWindow {
  // struct VirtualPixel* pixels;
  int width;
  int height;
  int offset_x;
  int offset_y;
  bool has_border;
  bool is_transparent;
};


void window_manager_init(void);
struct VirtualWindow* window_manager_window_new(int width, int height);
void window_manager_window_release(struct VirtualWindow* window);
void window_manager_window_release_all(void);
void window_manager_window_draw(struct VirtualWindow* window);
void window_manager_window_clear(struct VirtualWindow* window);
void window_manager_window_fill_character(struct VirtualWindow* window, chtype character);
void window_manager_window_set_pixel(struct VirtualWindow* window, int x, int y, struct VirtualPixel pixel);
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
struct VirtualWindow* window_manager_window_setup_from_sprite(const struct Sprite* sprite);
struct VirtualWindow* window_manager_window_set_sprite(struct VirtualWindow* window, const struct Sprite* sprite);
void window_manager_window_center_screen_x(struct VirtualWindow* window);
void window_manager_window_center_screen_y(struct VirtualWindow* window);
void window_manager_window_align_top_screen(struct VirtualWindow* window);
void window_manager_window_align_right_screen(struct VirtualWindow* window);
void window_manager_window_align_bottom_screen(struct VirtualWindow* window);
void window_manager_window_align_left_screen(struct VirtualWindow* window);


#endif
