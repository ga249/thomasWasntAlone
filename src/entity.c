#include <stdlib.h>
#include <simple_logger.h>

#include "entity.h"

typedef struct 
{
    Uint32  maxEnts;         /**<Maximum number of entities*/
    Entity  *entityList;     /**<List of entities*/
}EntityManager;

static EntityManager entity_manager = {0};

void entity_manager_close()
{
    int i;
    for (i = 0; i < entity_manager.maxEnts; i++)
    {
        if (entity_manager.entityList[i]._inuse)
        {
            entity_free(&entity_manager.entityList[i]);
        }
    }
    entity_manager.maxEnts = 0;
    free(entity_manager.entityList);
    entity_manager.entityList = NULL;
    slog("entity manager closed");
}

void entity_system_init(Uint32 maxEnts)
{
    if (entity_manager.entityList != NULL)
    {
        //TODO: cleanup
    }
    if (!maxEnts)
    {
        slog("cannot initialize a zero size entity list!");
        return;
    }
    entity_manager.entityList = malloc(sizeof(Entity) * maxEnts);
    if (entity_manager.entityList == NULL)
    {
        slog("failed to allocate %i entities for the entity manager", maxEnts);
        return;
    }
    entity_manager.maxEnts = maxEnts;
    memset(entity_manager.entityList,0,sizeof(Entity)*maxEnts);
    slog("entity manager initialized");
    atexit(entity_manager_close);

}

Entity *entity_new()
{
    int i;
    if (entity_manager.entityList == NULL)
    {
        slog("entity system does not exist");
        return NULL;
    }
    for (i = 0; i < entity_manager.maxEnts; i++)
    {
        if (entity_manager.entityList[i]._inuse)continue; //entity in use
        memset(&entity_manager.entityList[i],0,sizeof(Entity));
        entity_manager.entityList[i]._inuse = 1;
        return &entity_manager.entityList[i];
    }
    slog("out of open entity slots in memory!");
    return NULL;
}

void entity_free(Entity *self)
{
    if (!self)return;
    //destroy
    gf3d_model_free(self->model);
    memset(self,0,sizeof(Entity));
}

void entity_draw(Entity *self, Uint32 bufferFrame, VkCommandBuffer commandBuffer)
{
    if (!self)return;
    gf3d_model_draw(self->model,bufferFrame,commandBuffer, self->modelMat);
}

void entity_draw_all(Uint32 bufferFrame, VkCommandBuffer commandBuffer)
{
    int i;
    for (i = 0; i < entity_manager.maxEnts; i++)
    {
        if (!entity_manager.entityList[i]._inuse)continue; //entity not in use
        entity_draw(&entity_manager.entityList[i],bufferFrame, commandBuffer);
    }
}