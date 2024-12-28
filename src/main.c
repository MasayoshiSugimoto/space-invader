#include <time.h>
#include "input.h"
#include "consts.h"
#include "game.h"
#include "screen.h"
#include "color.h"
#include "window.h"
#include "main_menu.h"
#include "virtual_screen.h"
#include "test_suite.h"
#include "event.h"
#include "main_system_mode.h"


/********************************************************************************
* Main
********************************************************************************/


int main() {
  #if TEST_MODE_ENABLE
    test_suite_run();
  #endif

  event_on_start();
  const struct MainSystemMode* main_system_mode = NULL;

  // Loop to track cursor position
  while (true) {
    event_on_frame_start();
    if (main_system_mode != main_system_mode_get()) {
      main_system_mode = main_system_mode_get();
      main_system_mode->init();
    }
    event_on_render_start();
    main_system_mode->render();
    event_on_render_end();
    main_system_mode->input_update();
    if (main_system_mode->system_update() == MAIN_SYSTEM_MODE_DONE) {
      break;
    }
  }

  endwin();  // End ncurses.
  return 0;
}

