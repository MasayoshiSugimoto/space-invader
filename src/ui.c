#include "ui.h"


#define UI_MENU_WIDTH 31
#define UI_MENU_HEIGHT 15


void ui_init_ncurses() {
  
}


void ui_init(struct UI* ui) {
  ui_init_ncurses();
  color_init();
  manual_init(&ui->manual);
  sprite_init();
  screen_init(screen_get_screen());
}
