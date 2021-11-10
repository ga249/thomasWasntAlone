#include "simple_logger.h"
#include "button.h"
#include "collisions.h"
#include "world.h"
#include "player.h"

Entity *button_new(Vector3D position)
{
    Entity *button;
    
    button = entity_new();
    if (!button)
    {
        slog("Ent for button not created");
        return NULL;
    }

    button->model = gf3d_model_load("button");
    button->think = button_think;
    button->update = button_update;
    vector3d_copy(button->position,position);
    button->rotation.x = -M_PI;
    button->entType = ENT_BUTTON;
    button->charName = "button";
    button->hasGravity = 0;
    button->unlocked = 0;
    button->hbType = HB_SPHERE;
    button->hbRadius = 3;
    return button;
}

void button_think(Entity *self)
{
    if(!self)return;
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    if(collision_ent_ent(self, get_active_character()))
    {
        if(keys[SDL_SCANCODE_E])
        {
            gf3d_model_change_texture(self->model,"buttonPressed");
        }else{
            gf3d_model_change_texture(self->model,"button");
        }
    }
}

void button_update(Entity *self)
{
    
}