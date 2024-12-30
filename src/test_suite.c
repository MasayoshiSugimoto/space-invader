#include "test_suite.h"


static void _single_test() {
  sprite_loader_test();
}


void test_suite_run() {
  event_on_start();
  if (TEST_MODE_IS_SINGLE_TEST) {
    _single_test();
  } else {
    color_test();
    virtual_screen_test();
    window_manager_2_test();
    virtual_cursor_test();
    log_buffer_test();
  }
  log_info("Test suite completed.");
  endwin();  // End ncurses.
  exit(0);
}