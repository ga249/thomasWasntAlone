#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

#include "gfc_types.h"
#include "entity.h"

int collision_sphere_sphere(Vector3D s1pos,float s1Radius,Vector3D s2pos,float s2Radius);

int collision_ent_ent(Entity *ent1, Entity *ent2);

#endif