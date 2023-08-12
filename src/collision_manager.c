/********************************************************************************
 * This file manages collisions between entities.
 *
 * Collision will occur between sprites of opposite battalion. To start with,
 * we will detect collisions no a character base. We will modify in case it
 * is not sufficient.
 *******************************************************************************/


#include "collision_manager.h"


struct CollisionManager {
  char buffer[SCREEN_WIDTH * SCREEN_HEIGHT];
  bool is_collision[ENTITY_MAX];
} collision_manager;


struct SpriteInfo {
  bool active;
  enum SpriteId sprite_id;
  int width;
  int height;
  int character_count;
  int x;
  int y;
  const char* const* as_matrix;
  EntityId entity_id;
};


struct SpriteInfo sprite_infos[ENTITY_MAX];


void print_sprite(const struct SpriteInfo* sprite_info, int min_x, int min_y, int buffer_width) {
  int begin_x = sprite_info->x - min_x;
  int begin_y = sprite_info->y - min_y;

  for (int y = 0; y < sprite_info->height; y++) {
    for (int x = 0; x < sprite_info->width; x++) {
      collision_manager.buffer[(x + begin_x) + (y + begin_y) * buffer_width] = sprite_info->as_matrix[y][x];
    }
  }
}


void print_status() {
  for (int i = 0; i < array_size(collision_manager.is_collision); i++) {
    log_info_f("Collision status: {%d=%s}", i, boolean_as_string(collision_manager.is_collision[i]));
  }
}


void print_sprite_info(const struct SpriteInfo* sprite_info) {
  log_info_f(
      "SprintInfo: {"
        "active=%s, "
        "sprite_id=%d, "
        "width=%d, "
        "height=%d, "
        "character_count=%d, "
        "x=%d, "
        "y=%d"
      "}",
      boolean_as_string(sprite_info->active),
      sprite_info->sprite_id,
      sprite_info->width,
      sprite_info->height,
      sprite_info->character_count,
      sprite_info->x,
      sprite_info->y
  );
}


/********************************************************************************
 * Print every pair of sprites in a buffer relative to their respective positions
 * in the game. If the number of characters in the buffer is smaller than the
 * sum of the characters of both sprites, we consider it to be a collision.
 *******************************************************************************/
void collision_manager_update(struct EntitySystem* entity_system) {
  for (int entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    collision_manager.is_collision[entity_id] = false;
  }

  for (int entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    struct SpriteComponentUnit unit = sprite_component_get(entity_id);
    struct SpriteInfo* sprite_info = &sprite_infos[entity_id];
    struct Vector v = entity_system_get_coordinates(entity_system, entity_id);
    if (unit.active) {
      const struct Sprite* sprite = sprite_get_sprite(unit.sprite_id);

      sprite_info->active = true;
      sprite_info->sprite_id = unit.sprite_id;
      sprite_info->width = sprite->width;
      sprite_info->height = sprite->height;
      sprite_info->character_count = sprite->character_count;
      sprite_info->x = v.x;
      sprite_info->y = v.y;
      sprite_info->as_matrix = sprite->as_matrix;
      sprite_info->entity_id = entity_id;
    } else {
      sprite_info->active = false;
      sprite_info->sprite_id = SPRITE_ID_MAX;
      sprite_info->width = 0;
      sprite_info->height = 0;
      sprite_info->character_count = 0;
      sprite_info->x = v.x;
      sprite_info->y = v.y;
      sprite_info->as_matrix = NULL;
      sprite_info->entity_id = entity_id;
    }
  }

  for (int entity_id_1 = 0; entity_id_1 < ENTITY_MAX; entity_id_1++) {
    struct SpriteInfo* sprite_info_1 = &sprite_infos[entity_id_1];
    if (!sprite_info_1->active) continue;

    for (int entity_id_2 = entity_id_1 + 1; entity_id_2 < ENTITY_MAX; entity_id_2++) {
      struct SpriteInfo* sprite_info_2 = &sprite_infos[entity_id_2];
      if (!sprite_info_2->active) continue;

      int min_x = imin(sprite_info_1->x, sprite_info_2->x);
      int min_y = imin(sprite_info_1->y, sprite_info_2->y);
      int max_x = imax(
          sprite_info_1->x + sprite_info_1->width,
          sprite_info_2->x + sprite_info_2->width
      );
      int max_y = imax(
          sprite_info_1->y + sprite_info_1->height,
          sprite_info_2->y + sprite_info_2->height
      );

      int buf_width = max_x - min_x;
      int buf_height = max_y - min_y;
      int buf_size = buf_width * buf_height;

      for (int i = 0; i < buf_size; i++) {
        collision_manager.buffer[i] = ' ';
      }

      print_sprite(sprite_info_1, min_x, min_y, buf_width);
      print_sprite(sprite_info_2, min_x, min_y, buf_width);

      int character_count = 0;
      for (int i = 0; i < buf_size; i++) {
        if (collision_manager.buffer[i] != ' ') character_count++;
      }

      if (sprite_info_1->character_count + sprite_info_2->character_count > character_count) {
        collision_manager.is_collision[entity_id_1] = true;
        collision_manager.is_collision[entity_id_2] = true;
      }
    }
  }
}


bool collision_manager_is_collision(EntityId entity_id) {
  assert_entity_id(entity_id);
  return collision_manager.is_collision[entity_id];
}
