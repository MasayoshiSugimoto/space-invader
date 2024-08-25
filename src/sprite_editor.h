#ifndef SPRITE_EDITOR_H
#define SPRITE_EDITOR_H


#include <stdbool.h>
#include "virtual_screen.h"
#include "terminal.h"
#include "game.h"
#include "keyboard.h"
#include "ui.h"
#include "cursor.h"
#include "color.h"


void sprite_editor_init();
void sprite_editor_render();
void sprite_editor_enable(struct Game* game, struct UI* ui, KeyboardKey key);
void sprite_editor_input_update(KeyboardKey key);


#endif