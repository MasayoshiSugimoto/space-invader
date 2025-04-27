#ifndef BULLET_COMPONENT_STRUCT_H
#define BULLET_COMPONENT_STRUCT_H


#include "entity_system.h"


struct BulletComponent {
    EntityId entity_id;
    bool active;
};


#endif