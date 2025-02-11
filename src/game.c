#include "game.h"


struct Game {
  enum GameState game_state;
  EntityId spaceship_id;
  uint64_t last_frame_time_millisecond;
  enum GameOverResult game_over_result;
};


static struct Game _game;


void _game_over_update(void) {
  int active_counts[FACTION_ID_MAX];
  for (int i = 0; i < FACTION_ID_MAX; i++) {
    active_counts[i] = 0;
  }
  for (int i = 0; i < ENTITY_MAX; i++) {
    if (!entity_system_is_active(i)) continue;
    if (!faction_component_is_enabled(i)) continue;
    if (bullet_component_is_active(i)) continue;
    active_counts[faction_component_faction_id_get(i)]++;
  }
  enum GameOverResult result = _game.game_over_result;
  if (active_counts[FACTION_ID_ALIEN] == 0 && active_counts[FACTION_ID_PLAYER] == 0) {
    _game.game_over_result = GAME_OVER_LOOSE;
  } else if (active_counts[FACTION_ID_ALIEN] == 0) {
    _game.game_over_result = GAME_OVER_WIN;
  } else if (active_counts[FACTION_ID_PLAYER] == 0) {
    _game.game_over_result = GAME_OVER_LOOSE;
  } else {
    _game.game_over_result = GAME_OVER_NONE;
  }
  if (result == GAME_OVER_NONE && _game.game_over_result != GAME_OVER_NONE) {
    color_color_palette_activate(COLOR_PALETTE_ID_DEFAULT);
    color_fade_start_fade_out(DURATION_ONE_SECOND);
  }
}


void game_init_entities(const struct EntityData* entity_datas, size_t entity_datas_length) {
  for (int i = 0; i < entity_datas_length; i++) {
    EntityId entity_id = entity_system_create_entity();
    const struct EntityData* entity_data_ptr = &entity_datas[i];
    if (entity_data_ptr->active) {
      entity_system_enable(entity_id);
    } else {
      entity_system_disable(entity_id);
    }
    entity_system_set_coordinates(entity_id, entity_data_ptr->coordinates);
    entity_system_set_friendly_id(entity_id, entity_data_ptr->friendly_id);

    sprite_component_enable(entity_id);
    sprite_component_sprite_buffer_set(entity_id, sprite_loader_sprite_get(entity_data_ptr->sprite_file_name));
    sprite_component_z_set(entity_id, entity_data_ptr->z);

    faction_component_set(entity_id, entity_data_ptr->faction_id);
    faction_component_enable(entity_id);

    if (entity_data_ptr->is_basic_ai_active) {
      enemy_ai_basic_activate(entity_id);
    }

    if (entity_data_ptr->animation_name != NULL) {
      animation_set(entity_id, entity_data_ptr->animation_name);
    }
    animation_is_loop_set(entity_id, entity_data_ptr->animation_is_loop);
    if (entity_data_ptr->animation_auto_start) {
      animation_start(entity_id);
    }

    if (!entity_data_ptr->deactivate_collision) {
      collision_manager_activate(entity_id);
    }
  }
}


void game_init(void) {
  log_info("game_init()");
  _game.game_state = GAME_INIT_GAME_STATE;
  _game.last_frame_time_millisecond = get_current_millisecond();
  _game.game_over_result = GAME_OVER_NONE;

  // Initialization
  sprite_component_init();
  entity_system_init();
  enemy_ai_basic_init();
  bullet_component_init();
  animation_init();

  // Setup
  sprite_component_container_set(game_screen_get());
  bullet_component_setup();
  animation_setup();
}


void game_set_game_state(enum GameState game_state) {
  log_info_f("Game state set to: %s", game_state_as_string(game_state));
  if (game_state >= GAME_STATE_MAX) return;
  _game.game_state = game_state;
}


void game_update(void) {
  sprite_component_update();
  collision_manager_update();

  uint64_t now_millisecond = get_current_millisecond();
  uint64_t delta_time_millisecond = now_millisecond - _game.last_frame_time_millisecond;
  _game.last_frame_time_millisecond = now_millisecond;
  enemy_ai_basic_update(delta_time_millisecond);
  bullet_component_update();
  animation_update();
  _game_over_update();
}


void game_render(void) {
  game_screen_render();
  sprite_component_render();
}


enum GameOverResult game_game_over_result_get(void) {
  return _game.game_over_result;
}