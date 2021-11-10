#include "simple_logger.h"
#include "collisions.h"
#include "world.h"
#include "pressure_plate.h"
#include "player.h"
#include "keys.h"

Entity *pplate_new(Vector3D position)
{
    Entity *pplate;
    
    pplate = entity_new();
    if (!pplate)
    {
        slog("Ent for pplate not created");
        return NULL;
    }

    pplate->model = gf3d_model_load("pplate");
    pplate->think = pplate_think;
    pplate->update = pplate_update;
    vector3d_copy(pplate->position,position);
    pplate->rotation.x = -M_PI;
    pplate->entType = ENT_PLATE;
    pplate->charName = "pplate";
    pplate->hasGravity = 0;
    pplate->unlocked = 0;
    pplate->hbType = HB_SPHERE;
    pplate->hbRadius = 3;
    return pplate;
}

void pplate_think(Entity *self)
{
    if(!self)return;

    if(collision_ent_ent(self, get_active_character()))
    {
        gf3d_model_change_texture(self->model,"pplatePressed");
    }else{
        gf3d_model_change_texture(self->model,"pplate");
    }
}

void pplate_update(Entity *self)
{

}