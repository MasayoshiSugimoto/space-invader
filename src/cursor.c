#include "cursor.h"


void cursor_init(struct Cursor* cursor) {
  cursor->x = 0;
  cursor->y = 0;
}


void cursor_dump(struct Cursor* cursor) {
  log_info_f("cursor: x=%d, y=%d", cursor->x, cursor->y);
}

