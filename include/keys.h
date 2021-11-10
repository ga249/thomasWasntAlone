#ifndef __KEYS_H__
#define __KEYS_H__

#include "gfc_types.h"
#include "entity.h"

Entity *new_key(Vector3D position,char *modelName);

void key_remove_from_character(Entity *character);

void key_think(Entity *self);

void key_update(Entity *self);

#endif