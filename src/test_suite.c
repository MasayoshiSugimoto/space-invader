#include "test_suite.h"


static void _single_test() {
  log_buffer_test();
  endwin();  // End ncurses.
  exit(0);
}


void test_suite_run() {
  event_on_start();
  if (TEST_MODE_IS_SINGLE_TEST) {
    _single_test();  // Comment out for full test.
  }
  color_test();
  virtual_screen_test();
  window_manager_2_test();
  virtual_cursor_test();
  endwin();  // End ncurses.
  exit(0);
}