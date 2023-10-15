#ifndef MAIN_MENU_H
#define MAIN_MENU_H


#include "window.h"
#include "terminal.h"
#include "util.h"
#include "color.h"
#include "cursor.h"


enum MainMenuSelection {
  MAIN_MENU_SELECTION_START,
  MAIN_MENU_SELECTION_MANUAL,
  MAIN_MENU_SELECTION_QUIT,
  MAIN_MENU_SELECTION_MAX,
};


struct WindowDefinition {
  const char* title;
  const char** menu_items;
  const int nb_menu_items;
  const int width;
  const int height;
  int selection;
};


void main_menu_render_items(const struct WindowDefinition* window_definition);
void main_menu_next_selection(struct WindowDefinition* window_definition);
void main_menu_previous_selection(struct WindowDefinition* window_definition);
struct WindowDefinition* main_menu_get_definition();
int main_menu_get_selection(struct WindowDefinition* window_definition);


#endif
