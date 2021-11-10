#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__

#include "entity.h"

#define CHAR_1  1
#define CHAR_2  2
#define CHAR_3  3
#define CHAR_4  4
#define CHAR_5  5

Entity *character_ball_spawn(Vector3D position);

Entity *character_box_spawn(Vector3D position);

Entity *character_tallBoi_spawn(Vector3D position);

Entity *character_smallBoi_spawn(Vector3D position);

Entity *character_fatBoi_spawn(Vector3D position);

Entity *character_spawn_by_name(char *name, Vector3D position);

#endif