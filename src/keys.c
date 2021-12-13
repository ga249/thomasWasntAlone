#include "simple_logger.h"
#include "gfc_list.h"
#include "keys.h"
#include "collisions.h"
#include "world.h"


#define KEY_OFFSET 2.5


Entity *new_key(Vector3D position,char *modelName)
{
    Entity *ent = NULL;
    Vector3D scale = {.5,.5,.5};
    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no key for you!");
        return NULL;
    }
    if (!modelName)
    {
        slog("No modelname provided for key");
        return NULL;
    }
    ent->model = gf3d_model_load(modelName);
    ent->think = key_think;
    ent->update = key_update;
    vector3d_copy(ent->position,position);
    ent->scale = scale;
    ent->entType = ENT_KEY;
    ent->hasGravity = 0;
    ent->hbType = HB_SPHERE;
    ent->hbRadius = 2;
    return ent;
}

void keys2d_add_to_list(Entity *ent)
{
    Sprite *sprite;
    sprite = gf3d_sprite_load("images/2dKey.png",1024,1024, 1);

    gfc_list_prepend(ent->keys2d,sprite);

}

void key_think(Entity *self)
{
    if(!self)return;
    if(self->target)
    {
        if(self->target->char_ID == get_active_character()->char_ID)return;
    }
    if (collision_ent_ent(self,get_active_character()))
    {
        if(self->target)
        {
            gfc_list_delete_data(self->target->keys,self);
            gfc_list_delete_data(self->target->keys2d,self);
            self->target->keyCount -= 1;
        }
        
        self->target = get_active_character();
        gfc_list_prepend(self->target->keys, self);
        self->target->keyCount += 1;
        keys2d_add_to_list(self->target);

    }

}

void key_update(Entity *self)
{
    if(!self)return;
    int keyOffsetMultiplier;
    if(self->target)
    {
        keyOffsetMultiplier = gfc_list_get_item_index(self->target->keys,self);
        
        keyOffsetMultiplier += 1;
        self->position = self->target->position;
        self->position.z += (KEY_OFFSET * keyOffsetMultiplier);

    }
}

void keys_draw()
{
    Entity *activeC = get_active_character();
    int numKeys;
    Vector2D pos = vector2d(10,10);
    int posOffset = 100;

    numKeys = activeC->keyCount;
    int i;
    for (i = 0; i < numKeys; i++)
    {
        pos.y += posOffset * i;
        gf3d_sprite_draw(gfc_list_get_nth(activeC->keys2d,i),pos,vector2d(2,2),1);
    }
}
