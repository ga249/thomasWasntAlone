#include "simple_logger.h"
#include "door.h"

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
    Vector3D min;

    door->model = gf3d_model_load("door");
    door->think = door_think;
    door->update = door_update;
    vector3d_copy(door->position,position);
    door->rotation.x = -M_PI;
    door->entType = ENT_DOOR;
    door->charName = "door";
    door->hasGravity = 1;
    door->hbType = HB_RECT;
    min = door->position;
    min.z -= 2;
    min.x -= 1;
    min.y -= .5;
    door->hbMin = min;
    door->hbMax = door->position;
    return door;
}

void door_think(Entity *self)
{

}

void door_update(Entity *self)
{
    
}