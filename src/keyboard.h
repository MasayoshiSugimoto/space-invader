#ifndef KEYBOARD_H
#define KEYBOARD_H


#include "ncurses.h"
#include "util.h"
#include "log.h"


typedef int KeyboardKey;


const char* keyboard_get_key_name(KeyboardKey key);


#endif