#include "simple_logger.h"
#include "collisions.h"
#include "world.h"
#include "telepad.h"
#include "player.h"
#include "keys.h"

float teleBuffer = 0;

Entity *telepad_new(Vector3D position)
{
    Entity *telepad;
    
    telepad = entity_new();
    if (!telepad)
    {
        slog("Ent for telepad not created");
        return NULL;
    }
    Vector3D min,max;

    telepad->model = gf3d_model_load("jpad");
    gf3d_model_change_texture(telepad->model, "telepad");
    telepad->think = telepad_think;
    telepad->update = telepad_update;
    vector3d_copy(telepad->position,position);
    telepad->rotation.x = -M_PI;
    telepad->entType = ENT_PAD;
    telepad->charName = "telepad";
    telepad->hasGravity = 0;
    telepad->hbType = HB_RECT;
    max = telepad->position;
    max.x += 1.5;
    max.y += 1.5;
    max.z += .5;
    telepad->hbMax = max;
    min = telepad->position;
    min.x -= 1.5;
    min.y -= 1.5;
    min.z -= .5;
    telepad->hbMin = min;
    return telepad;
}

Entity *telepad_make_pair(Entity *telepad, Vector3D position)
{
    if(!telepad)
    {
        slog("Telepad pair not provided");
        return NULL;
    }
    Entity *tpad = telepad_new(position);
    tpad->target = telepad;
    telepad->target = tpad;

    return tpad;
}

void telepad_think(Entity *self)
{
    if(!self)return;
    if(!self->target)return;  //telepad has no pair

    if(collision_ent_ent(self, get_active_character()))
    {
        if (SDL_GetTicks() - teleBuffer >= 400)
        {
            teleBuffer = SDL_GetTicks();

            get_active_character()->position = self->target->position;
            
        }
    }
}

void telepad_update(Entity *self)
{

}
