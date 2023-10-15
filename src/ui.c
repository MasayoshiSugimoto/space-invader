#include "ui.h"


#define UI_MENU_WIDTH 31
#define UI_MENU_HEIGHT 15


void ui_init_ncurses() {
  initscr();
  noecho();
  cbreak();
  nodelay(stdscr, true);
  notimeout(stdscr, true);
  keypad(stdscr, TRUE);
}


void ui_init(struct UI* ui) {
  ui_init_ncurses();
  color_init();
  manual_init(&ui->manual);
  start_screen_init(&ui->start_screen);
  sprite_init();
  screen_init(screen_get_screen());
}
