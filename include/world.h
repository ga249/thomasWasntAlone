#ifndef __WORLD_H__
#define __WORLD_H__


#include "gfc_types.h"
#include "gfc_list.h"
#include "gfc_matrix.h"
#include "gf3d_vgraphics.h"
#include "gf3d_model.h"
#include "entity.h"

typedef struct
{
    Matrix4 modelMat;
    Model *worldModel;
    List *entityList;       //entities that exist in the world
    int numKeys;
    Entity *activeCharacter;
}World;

World *get_current_level();

Entity *get_active_character();

void active_character_think();

void active_character_update();

World *world_load(char *filename);

void world_draw(World *world);

void world_delete(World *world);

void world_run_updates(World *world);

void world_add_entity(World *world,Entity *entity);

#endif
