#include "start_screen.h"


void start_screen_render() {
  struct Terminal terminal;
  terminal_init(&terminal);

  struct Window terminal_window = {
    0,  // top
    0,  // left
    terminal.width,  // width
    terminal.height  // height
  };

  window_render_center_string(&terminal_window, terminal_window.height / 2, "Space Invader");
}
