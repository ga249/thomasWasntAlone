#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

#include "gfc_types.h"
#include "entity.h"

int collision_sphere_sphere(Vector3D s1pos,float s1Radius,Vector3D s2pos,float s2Radius);

int collision_ent_ent(Entity *ent1, Entity *ent2);

int collision_bounds(Entity *ent);

int collision_mouse_rect(Vector2D mPos, Vector2D rPos, Vector2D widthHeight);

int collide_menu(SDL_Rect r1, Vector2D m);

#endif