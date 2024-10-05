#ifndef START_SCREEN_H
#define START_SCREEN_H


#include "util.h"
#include "window.h"
#include "terminal.h"
#include "virtual_screen.h"
#include "task_status.h"
#include "cursor.h"
#include "event.h"


void start_screen_init(void);
enum TaskStatus start_screen_render(void);


#endif

