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


struct EntityData {
  EntityId entity_id;
  struct Vector coordinates;
  enum SpriteId sprite_id;
  bool active;
  enum FactionId faction_id;
};


const struct EntityData entity_data[] = {
  {0, {0, 0}, SPRITE_ID_SPACESHIP, true, FACTION_ID_PLAYER},
  {1, {10, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN},
  {2, {17, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN},
  {3, {24, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN},
  {4, {31, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN},
  {5, {38, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN},
  {6, {45, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN},
  {7, {52, 1}, SPRITE_ID_ALIEN, true, FACTION_ID_ALIEN},
};


bool is_spaceship(EntityId entity_id) {
  enum SpriteId sprite_id = sprite_component_get_sprite_id(entity_id);
  return sprite_id == SPRITE_ID_SPACESHIP;
}


void game_init_spaceship_coordinates(struct EntitySystem* entity_system) {
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (!is_spaceship(entity_id)) continue;
    screen_set_entity_alignment(screen_get_screen(), entity_system, entity_id, SCREEN_ALIGNMENT_BOTTOM_CENTER);
  }
}


void game_init_entities(struct EntitySystem* entity_system) {
  for (int i = 0; i < array_size(entity_data); i++) {
    EntityId entity_id = entity_system_create_entity(entity_system);
    const struct EntityData* entity_data_ptr = &entity_data[i];
    entity_system_set_coordinates(entity_system, entity_id, entity_data_ptr->coordinates);

    struct SpriteComponentUnit sprite_unit = sprite_component_get(entity_id);
    sprite_unit.sprite_id = entity_data_ptr->sprite_id;
    sprite_unit.active = entity_data_ptr->active;
    sprite_component_set(&sprite_unit);

    faction_component_set(entity_id, entity_data_ptr->faction_id);
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
  game_init_entities(game->entity_system);
  game_init_spaceship_coordinates(game->entity_system);

  animation_init();

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


void game_apply_collision_to_enemies() {
  for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (
        collision_manager_is_collision(entity_id)
        && sprite_component_get_sprite_id(entity_id) == SPRITE_ID_ALIEN
    ) {
      animation_set(entity_id, ANIMATION_ID_EXPLOSION);
    }
  }
}


void game_update(struct Game* game) {
  collision_manager_update(game->entity_system);
  game_apply_collision_to_enemies();

  uint64_t now_millisecond = get_current_millisecond();
  uint64_t delta_time_millisecond = now_millisecond - game->last_frame_time_millisecond;
  game->last_frame_time_millisecond = now_millisecond;
  enemy_ai_basic_update(game->entity_system, delta_time_millisecond);
  bullet_component_update(game->entity_system, delta_time_millisecond);
  animation_update(game->entity_system, delta_time_millisecond);

  bullet_component_cleanup(game->entity_system);
}
