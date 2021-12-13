#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "simple_json.h"
#include "simple_logger.h"
#include "collisions.h"
#include "gf3d_sprite.h"



#define MAIN_MENU              0
#define IN_GAME                1


Vector4D v4d_red;
Vector4D v4d_green;
Vector4D v4d_blue;
Vector4D v4d_yellow;

Sprite *background;

typedef struct
{
    Sprite     *background;     /**<Background sprite>*/
    int         paused;
    int         screen;
    int         done;
}Level;

/**
 * @brief Creates level with bg and bounds
 * @return Object type of Level
 * */
Level *level_new();

/**
 * @brief Frees level and its sprite
 * */
void level_free(Level *level);

/**
 * @brief Draw level bg image and bounds
 * */
void level_draw(Level *level);


/**
 * @brief Get current level object
 * @return Static type Level
 * */
Level *level_get_active();

/**
 * @brief Update things in level, pause etc.
 * */
void level_update(Level *lvl);


#endif