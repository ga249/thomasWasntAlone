#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "player.h"
#include "world.h"
#include "characters.h"


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
        vector3d_add(self->position,self->position,-forward);
        //self->velocity = forward;
    }
    if (keys[SDL_SCANCODE_S])
    {
        vector3d_add(self->position,self->position,forward);
        //self->velocity = vector3d_negative(forward);      
    }
    if (keys[SDL_SCANCODE_D])
    {
        vector3d_add(self->position,self->position,-right);
    }
    if (keys[SDL_SCANCODE_A])    
    {
        vector3d_add(self->position,self->position,right);
    }
    if (keys[SDL_SCANCODE_SPACE])
    {
        if (ent_is_grounded(self))
        self->velocity.z = .25;
    }
    //if (keys[SDL_SCANCODE_Z])self->position.z -= 0.10;
    
    if (keys[SDL_SCANCODE_DOWN])self->rotation.x -= 0.0030;
    if (keys[SDL_SCANCODE_UP])self->rotation.x += 0.0030;
    if (keys[SDL_SCANCODE_RIGHT])self->rotation.z -= 0.0030;
    if (keys[SDL_SCANCODE_LEFT])self->rotation.z += 0.0030;

    //slog("keyCount: %i", self->keyCount);

}

void player_update(Entity *self)
{
    if (!self)return;
    Vector3D camPos = self->position;
    Vector3D fwd = self->fwd;
    Vector3D min,max;
    vector3d_set_magnitude(&fwd, 7);
    vector3d_add(camPos,camPos,fwd);
    camPos.z += 3;

    //slog("posX: %f posY: %f",self->position.x, self->position.y);
    gf3d_camera_set_position(camPos);
    gf3d_camera_set_rotation(self->rotation);

    switch (self->char_ID)
    {
    case CHAR_2:
        max = self->position;
        max.x += 1;
        max.y += 1;
        max.z += 1;
        self->hbMax = max;
        min = self->position;
        min.x -= 1;
        min.y -= 1;
        min.z -= 1;
        self->hbMin = min;
        break;
    
    case CHAR_3:
        max = self->position;
        max.x += 1;
        max.y += 1;
        max.z += 3;
        self->hbMax = max;
        min = self->position;
        min.x -= 1;
        min.y -= 1;
        min.z -= 1;
        self->hbMin = min;
        break;

    case CHAR_4:
        max = self->position;
        max.x += .5;
        max.y += .5;
        max.z += .5;
        self->hbMax = max;
        min = self->position;
        min.x -= .5;
        min.y -= .5;
        min.z -= .5;
        self->hbMin = min;
        break;

    case CHAR_5:
        max = self->position;
        max.x += 2;
        max.y += 2;
        max.z += .5;
        self->hbMax = max;
        min = self->position;
        min.x -= 2;
        min.y -= 2;
        min.z -= .5;
        self->hbMin = min;
        break;
    default:
        break;
    }
}

/*eol@eof*/
