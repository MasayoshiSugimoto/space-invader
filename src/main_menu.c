#include "main_menu.h"


const int LINE_BUFFER_MAX = 512;  // This should be enough to contain a line.


const char* menu_items[] = {
  "Start",
  "How to Play",
  "Quit"
};


struct WindowDefinition window_definition = {
  "Space Invader",
  menu_items,
  3,
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  MAIN_MENU_SELECTION_START
};


void main_menu_render_items(const struct WindowDefinition* window_definition) {
  struct Terminal terminal;
  terminal_init(&terminal);

  struct Window window = {
    terminal.height / 2 - window_definition->height / 2,  // top
    terminal.width / 2 - window_definition->width / 2,  // left
    window_definition->width,
    window_definition->height
  };

  const char* title = window_definition->title;
  const char** menu_items = window_definition->menu_items;
  const int nb_menu_items = window_definition->nb_menu_items;

  // 2 blank lines between title and items. 1 blank line between items.
  int content_height = 1 + 2 + nb_menu_items * 2;
  int content_width = strlen(title);
  for (int i = 0; i < nb_menu_items; i++) {
    int length = strlen(menu_items[i]);
    if (length > content_width) content_width = length;
  }

  int y = window.height / 2 - content_height / 2;
  attron(COLOR_PAIR(COLOR_PAIR_ID_MENU_TITLE));
  window_render_center_string(&window, y, title);
  y++;  // 2 lines between title and first menu item.
  char underline[LINE_BUFFER_MAX];
  int underline_index = 0;
  for (underline_index = 0; underline_index < strlen(title); underline_index++) {
    underline[underline_index] = '-';
  }
  underline[underline_index] = 0;
  window_render_center_string(&window, y, (const char *)&underline);
  attroff(COLOR_PAIR(COLOR_PAIR_ID_MENU_TITLE));

  for (int i = 0; i < nb_menu_items; i++) {
    y += 2;
    if (window_definition->selection == i) {
      window_render_center_string_selection(&window, y, menu_items[i]); 
    } else {
      window_render_center_string(&window, y, menu_items[i]); 
    }
  }

  window_render_border(&window);
}


void main_menu_next_selection(struct WindowDefinition* window_definition) {
  window_definition->selection++;
  if (window_definition->selection >= window_definition->nb_menu_items) {
    window_definition->selection = 0;
  }
}


void main_menu_previous_selection(struct WindowDefinition* window_definition) {
  if (window_definition->selection == 0) {
    window_definition->selection = window_definition->nb_menu_items - 1;
  } else {
    window_definition->selection--;
  }
}


struct WindowDefinition* main_menu_get_definition() {
  return &window_definition;
}


int main_menu_get_selection(struct WindowDefinition* window_definition) {
  return window_definition->selection;
}
