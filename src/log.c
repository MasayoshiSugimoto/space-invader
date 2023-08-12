#include "log.h"


void log_init() {
  g_debug_file = fopen(LOG_FILE, "w+");
  if (g_debug_file == NULL) {
    log_fatal_f("fopen(\"%s\") failed (%d): %s\n", LOG_FILE, errno, strerror(errno));
  }
}
