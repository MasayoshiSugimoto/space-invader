#ifndef INPUT_H
#define INPUT_H


#include "entity_spaceship.h"
#include "keyboard.h"
#include "input.h"


struct InputMapping {
  KeyboardKey key;
  void (*action)(KeyboardKey key);
};


KeyboardKey input_get(void);
KeyboardKey input_process(const struct InputMapping* input_mappings, int length, KeyboardKey key);


#endif

