#include "game.h"


const char* g_game_state_strings[] = {
  "GAME_STATE_START_MENU",
  "GAME_STATE_IN_GAME",
  "GAME_STATE_GAME_OVER",
  "GAME_STATE_GAME_WON",
  "GAME_STATE_MENU",
  "GAME_STATE_MANUAL",
  "GAME_STATE_START_SCREEN",
  "GAME_STATE_CREDITS",
  "GAME_STATE_QUIT",
  "GAME_STATE_MAX"
};


const struct Entity entity_init_data[] = {
  {1, {10, 1}},
  {2, {17, 1}},
  {3, {24, 1}},
  {4, {31, 1}},
  {5, {38, 1}},
  {6, {45, 1}},
  {7, {52, 1}},
  {8, {0, 0}},
  {9, {0, 0}},
  {10, {0, 0}},
};


struct SpriteComponentData {
  EntityId entity_id;
  enum SpriteId sprite_id;
  bool active;
};


const struct SpriteComponentData sprite_component_data[] = {
  {1, SPRITE_ID_ALIEN, true},
  {2, SPRITE_ID_ALIEN, true},
  {3, SPRITE_ID_ALIEN, true},
  {4, SPRITE_ID_ALIEN, true},
  {5, SPRITE_ID_ALIEN, true},
  {6, SPRITE_ID_ALIEN, true},
  {7, SPRITE_ID_ALIEN, true},
  {8, SPRITE_ID_SPACESHIP_BULLET, false},
  {9, SPRITE_ID_SPACESHIP_BULLET, false},
  {10, SPRITE_ID_SPACESHIP_BULLET, false},
};


void game_init_spaceship(struct Game* game) {
  EntityId entity_id = entity_system_create_entity(game->entity_system);
  sprite_component_setup(entity_id, SPRITE_ID_SPACESHIP);
  game->spaceship_id = entity_id;
  enum SpriteId sprite_id = sprite_component_get_sprite_id(entity_id);
  const struct Sprite* sprite = sprite_get_sprite(sprite_id);
  struct Vector v = {
    SCREEN_WIDTH / 2 - sprite->width / 2,
    SCREEN_HEIGHT - sprite->height
  };
  entity_system_set_coordinates(game->entity_system, entity_id, v);
  sprite_component_set_active(entity_id, true);
}


void game_init_entities(struct EntitySystem* entity_system) {
  for (int i = 0; i < array_size(entity_init_data); i++) {
    EntityId entity_id = entity_system_create_entity(entity_system);
    entity_system_set_coordinates(entity_system, entity_id, entity_init_data[i].coordinates);
    for (int j = 0; j < array_size(sprite_component_data); j++) {
      if (sprite_component_data[j].entity_id != entity_init_data[i].entity_id) continue;
      struct SpriteComponentUnit sprite_unit = sprite_component_get(entity_id);
      sprite_unit.sprite_id = sprite_component_data[j].sprite_id;
      sprite_unit.active = sprite_component_data[j].active;
      sprite_component_set(&sprite_unit);
    }
    enum SpriteId sprite_id = sprite_component_get_sprite_id(entity_id);
    log_info_f("Entity created: {id=%ld, sprite=%s}", entity_id, sprite_get_file_name(sprite_id));
  }
}


void game_init(struct Game* game) {
  log_info("game_init(game)");
  game->cursor.x = 0;
  game->cursor.y = 0;
  game->game_state = GAME_STATE_IN_GAME;
  game->entity_system = entity_system_create();
  game->last_frame_time_millisecond = get_current_millisecond();

  sprite_component_init();
  entity_system_init(game->entity_system);
  game_init_spaceship(game);
  game_init_entities(game->entity_system);

  enemy_ai_basic_init();
  bullet_component_init();
}


void game_print_state(enum GameState game_state) {
  log_info_f("Game state: %s", g_game_state_strings[game_state]);
}


void game_set_game_state(struct Game* game, enum GameState game_state) {
  log_info_f("Game state set to: %s", g_game_state_strings[game_state]);
  if (game_state >= GAME_STATE_MAX) return;
  game->game_state = game_state;
}


void game_update(struct Game* game) {
  uint64_t now_millisecond = get_current_millisecond();
  uint64_t delta_time_millisecond = now_millisecond - game->last_frame_time_millisecond;
  game->last_frame_time_millisecond = now_millisecond;
  enemy_ai_basic_update(game->entity_system, delta_time_millisecond);
  bullet_component_update(game->entity_system, delta_time_millisecond);

  bullet_component_cleanup(game->entity_system);
}
