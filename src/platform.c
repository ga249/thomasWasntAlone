#include "simple_logger.h"
#include "platform.h"
#include "collisions.h"
#include "world.h"

void platform_think(Entity *self);
void platform_update(Entity *self);

float thinkBuffer;
float doBuffer;
int backNForth = 1;

Entity *platform_new(Vector3D position, Vector3D lwh)
{
    Entity *platform;
    
    platform = entity_new();
    if (!platform)
    {
        slog("Ent for platform not created");
        return NULL;
    }
    Vector3D min,max;

    platform->model = gf3d_model_load("platform");
    platform->think = platform_think;
    platform->update = platform_update;
    vector3d_copy(platform->position,position);
    platform->entType = ENT_PLAT;
    platform->charName = "platform";
    platform->hasGravity = 0;
    platform->hbType = HB_RECT;
    max = platform->position;
    max.x += lwh.x/2;
    max.y += lwh.y/2;
    max.z += lwh.z/2;
    platform->hbMax = max;
    min = platform->position;
    min.x -= lwh.x/2;
    min.y -= lwh.y/2;
    min.z -= lwh.z/2;
    platform->hbMin = min;
    return platform;
}

void platform_think(Entity *self)
{
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    //---------------------------------------------------------------------------Think pause and hold cycle----------------
    //ranThinkBuffer = gfc_random()
    if (SDL_GetTicks() - thinkBuffer >= 2000)
    {
        if (SDL_GetTicks() - doBuffer >= 1000)
        {
            thinkBuffer = SDL_GetTicks();
            //slog("%i", choice);
        //--------------------------------------decision making logic-------------------------------
            if (backNForth == 0)
            {
                backNForth = 1;
            }else if (backNForth == 1){
                backNForth = 0;
            }
            //---------------------------------decision making logic-------------------------------
        }
//---------------------------------------------------------------------------Think pause and hold cycle----------------
        
    if(backNForth == 0)
    self->position.z += .05;
    else if (backNForth == 1){
        self->position.z -= .05;
    }

//---------------------------------Think pause and hold cycle----------------
    }else{doBuffer = SDL_GetTicks();}
//---------------------------------Think pause and hold cycle----------------

    if (collision_ent_ent(self,get_active_character()) && !keys[SDL_SCANCODE_SPACE])
    {
        get_active_character()->position = self->position;
        get_active_character()->position.z +=1;
        get_active_character()->hasGravity = 0;
        get_active_character()->onPForm = 1;
    }else{
        get_active_character()->hasGravity = 1;
        get_active_character()->onPForm = 0;
    }

}

void platform_update(Entity *self)
{
    Vector3D max, min;
    max = self->position;
    max.x += self->lwh.x/2;
    max.y += self->lwh.y/2;
    max.z += self->lwh.z/2;
    self->hbMax = max;
    min = self->position;
    min.x -= self->lwh.x/2;
    min.y -= self->lwh.y/2;
    min.z -= self->lwh.z/2;
    self->hbMin = min;
}