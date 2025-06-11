#include "log.h"


static struct _IO_FILE* g_debug_file;

 
void log_init(void) {
  g_debug_file = fopen(LOG_FILE, "w+");
  if (g_debug_file == NULL) {
    log_fatal_f("fopen(\"%s\") failed (%d): %s\n", LOG_FILE, errno, strerror(errno));
  }
}


struct _IO_FILE* log_debug_file_get(void) {
  return g_debug_file;
}