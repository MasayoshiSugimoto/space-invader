#include "main_system_mode.h"


const static struct MainSystemMode* _main_system_mode;


void main_system_mode_set(const struct MainSystemMode* main_system_mode) {
    _main_system_mode = main_system_mode;
}


const struct MainSystemMode* main_system_mode_get(void) {
    return _main_system_mode;
}


void main_system_no_op(void) {}