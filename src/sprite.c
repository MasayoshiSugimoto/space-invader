#include "sprite.h"


struct Sprite {
  enum SpriteId sprite_id;
  const char* file_name;
  const char* as_string;
  int width;
  int height;
};


struct SpriteConfig {
  enum SpriteId sprite_id;
  const char* sprite_id_as_string;
  const char* file_name;
};


const struct SpriteConfig sprite_configs[] = {
  {SPRITE_ID_SPACESHIP, "SPRITE_ID_SPACESHIP", "spaceship.txt"},
};


struct Sprite sprites[SPRITE_ID_MAX];


const char* load_sprite(const char* file_name) {
  char path_buf[1024];
  strcpy(path_buf, SPRITE_DIRECTORY);
  strcat(path_buf, "/");
  strcat(path_buf, file_name);

  FILE* file = fopen(path_buf, "r");
  if (file == NULL) {
    log_fatal_f("Could not load `%s`.", path_buf);
  }
  log_info_f("Loading sprite: %s", path_buf);

  fseek(file, 0L, SEEK_END);
  int length = ftell(file);
  if (length == 0) return "";
  rewind(file);
  char* buf = malloc(sizeof(char) * length + 1);
  for (int i = 0; i < length; i++) {
    buf[i] = fgetc(file);
  }
  buf[length] = 0;  // End the string.

  fclose(file);
  return buf;
}


int sprite_get_height(const char* sprite_as_string) {
  int count = 0; 
  for (int i = 0; i < strlen(sprite_as_string); i++) {
    if (sprite_as_string[i] == '\n') {
      count++;
    }
  }
  return count;
}


int sprite_get_width(const char* sprite_as_string) {
  int width = 0;
  int line_size = 0;
  for (int i = 0; i < strlen(sprite_as_string); i++) {
    switch (sprite_as_string[i]) {
      case '\r':
        // Ignore.
        break;
      case '\n':
        width = imax(width, line_size);
        line_size = 0;
        break;
      default:
        line_size++;
    }
  }
  return width;
}


const char* sprite_get_sprite_id_as_string(enum SpriteId sprite_id) {
  for (int i = 0; i < array_size(sprite_configs); i++) {
    const struct SpriteConfig* sprite_config = &sprite_configs[i];
    if (sprite_config->sprite_id == sprite_id) {
      return sprite_config->sprite_id_as_string;
    }
  }
  log_fatal_f("Invalid sprite id: %d", sprite_id);
}


void sprite_log(struct Sprite* sprite) {
  const char* sprite_id = sprite_get_sprite_id_as_string(sprite->sprite_id);
  log_info_f(
      "{sprite_id=%s, file_name=%s, as_string=see below, width=%d, height=%d}",
      sprite_id,
      sprite->file_name,
      sprite->width,
      sprite->height
  );
  log_info_f("Rendering sprite %s:\n%s", sprite_id, sprite->as_string);
}


void sprite_init() {
  // TODO: Add a bunch of assert to avoid apocalypse.
  for (int i = 0; i < array_size(sprite_configs); i++) {
    const struct SpriteConfig* config = &sprite_configs[i];
    const char* sprite_as_string = load_sprite(config->file_name);

    struct Sprite* sprite = &sprites[config->sprite_id];
    sprite->sprite_id = config->sprite_id;
    sprite->file_name = config->file_name;
    sprite->as_string = sprite_as_string;
    sprite->width = sprite_get_width(sprite_as_string);
    sprite->height = sprite_get_height(sprite_as_string);

    sprite_log(sprite);
  }
}


const char* sprite_as_string(enum SpriteId sprite_id) {
  return sprites[sprite_id].as_string;
}


