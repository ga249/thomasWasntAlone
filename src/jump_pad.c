#include "simple_logger.h"
#include "collisions.h"
#include "world.h"
#include "jump_pad.h"
#include "player.h"
#include "keys.h"

Entity *jpad_new(Vector3D position)
{
    Entity *jpad;
    
    jpad = entity_new();
    if (!jpad)
    {
        slog("Ent for jpad not created");
        return NULL;
    }
    Vector3D min,max;

    jpad->model = gf3d_model_load("jpad");
    jpad->think = jpad_think;
    jpad->update = jpad_update;
    vector3d_copy(jpad->position,position);
    jpad->rotation.x = -M_PI;
    jpad->entType = ENT_PAD;
    jpad->charName = "jpad";
    jpad->hasGravity = 0;
    jpad->hbType = HB_RECT;
    max = jpad->position;
    max.x += 1.5;
    max.y += 1.5;
    max.z += .5;
    jpad->hbMax = max;
    min = jpad->position;
    min.x -= 1.5;
    min.y -= 1.5;
    min.z -= .5;
    jpad->hbMin = min;
    return jpad;
}

void jpad_think(Entity *self)
{
    if(!self)return;

    if(collision_ent_ent(self, get_active_character()))
    {
        get_active_character()->velocity.z = .5;
    }
}

void jpad_update(Entity *self)
{

}