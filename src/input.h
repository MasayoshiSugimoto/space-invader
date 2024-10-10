#ifndef INPUT_H
#define INPUT_H


#include "entity_spaceship.h"
#include "main_menu.h"
#include "keyboard.h"
#include "input.h"
#include "sprite_editor.h"


struct InputMapping {
  KeyboardKey key;
  void (*action)(KeyboardKey key);
};


void input_update(struct Game* game);
void input_process(const struct InputMapping* input_mapping, int length);


#endif

