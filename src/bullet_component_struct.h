#ifndef BULLET_COMPONENT_STRUCT_H
#define BULLET_COMPONENT_STRUCT_H


#include "entity_system.h"


enum BulletState {
	BULLET_STATE_MOVING,
	BULLET_STATE_EXPLODING,
};


struct BulletComponent {
    EntityId entity_id;
		enum BulletState state;
    bool active;
};
 

#endif
