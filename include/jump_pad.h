#ifndef __JUMP_PAD_H__
#define __JUMP_PAD_H__

#include "gfc_types.h"
#include "entity.h"

/**
 * @brief provide a pointer to a new jump pad
 * @param position a vector3d for center of jump pad
 * @return pointer to jump pad entity
 */
Entity *jpad_new(Vector3D position);

void jpad_think(Entity *self);

void jpad_update(Entity *self);

#endif