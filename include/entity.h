#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "gfc_types.h"
//#include ""

#include "gf3d_model.h"

typedef struct  Entity_S
{
    Uint8           _inuse;     /**<keeps track of memory usage*/
    Model           *model;     /**<pointer to the entity model to draw (optional)*/
    Matrix4         *modelMat;   /**<model matrix for entity*/
    void            (*think)(struct Entity_S *self);        /**<pointer to the think function*/
    Uint32          health;     /**<entity dies when it reaches zero*/
}Entity;


/**
 * @brief   initialize entity system
 * @param   maxEntities max number of entities
 */
void entity_system_init(Uint32 maxEnts);

/**
 * @brief   create an entity
 * @return  a pointer to an entity
 */
Entity *entity_new();

/**
 * @brief   free an entity
 * @param self  a pointer to an entity
 */
void entity_free(Entity *self);

/**
 * @brief   draw an entity
 * @param self  a pointer to an entity
 */
void entity_draw(Entity *self, Uint32 bufferFrame, VkCommandBuffer commandBuffer);

void entity_draw_all(Uint32 bufferFrame, VkCommandBuffer commandBuffer);

void entity_think(Entity *self);


#endif