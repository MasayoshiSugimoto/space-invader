#include "start_screen.h"


struct VirtualWindow g_window;
const char* g_title = "SPACE INVADER";


void start_screen_init() {
  int width = SCREEN_WIDTH;
  int height = SCREEN_HEIGHT;
  virtual_window_init(&g_window);
  virtual_window_setup(
    &g_window, 
    width, 
    height, 
    virtual_screen_center_x() - width / 2, 
    virtual_screen_center_y() - height / 2
  );
}


enum TaskStatus start_screen_render() {
  if (fade_out_is_done()) {
    fade_out_stop();
    return TASK_STATUS_DONE;
  }
  virtual_screen_reset();
  virtual_window_set_string(
    &g_window, 
    g_title, 
    virtual_window_center_x(&g_window, g_title), 
    virtual_window_center_y(&g_window)
  );
  virtual_window_draw(&g_window);
  fade_out_render(&g_virtual_screen);
  return TASK_STATUS_RUNNING;
}
