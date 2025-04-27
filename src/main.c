#include <time.h>
#include <stdlib.h>
#include "consts.h"
#include "game.h"
#include "color.h"
#include "virtual_screen.h"
#include "test_suite.h"
#include "event.h"
#include "main_system_mode.h"


/********************************************************************************
* Main
********************************************************************************/


int main() {
  if (TEST_MODE == TEST_MODE_SINGLE_TEST || TEST_MODE == TEST_MODE_TEST_SUITE) {
    test_suite_run();
  }

  atexit(event_on_program_shutdown);
  event_on_program_start();
  const struct MainSystemMode* main_system_mode = NULL;

  while (true) {
    event_on_frame_start();
    if (main_system_mode != main_system_mode_get()) {
      if (main_system_mode != NULL) event_on_system_release();
      event_on_system_start();
      main_system_mode = main_system_mode_get();
      main_system_mode->init();
    }
    main_system_mode->input_update();
    if (main_system_mode->system_update() == MAIN_SYSTEM_MODE_DONE) {
      main_system_mode->release();
      break;
    }
    event_on_render_start();
    main_system_mode->render();
    event_on_render_end();
  }

  return 0;
}

