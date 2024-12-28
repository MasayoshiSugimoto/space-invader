#include "sprite_loader.h"


/*
The sprite loader will provide below functionalities:
- Saving one sprite
- Loading one sprite by file name
- Loading a sprite set
- Clearing all loaded sprites
- Getting one sprite after it has been loaded

When loaded, the sprite is added to a data structure owned by the sprite loader.

A sprite is saved with its palette data.
*/


#define SPRITE_LOADER_MAX_PATH_LENGTH 4096


static struct SpriteLoader {
  struct Sprite* sprites;
  int sprites_length;
} _sprite_loader;
static char _path[SPRITE_LOADER_MAX_PATH_LENGTH];


void sprite_loader_init(void) {
  log_info("Initializing sprite loader...");
  _sprite_loader.sprites = NULL;
  _sprite_loader.sprites_length = 0;
}


void sprite_loader_save(const struct Sprite* sprite) {
  strcpy(_path, SPRITE_DIRECTORY);
  strcat(_path, "/");
  strcat(_path, sprite->file_name);
  log_info_f("Saving sprite to: %s", _path);
}


void sprite_loader_load(struct Sprite* sprite, const char* file_name) {

}


void sprite_loader_load_sprite_set(const char* sprite_set_name) {

}


void sprite_loader_clear(void) {

}


struct Sprite* sprite_loader_sprite_get(const char* file_name) {
    return NULL;
}


void _sprite_loader_usage_sample(void) {
  int width = 4;
  int height = 4;
  struct Sprite sprite_1;
  sprite_init_sprite(&sprite_1, width, height);
  struct Sprite sprite_2;
  sprite_init_sprite(&sprite_2, width, height);
  // Do relevant changes to the sprites...
  sprite_loader_save(&sprite_1);
  sprite_loader_save(&sprite_2);

  sprite_loader_load_sprite_set("sprite_set_level_1");
  struct Sprite* sprite_loaded = sprite_loader_sprite_get("space_ship");
}