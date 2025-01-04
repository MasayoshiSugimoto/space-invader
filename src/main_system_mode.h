#ifndef MAIN_SYSTEM_MODE_H
#define MAIN_SYSTEM_MODE_H


enum MainSystemModeStatus {
    MAIN_SYSTEM_MODE_RUNNING,
    MAIN_SYSTEM_MODE_DONE,
};


struct MainSystemMode {
    const char* name;
    void (*init)(void);
    void (*release)(void);
    void (*input_update)(void);
    enum MainSystemModeStatus (*system_update)(void);
    void (*render)(void);
};


void main_system_mode_set(const struct MainSystemMode* main_system_mode);
const struct MainSystemMode* main_system_mode_get(void);
void main_system_no_op(void);


#endif