#include "test_suite.h"


void _single_test() {
  window_manager_test();
  endwin();  // End ncurses.
  exit(0);
}


void test_suite_run() {
  _single_test();  // Comment out for full test.
  color_test();
  virtual_screen_test();
  window_manager_test();
  virtual_cursor_test();
  endwin();  // End ncurses.
  exit(0);
}