#include "ui.h"


#define UI_MENU_WIDTH 31
#define UI_MENU_HEIGHT 15


void ui_init(struct UI* ui) {
  manual_init(&ui->manual);
}
