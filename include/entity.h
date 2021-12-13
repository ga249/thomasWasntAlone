#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_types.h"
#include "gfc_list.h"

#include "gf3d_model.h"

#define ENT_PLAYER 0
#define ENT_KEY    1
#define HB_SPHERE  2
#define HB_RECT    3
#define ENT_DOOR   5
#define ENT_BUTTON 6
#define ENT_PLATE  7
#define ENT_PAD    8
#define ENT_PLAT   9    


typedef struct Entity_S
{
    Uint8       _inuse;     /**<keeps track of memory usage*/
    Matrix4     modelMat;   /**<orientation matrix for the model*/
    Model      *model;      /**<pointer to the entity model to draw  (optional)*/
    void       (*think)(struct Entity_S *self); /**<pointer to the think function*/
    void       (*update)(struct Entity_S *self); /**<pointer to the update function*/
    void       (*collide)(struct Entity_S *self); /**<pointer to an optional collide funciton*/
    
    Vector3D    position;  
    Vector3D    velocity;
    Vector3D    acceleration;
    
    int         hbType;
    float       hbRadius;
    Vector3D    hbMin,hbMax;
    Vector3D    lwh;
    
    Vector3D    scale;
    Vector3D    rotation;
    Vector3D    fwd;        /**<forward direction vector of ent*/
    
    int         entType;

    int         hasGravity;
    int         onPForm;
    
    int         char_ID;
    char       *charName;
    struct Entity_S *target;

    List       *keys;
    int         keyCount;
    List       *keys2d;

    int         unlocked;
    void       *customData;   /**<IF an entity needs to keep track of extra data, we can do it here*/
}Entity;

/**
 * @brief initializes the entity subsystem
 * @param maxEntities the limit on number of entities that can exist at the same time
 */
void entity_system_init(Uint32 maxEntities);

/**
 * @brief provide a pointer to a new empty entity
 * @return NULL on error or a valid entity pointer otherwise
 */
Entity *entity_new();

/**
 * @brief free a previously created entity from memory
 * @param self the entity in question
 */
void entity_free(Entity *self);


/**
 * @brief Draw an entity in the current frame
 * @param self the entity in question
 */
void entity_draw(Entity *self);

/**
 * @brief draw ALL active entities
 */
void entity_draw_all();

/**
 * @brief Call an entity's think function if it exists
 * @param self the entity in question
 */
void entity_think(Entity *self);

/**
 * @brief run the think functions for ALL active entities
 */
void entity_think_all();

/**
 * @brief run the update functions for ALL active entities
 */
void entity_update_all();

Entity *entity_get_character_by_id(int id);

Entity *entity_get_player_by_name(char *charName);

int ent_is_grounded(Entity *ent);

char *ent_get_name(Entity *ent);

#endif
