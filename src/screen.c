#include "screen.h"


#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 20


void screen_init(struct Screen* screen) {
  int width = SCREEN_WIDTH;
  int height = SCREEN_HEIGHT;

  screen->width = width;
  screen->height = height;
  screen->screen_buffer = malloc(sizeof(ScreenCharacter) * width * height);
  for (int i = 0; i < array_size(screen->windows); i++) {
    screen->windows[i].position = VZERO;
    screen->windows[i].sprite_id = SPRITE_ID_NONE;
  }
}


void screen_render_border(const struct Screen* screen, const struct Vector screen_offset) {
  int left = screen_offset.x - 1;
  int line = screen_offset.y - 1;
  log_info_f("corner={%d, %d}", left, line);

  // Print top border.
  move(line, left);
  addch(ACS_ULCORNER);
  for (int x = 0; x < screen->width; x++) {
    addch(ACS_HLINE);
  }
  addch(ACS_URCORNER);
  line++;

  for (int y = 0; y < screen->height; y++) {
    move(line, left);
    addch(ACS_VLINE);
    move(line, left + 1 + screen->width);
    addch(ACS_VLINE);
    line++;
  }

  // Print bottom border.
  move(line++, left);
  addch(ACS_LLCORNER);
  for (int x = 0; x < screen->width; x++) {
    addch(ACS_HLINE);
  }
  addch(ACS_LRCORNER);
}


struct Vector screen_get_offset(const struct Screen* screen, const struct Terminal* terminal) {
  struct Vector center = terminal_center(terminal);
  struct Vector result = {
    center.x - screen->width / 2,
    center.y - screen->height / 2
  };
  return result;
}


void screen_render_entities(const struct Screen* screen, const struct Vector screen_offset, const struct EntitySystem* entity_system) {
  const struct SpriteComponent* sprite_component = &entity_system->sprite_component;
  for (int i = 0; i < ENTITY_MAX; i++) {
    enum SpriteId sprite_id = sprite_component->sprite_id[i];
    if (sprite_id == SPRITE_ID_NONE) continue;
    struct Vector top_left = vector_add(entity_system->coordinates[i], screen_offset);
    const struct Sprite* sprite = sprite_get_sprite(sprite_id);
    for (int y = 0; y < sprite->height; y++) {
      move(top_left.y + y, top_left.x);
      for (int x = 0; x < sprite->width; x++) {
        addch(sprite->as_matrix[y][x]);
      }
    }
  }
}


void screen_render(struct Screen* screen, struct Terminal* terminal, struct Game* game) {
  const struct Vector screen_offset = screen_get_offset(screen, terminal);

  screen_render_entities(screen, screen_offset, game->entity_system);
  screen_render_border(screen, screen_offset);
}
