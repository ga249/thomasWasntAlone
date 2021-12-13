#include "level.h"

Vector4D v4d_red   = {255, 100, 100, 255};
Vector4D v4d_green = {100, 255, 100, 255};
Vector4D v4d_blue  = {100, 100, 255, 255};

static Level *current_level = NULL;
const Uint8 *keys;
float pauseBuffer;

Level *level_get_active()
{
    return current_level;
}

Level *level_new()
{
    Level *level;
    level = (Level*)gfc_allocate_array(sizeof(Level), 1); //allocate array
    if(!level)return NULL;
    level->screen = 0;
    current_level = level;
    return level;
}

void level_draw(Level *level)
{
    if (!level)return;
    
}

void level_update(Level *lvl)
{
    if(!lvl)return;
    keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_P])
    {
        if (SDL_GetTicks() - pauseBuffer >= 200)
        {
            pauseBuffer = SDL_GetTicks();

            if(lvl->paused)
            {
                lvl->paused = 0;
            }else{
                lvl->paused = 1;
            }
        }
    }

    //--------------------------------------------------------debugging-------------------------------------------

    if (keys[SDL_SCANCODE_M])
    {
        if (SDL_GetTicks() - pauseBuffer >= 200)
        {
            pauseBuffer = SDL_GetTicks();

            if (lvl->screen == MAIN_MENU)
            {
                lvl->screen = IN_GAME;
            }else if (lvl->screen == IN_GAME)
            {
                lvl->screen = MAIN_MENU;
            }
        }
    }
    //--------------------------------------------------------------------------------------------------------------------------
}