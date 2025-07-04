#include "terminal.h"


void terminal_init(struct Terminal* terminal) {
  if (DEBUG_NO_SCREEN_OUTPUT) {
    terminal->height = TERMINAL_MIN_HEIGHT;
    terminal->width = TERMINAL_MIN_WIDTH;
  } else {
    getmaxyx(stdscr, terminal->height, terminal->width);
  }
}


void terminal_check_minimum_size(void) {
  struct Terminal terminal;
  terminal_init(&terminal);
  while (terminal.height < TERMINAL_MIN_HEIGHT || terminal.width < TERMINAL_MIN_WIDTH) {
    log_info_f("terminal={width:%d, height:%d}", terminal.width, terminal.height);
    log_info("Terminal is too small. Please resize the terminal.");
    erase();
    addstr(
        "Terminal is too small.\n"
        "Please resize the terminal.\n"
    );
    refresh();
    getch();  // Wait for resize.
  }
}


struct Vector terminal_center(const struct Terminal* terminal) {
  struct Vector v;
  v.x = terminal->width / 2;
  v.y = terminal->height / 2;
  return v;
}


struct Vector term_get_size(void) {
  struct Vector empty_vector;
  empty_vector.x = 0;
  empty_vector.y = 0;

  char const *const term = getenv("TERM");
  if (term == NULL) {
    log_fatal("TERM environment variable not set\n" );
    return empty_vector;
  }
  log_info_f("TERM=%s", term);

  char const *const cterm_path = ctermid(NULL);
  if (cterm_path == NULL || cterm_path[0] == '\0') {
    log_fatal("ctermid() failed\n");
    return empty_vector;
  }
  log_info_f("cterm_path=%s", cterm_path);

  int tty_fd = open(cterm_path, O_RDWR);
  if (tty_fd == -1) {
    log_fatal_f("open(\"%s\") failed (%d): %s\n", cterm_path, errno, strerror(errno));
    return empty_vector;
  }

  int setupterm_err;
  if (setupterm((char*)term, tty_fd, &setupterm_err) == ERR) {
    switch (setupterm_err) {
      case -1:
        log_fatal("setupterm() failed: terminfo database not found\n");
        goto cleanup;
      case 0:
        log_fatal_f("setupterm() failed: TERM=%s not found in database\n", term);
        goto cleanup;
      case 1:
        log_fatal("setupterm() failed: terminal is hardcopy\n");
        goto cleanup;
    } // switch
  }

  int cols = tigetnum("cols");
  if (cols < 0) {
    log_fatal_f("tigetnum(\"cols\") failed (%d)\n", cols);
  }

  int l = tigetnum("lines");
  if (l < 0) {
    log_fatal_f("tigetnum(\"lines\") failed (%d)\n", l);
  }

cleanup:
  if (tty_fd != -1) close(tty_fd);
  struct Vector v;
  v.x = cols < 0 ? 0 : cols;
  v.y = l < 0 ? 0 : l;

  char buf[256];
  vector_as_string(buf, v);
  log_info_f("Terminal size: %s", buf);
  return v;
}
