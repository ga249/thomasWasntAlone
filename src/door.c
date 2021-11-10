#include "simple_logger.h"
#include "collisions.h"
#include "world.h"
#include "door.h"
#include "player.h"
#include "keys.h"


void door_think(Entity *self);
void door_update(Entity *self);

Entity *door_new(Vector3D position)
{
    Entity *door;
    
    door = entity_new();
    if (!door)
    {
        slog("Ent for door not created");
        return NULL;
    }
    Vector3D min,max;

    door->model = gf3d_model_load("door");
    door->think = door_think;
    door->update = door_update;
    vector3d_copy(door->position,position);
    door->rotation.x = -M_PI;
    door->entType = ENT_DOOR;
    door->charName = "door";
    door->hasGravity = 0;
    door->unlocked = 0;
    door->hbType = HB_RECT;
    max = door->position;
    max.x += 1;
    max.y += 1;
    max.z += 2;
    door->hbMax = max;
    min = door->position;
    min.x -= 1;
    min.y -= .5;
    min.z -= .5;
    door->hbMin = min;
    return door;
}

void door_think(Entity *self)
{
    if(!self)return;
    if(self->unlocked)return;
    Entity *key;

    if(collision_ent_ent(self,get_active_character()))
    {
        if(get_active_character()->keyCount == 0)
        {
            vector3d_add(get_active_character()->position,get_active_character()->position,vector3d_negative(get_active_character()->fwd));
        }else{
            self->unlocked = 1;
            gf3d_model_change_texture(self->model,"doorGreen");
            key = gfc_list_get_nth(get_active_character()->keys,0);
            entity_free(key);
            get_active_character()->keyCount -= 1;
        }
    }

    
}

void door_update(Entity *self)
{
    
}