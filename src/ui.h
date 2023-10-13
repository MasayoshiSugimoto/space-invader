#ifndef UI_H
#define UI_H


#include "menu.h"
#include "game_menu.h"
#include "terminal.h"
#include "manual.h"
#include "color.h"
#include "start_screen.h"
#include "sprite.h"


/**
 * This struct is expected to contain all UI singletons.
 */
struct UI {
  struct ItemSelection game_menu;
  struct Terminal terminal;
  struct Manual manual;
  struct StartScreen start_screen;
};


void ui_init(struct UI* ui);


#endif
