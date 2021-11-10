#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "player.h"
#include "world.h"


void player_think(Entity *self);
void player_update(Entity *self);

Vector3D vector3d_negative(Vector3D v)
{
    v.x *= -1;
    v.y *= -1;
    v.z *= -1;
    return v;
}

Entity *player_new(Vector3D position,char *modelName,char *charName, int isActive)
{
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    if (!modelName)
    {
        slog("No modelname provided for player");
        return NULL;
    }
    ent->model = gf3d_model_load(modelName);
    ent->think = player_think;
    ent->update = player_update;
    vector3d_copy(ent->position,position);
    ent->rotation.x = -M_PI;
    ent->entType = ENT_PLAYER;
    ent->charName = charName;
    ent->hasGravity = 1;
    ent->hbType = HB_SPHERE;
    ent->hbRadius = 2;
    return ent;
}


void player_think(Entity *self)
{
    //if (!strcmp(self->charName,get_active_character()->charName))return;
    Vector3D forward;
    Vector3D right;
    Vector3D up;
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    vector3d_angle_vectors(self->rotation, &right, &forward, &up);
    
    vector3d_set_magnitude(&forward,0.1);
    vector3d_set_magnitude(&right,0.1);
    vector3d_set_magnitude(&up,0.1);
    forward.z = 0;
    self->fwd = forward;
    //slog("fwd.xyz: %f, %f, %f",forward.x,forward.y,forward.z);
    //slog("right.xyz: %f, %f, %f",right.x,right.y,right.z);
    //slog("up.xyz: %f, %f, %f",up.x,up.y,up.z);
    //slog("rot.x: %f, rot.y: %f, rot.z: %f", self->rotation.x,self->rotation.y,self->rotation.z);

    
    //slog("z: %f", self->position.z);
    if (keys[SDL_SCANCODE_W])
    {   
        vector3d_add(self->position,self->position,forward);
        //self->velocity = forward;
    }
    if (keys[SDL_SCANCODE_S])
    {
        vector3d_add(self->position,self->position,-forward);
        //self->velocity = vector3d_negative(forward);      
    }
    if (keys[SDL_SCANCODE_D])
    {
        vector3d_add(self->position,self->position,right);
    }
    if (keys[SDL_SCANCODE_A])    
    {
        vector3d_add(self->position,self->position,-right);
    }
    if (keys[SDL_SCANCODE_SPACE])self->velocity.z = .25;
    if (keys[SDL_SCANCODE_Z])self->position.z -= 0.10;
    
    if (keys[SDL_SCANCODE_DOWN])self->rotation.x -= 0.0010;
    if (keys[SDL_SCANCODE_UP])self->rotation.x += 0.0010;
    if (keys[SDL_SCANCODE_RIGHT])self->rotation.z -= 0.0010;
    if (keys[SDL_SCANCODE_LEFT])self->rotation.z += 0.0010;

}

void player_update(Entity *self)
{
    if (!self)return;
    //if (!strcmp(self->charName,get_active_character()->charName))return;
    Vector3D camPos = self->position;
    Vector3D fwd = self->fwd;
    vector3d_set_magnitude(&fwd, 6);
    vector3d_add(camPos,camPos,vector3d_negative(fwd));
    camPos.z += 2;

    gf3d_camera_set_position(camPos);
    gf3d_camera_set_rotation(self->rotation);
}

/*eol@eof*/