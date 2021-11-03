#ifndef     __PLAYER_H_
#define     __PLAYER_H_

#include    "entity.h"

/**
 * @brief   create player
 */
Entity *player_new(Vector3D position,char *modelName,char *charName, int isActive);

void    player_think(Entity *self);

#endif