#ifndef START_SCREEN_H
#define START_SCREEN_H


#include "util.h"
#include "window.h"
#include "terminal.h"
#include "virtual_screen.h"
#include "post_effect.h"
#include "task_status.h"


void start_screen_init();
enum TaskStatus start_screen_render();


#endif

