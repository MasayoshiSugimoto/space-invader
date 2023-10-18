#ifndef UI_H
#define UI_H


#include "menu.h"
#include "terminal.h"
#include "manual.h"
#include "color.h"
#include "start_screen.h"
#include "sprite.h"
#include "screen.h"


/**
 * This struct is expected to contain all UI singletons.
 */
struct UI {
  struct Terminal terminal;
  struct Manual manual;
};


void ui_init(struct UI* ui);


#endif
