#ifndef ENTITY_DATA_H
#define ENTITY_DATA_H


#include <stdint.h>
#include "vector.h"
#include "faction_component.h"


struct EntityData {
  uint16_t friendly_id;
  struct Vector coordinates;
  bool active;
  enum FactionId faction_id;
  const char* sprite_file_name;
  bool is_basic_ai_active;
  const char* animation_name;
  uint8_t z;
  bool deactivate_collision;
};


#endif