#include "test_suite.h"


static void _single_test() {
  array_test();
}


void test_suite_run() {
  event_on_program_start();
  if (TEST_MODE == TEST_MODE_SINGLE_TEST) {
    event_on_system_start();
    _single_test();
    event_on_system_release();
  } else if (TEST_MODE == TEST_MODE_TEST_SUITE) {
    void (*fs[])(void) = {
      color_test,
      virtual_screen_test,
      window_manager_2_test,
      virtual_cursor_2_test,
      log_buffer_test,
      sprite_loader_test,
      arena_test
    };
    for (int i = 0; i < array_size(fs); i++) {
      event_on_system_start();
      fs[i]();
      event_on_system_release();
    }
  }
  event_on_program_shutdown();
  log_info("Test suite completed.");
  exit(0);
}