#ifndef __TELEPAD_H__
#define __TELEPAD_H__

#include "gfc_types.h"
#include "entity.h"

/**
 * @brief provide a pointer to a new telepad
 * @param position a vector3d for center of telepad
 * @return pointer to telepad entity
 */
Entity *telepad_new(Vector3D position);

Entity *telepad_make_pair(Entity *telepad, Vector3D position);

void telepad_think(Entity *self);

void telepad_update(Entity *self);

#endif