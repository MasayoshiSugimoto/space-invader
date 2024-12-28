#ifndef START_SCREEN_H
#define START_SCREEN_H


#include "util.h"
#include "terminal.h"
#include "virtual_screen.h"
#include "task_status.h"
#include "cursor.h"
#include "event.h"
#include "main_system_mode.h"


struct MainSystemMode g_start_screen_main_system_mode;


void start_screen_init(void);
enum MainSystemModeStatus start_screen_update(void);
void start_screen_render(void);


#endif

