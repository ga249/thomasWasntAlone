#include <stdlib.h>
#include <string.h>

#include "simple_logger.h"

#include "entity.h"

typedef struct
{
    Entity *entity_list;
    Uint32  entity_count;
    
}EntityManager;

static EntityManager entity_manager = {0};

void entity_system_close()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        entity_free(&entity_manager.entity_list[i]);        
    }
    free(entity_manager.entity_list);
    memset(&entity_manager,0,sizeof(EntityManager));
    slog("entity_system closed");
}

void entity_system_init(Uint32 maxEntities)
{
    entity_manager.entity_list = gfc_allocate_array(sizeof(Entity),maxEntities);
    if (entity_manager.entity_list == NULL)
    {
        slog("failed to allocate entity list, cannot allocate ZERO entities");
        return;
    }
    entity_manager.entity_count = maxEntities;
    atexit(entity_system_close);
    slog("entity_system initialized");
}

Entity *entity_new()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet, so we can!
        {
            entity_manager.entity_list[i]._inuse = 1;
            gfc_matrix_identity(entity_manager.entity_list[i].modelMat);
            entity_manager.entity_list[i].scale.x = 1;
            entity_manager.entity_list[i].scale.y = 1;
            entity_manager.entity_list[i].scale.z = 1;
            return &entity_manager.entity_list[i];
        }
    }
    slog("entity_new: no free space in the entity list");
    return NULL;
}

void entity_free(Entity *self)
{
    if (!self)return;
    //MUST DESTROY
    gf3d_model_free(self->model);
    memset(self,0,sizeof(Entity));
}


void entity_draw(Entity *self)
{
    if (!self)return;
    gf3d_model_draw(self->model,self->modelMat);
}

void entity_draw_all()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        entity_draw(&entity_manager.entity_list[i]);
    }
}

void entity_think(Entity *self)
{
    if (!self)return;
    if (self->think)
    {
        //if (self->entType != ENT_PLAYER)
        //{
        //    self->think(self);
        //}else{
        //    if(self->activePlayer)self->think(self);
        //}
        self->think(self);
    }
}

void entity_think_all()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        entity_think(&entity_manager.entity_list[i]);
    }
}


void entity_update(Entity *self)
{
    if (!self)return;
    // HANDLE ALL COMMON UPDATE STUFF

    if (self->hasGravity)
    {
        if(!ent_is_grounded(self))
        {
            self->acceleration.z = -.005;
        }else if (ent_is_grounded(self)){
            self->position.z += .5;
            self->position.z = 0;
            self->acceleration.z = 0;
        }
    }
    
    vector3d_add(self->position,self->position,self->velocity);
    vector3d_add(self->velocity,self->acceleration,self->velocity);
    
    gfc_matrix_identity(self->modelMat);
    gfc_matrix_scale(self->modelMat,self->scale);
    
    gfc_matrix_rotate(self->modelMat,self->modelMat,self->rotation.z,vector3d(0,0,1));
    gfc_matrix_rotate(self->modelMat,self->modelMat,self->rotation.y,vector3d(0,1,0));
    gfc_matrix_rotate(self->modelMat,self->modelMat,self->rotation.x,vector3d(1,0,0));
    
    gfc_matrix_translate(self->modelMat,self->position);
    
    if (self->update)self->update(self);
}

void entity_update_all()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        entity_update(&entity_manager.entity_list[i]);
    }
}

Entity *entity_get_active_player()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        if (entity_manager.entity_list[i].activePlayer == 1)
        {
            return &entity_manager.entity_list[i];
        }
    }
    slog("Active player doesn't exist");
    return NULL;
}

Entity *entity_get_player_by_name(char *charName)
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        if (strcmp(entity_manager.entity_list[i].charName,(const char *)charName))
        {
            return &entity_manager.entity_list[i];
        }
    }
    slog("CharName %s doesn't exist", charName);
    return NULL;
}

int entity_is_active_player()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        if (entity_manager.entity_list[i].activePlayer == 1)
        {
            return 1;
        }
    }
    return 0;
}

int ent_is_grounded(Entity *ent)
{
    float test;
    test = ent->position.z -.1;
    if (test < 0.0)
    {
        return 1;
    }else{
        return 0;
    }
}
/*eol@eof*/
