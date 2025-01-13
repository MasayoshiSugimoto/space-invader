#ifndef INPUT_H
#define INPUT_H


#include "keyboard.h"


struct InputMapping {
  KeyboardKey key;
  void (*action)(KeyboardKey key);
};


KeyboardKey input_get(void);
KeyboardKey input_process(const struct InputMapping* input_mappings, int length, KeyboardKey key);


#endif

