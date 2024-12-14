#ifndef WINDOW_MANAGER_2_H
#define WINDOW_MANAGER_2_H


#include <stdbool.h>
#include <curses.h>
#include <ncurses.h>
#include "color.h"
#include "virtual_screen.h"
#include "virtual_pixel.h"
#include "sprite_buffer.h"
#include "cursor.h"


#define WINDOW_MANAGER_WIDTH_MAX 800
#define WINDOW_MANAGER_HEIGHT_MAX 600


struct VirtualWindow2 {
  int offset_x;
  int offset_y;
  bool has_border;
  bool is_transparent;
  const struct SpriteBuffer* buffer;
};


void window_manager_window_2_init(struct VirtualWindow2* window);
void window_manager_window_draw_2(struct VirtualWindow2* window);
struct VirtualPixel window_manager_window_get_pixel_2(const struct VirtualWindow2* window, int x, int y);
int window_manager_window_get_outer_offset_x_2(const struct VirtualWindow2* window);
int window_manager_window_get_outer_offset_y_2(const struct VirtualWindow2* window);
int window_manager_window_get_outer_width_2(const struct VirtualWindow2* window);
int window_manager_window_get_outer_height_2(const struct VirtualWindow2* window);
int window_manager_window_get_outer_left_2(const struct VirtualWindow2* window);
int window_manager_window_get_outer_right_2(const struct VirtualWindow2* window);
int window_manager_window_get_outer_top_2(const struct VirtualWindow2* window);
int window_manager_window_get_outer_bottom_2(const struct VirtualWindow2* window);
bool window_manager_window_is_inside_screen_2(const struct VirtualWindow2* window);
bool window_manager_window_is_inside_2(const struct VirtualWindow2* window, int x, int y);
void window_manager_window_center_screen_x_2(struct VirtualWindow2* window);
void window_manager_window_center_screen_y_2(struct VirtualWindow2* window);
void window_manager_window_align_top_screen_2(struct VirtualWindow2* window);
void window_manager_window_align_right_screen_2(struct VirtualWindow2* window);
void window_manager_window_align_bottom_screen_2(struct VirtualWindow2* window);
void window_manager_window_align_left_screen_2(struct VirtualWindow2* window);
void window_manager_cursor_show(struct VirtualWindow2* window, int x, int y);
void window_manager_cursor_blink(struct VirtualWindow2* window, int x, int y);
void window_manager_cursor_hide();


#endif
