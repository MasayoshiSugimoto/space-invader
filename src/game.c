#include "game.h"


struct Game {
  enum GameState game_state;
  EntityId spaceship_id;
  uint64_t last_frame_time_millisecond;
};


static struct Game _game;


void game_init_entities(const struct EntityData* entity_datas, size_t entity_datas_length) {
  struct EntitySystem* entity_system = entity_system_get();
  for (int i = 0; i < entity_datas_length; i++) {
    EntityId entity_id = entity_system_create_entity(entity_system);
    const struct EntityData* entity_data_ptr = &entity_datas[i];
    entity_system_set_coordinates(entity_system, entity_id, entity_data_ptr->coordinates);

    struct SpriteComponentUnit sprite_unit = sprite_component_get(entity_id);
    sprite_unit.sprite_id = entity_data_ptr->sprite_id;
    sprite_unit.active = entity_data_ptr->active;
    sprite_unit.sprite_buffer = sprite_loader_sprite_get(entity_data_ptr->sprite_file_name);
    sprite_component_set(&sprite_unit);

    faction_component_set(entity_id, entity_data_ptr->faction_id);
    enum SpriteId sprite_id = sprite_component_get_sprite_id(entity_id);
    log_info_f("Entity created: {id=%ld, sprite=%s}", entity_id, sprite_get_file_name(sprite_id));

    if (entity_data_ptr->is_basic_ai_active) {
      enemy_ai_basic_activate(i);
    }
  }
}


void game_init(void) {
  log_info("game_init()");
  _game.game_state = GAME_INIT_GAME_STATE;
  _game.last_frame_time_millisecond = get_current_millisecond();

  // sprite_component_init();
  entity_system_init();

  // animation_init();

  enemy_ai_basic_init();
  // bullet_component_init();

  sprite_component_container_set(game_screen_get());
}


void game_set_game_state(enum GameState game_state) {
  log_info_f("Game state set to: %s", game_state_as_string(game_state));
  if (game_state >= GAME_STATE_MAX) return;
  _game.game_state = game_state;
}


void game_apply_collision_to_enemies() {
  // for (EntityId entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
  //   if (
  //       collision_manager_is_collision(entity_id)
  //       && sprite_component_get_sprite_id(entity_id) == SPRITE_ID_ALIEN
  //   ) {
  //     animation_set(entity_id, ANIMATION_ID_EXPLOSION);
  //   }
  // }
}


void game_update(void) {
  collision_manager_update();
  game_apply_collision_to_enemies();

  uint64_t now_millisecond = get_current_millisecond();
  uint64_t delta_time_millisecond = now_millisecond - _game.last_frame_time_millisecond;
  _game.last_frame_time_millisecond = now_millisecond;
  enemy_ai_basic_update(delta_time_millisecond);
  bullet_component_update(delta_time_millisecond);
  animation_update(delta_time_millisecond);
  bullet_component_cleanup();
  sprite_component_update();
}


void game_render(void) {
  game_screen_render();
  sprite_component_render();
}