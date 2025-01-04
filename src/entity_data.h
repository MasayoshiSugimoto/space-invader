#ifndef ENTITY_DATA_H
#define ENTITY_DATA_H


#include "vector.h"
#include "sprite.h"
#include "faction_component.h"


struct EntityData {
  struct Vector coordinates;
  enum SpriteId sprite_id;
  bool active;
  enum FactionId faction_id;
  const char* sprite_file_name;
};


#endif