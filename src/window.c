#include "window.h"

void window_move(struct Window* window, int y, int x) {
  move(window->top + y + 1, window->left + x + 1);
}


void window_addch(struct Window* window, const chtype character) {
  int x;
  int y;
  getyx(stdscr, y, x);

  if (window->left >= x) x = window->left + 1;
  if (x > window->left + window->width) {
    x = window->left + 1;
    y++;
  }

  if (window->top >= y) y = window->top + 1;
  if (y > window->top + window->width) {
    return;
  }

  mvaddch(y, x, character);
}


void window_render_center_string(struct Window* window, int y, const char* string) {
  int length = strlen(string);
  int left = window->width / 2 - length / 2;
  window_move(window, y, left);
  for (int i = 0; i < length; i++) {
    addch(string[i]);
  }
}


void window_render_center_string_selection(struct Window* window, int y, const char* string) {
  int length = strlen(string);
  int left = window->width / 2 - length / 2;
  window_move(window, y, 0);
  attron(COLOR_PAIR(COLOR_PAIR_ID_MENU_SELECTION));
  for (int i = 0; i < left; i++) {
    addch(' ');
  }
  for (int i = 0; i < length; i++) {
    addch(string[i]);
  }
  for (int i = left + length; i < window->width; i++) {
    addch(' ');
  }
  attroff(COLOR_PAIR(COLOR_PAIR_ID_MENU_SELECTION));
}


void window_render_border(struct Window* window) {
  int line = window->top;
  move(line, window->left);
  addch(ACS_ULCORNER);
  for (int x = 0; x < window->width; x++) {
    addch(ACS_HLINE);
  }
  addch(ACS_URCORNER);
  line++;

  for (int y = 0; y < window->height; y++) {
    move(line, window->left);
    addch(ACS_VLINE);
    move(line, window->left + 1 + window->width);
    addch(ACS_VLINE);
    line++;
  }

  // Print bottom border.
  move(line++, window->left);
  addch(ACS_LLCORNER);
  for (int x = 0; x < window->width; x++) {
    addch(ACS_HLINE);
  }
  addch(ACS_LRCORNER);
}
