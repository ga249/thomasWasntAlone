#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "gfc_types.h"
#include "entity.h"

/**
 * @brief provide a pointer to a new platform
 * @param position a vector3d to center of the button
 * @return pointer to button entity
 */
Entity *button_new(Vector3D position);

void button_think(Entity *self);

void button_update(Entity *self);

#endif