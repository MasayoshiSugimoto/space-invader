#include "sprite_loader.h"


/*
# DESCRIPTION

The sprite loader will provide below functionalities:
- Saving one sprite
- Loading one sprite by file name
- Loading a sprite set
- Clearing all loaded sprites
- Getting one sprite after it has been loaded

When loaded, the sprite is added to a data structure owned by the sprite loader.

# FORMAT OF THE SPRITE FILE

A sprite is saved with its palette data.

First Line:
  1. First Number: width
  2. Second Number: height
Second Block:
  - Is of size width * height
  - Contains sprite characters
Third Block:
  - Contains color data. Each cell is a number with 3 digits of range [0, 255].

Sample format below:
```
4 2
abcd
efgh
000000000000
000000000000
```

# FORMAT OF SPRITE SET FILE

```
sprite_1.dat
sprite_2.dat
sprite_3.dat
```
*/


#define SPRITE_LOADER_MAX_PATH_LENGTH 4096
#define SPRITE_LOADER_BUFFER_LENGTH 20


static struct SpriteLoader {
  struct SpriteBuffer sprites[SPRITE_LOADER_BUFFER_LENGTH];
  int sprites_length;
} _sprite_loader;
static char _path[SPRITE_LOADER_MAX_PATH_LENGTH];


void _path_sprite_get(char* buf, const char* file_name) {
  strcpy(_path, DATA_SPRITE_DIRECTORY);
  strcat(_path, "/");
  strcat(_path, file_name); 
}


void _path_sprite_set_get(char* buf, const char* file_name) {
  strcpy(_path, DATA_SPRITE_SET_DIRECTORY);
  strcat(_path, "/");
  strcat(_path, file_name); 
}


void _sprite_loader_load(struct SpriteBuffer* sprite, const char* file_name) {
  assert(file_name != NULL, "Sprite buffer file name is empty.");
  sprite_buffer_init(sprite);
  sprite_buffer_clear(sprite);
  _path_sprite_get(_path, file_name);
  log_info_f("Loading sprite from file: %s", _path);
  FILE* file = fopen(_path, "r");
  if (file == NULL) {
    log_fatal_f("Could not load sprite: `%s`.", _path);
  }
  int width;
  int height;
  int count = fscanf(file, "%d %d", &width, &height);
  char c = fgetc(file);
  assert_f(c == '\n', "New line expected. Got %c", c);
  switch (count) {
    case 0:
      log_fatal_f("Failed to load sprite: %s", _path);
    case EOF:
      log_fatal_f("Failed to load sprite: %s. EOF returned.", _path);
    case 2:
      log_info_f("Sprite loaded successfully: %s", _path);
      break;
    default:
      log_fatal_f("Failed to load all arguments for sprite: %s. count = %d", _path, count);
  }
  if (width > 0 && height > 0) {
    sprite_buffer_allocate(sprite, width, height);
    sprite_buffer_clear(sprite);
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        char c = fgetc(file);
        assert(c != EOF, "Failed to load sprite. Unexpected EOF.");
        sprite_buffer_access(sprite, x, y)->character = c;
      }
      char c = fgetc(file);
      assert(c == '\n', "Failed to load sprite. New line expected.");
    }
  }
  sprite_buffer_file_name_set(sprite, file_name);
  fclose(file);
}


void sprite_loader_init(void) {
  log_info("Initializing sprite loader...");
  for (int i = 0; i < SPRITE_LOADER_BUFFER_LENGTH; i++) {
    sprite_buffer_init(&_sprite_loader.sprites[0]);
  }
  _sprite_loader.sprites_length = 0;
}


void sprite_loader_save(const struct SpriteBuffer* sprite) {
  assert(sprite->file_name != NULL, "Sprite buffer file name is empty.");

  _path_sprite_get(_path, sprite->file_name);
  log_info_f("Saving sprite to: %s", _path);

  int length = sprite->width * sprite->height;

  FILE* file = fopen(_path, "w");
  if (file == NULL) {
    log_fatal_f("Could not load `%s`.", _path);
  }

  fprintf(file, "%d %d\n", sprite->width, sprite->height);
  if (length > 0) {
    // character count = nb cell of the sprite buffer + nb of new line character
    for (int i = 0; i < length; i++) {
      if (i != 0 && i % sprite->width == 0) {
        fputc('\n', file);
      }
      fputc(sprite->buffer[i].character, file);
    }
    fputc('\n', file);
    for (int i = 0; i < length; i++) {
      if (i != 0 && i % sprite->width == 0) {
        fputc('\n', file);
      }
      fprintf(file, "%03d", sprite->buffer[i].color_pair_id);
    }
  }

  fclose(file);
}


void sprite_loader_load_sprite_set(const char* sprite_set_file_name) {
  assert(sprite_set_file_name != NULL, "Sprite buffer set file name is empty.");
  _path_sprite_set_get(_path, sprite_set_file_name);
  log_info_f("Loading sprite set from file: %s", _path);
  FILE* file = fopen(_path, "r");
  if (file == NULL) {
    log_fatal_f("Could not load sprite set: `%s`.", _path);
  }
  char buf [SYSTEM_FILE_NAME_MAX];
  int count = 0;
  do {
    count = fscanf(file, "%s", buf);
    if (count == 0) {
      count = fscanf(file, "%s\n", buf);  
    }
    if (count == 1) {
      log_info_f("Sprite file name: %s", buf);
      struct SpriteBuffer* sprite_buffer = &_sprite_loader.sprites[_sprite_loader.sprites_length++];
      _sprite_loader_load(sprite_buffer, buf);
    }
  } while (count != EOF);
  fclose(file);
}


void sprite_loader_clear(void) {
  
}


struct SpriteBuffer* sprite_loader_sprite_get(const char* file_name) {
  assert(file_name != NULL, "File name is empty.");
  for (int i = 0; i < _sprite_loader.sprites_length; i++) {
    if (strcmp(_sprite_loader.sprites[i].file_name, file_name) == 0) {
      return &_sprite_loader.sprites[i];
    }
  }
  return NULL;
}
