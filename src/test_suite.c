#include "test_suite.h"


void _single_test() {
  window_manager_test();
  exit(0);
}


void test_suite_run() {
  _single_test();  // Comment out for full test.
  color_test();
  virtual_screen_test();
  exit(0);
}