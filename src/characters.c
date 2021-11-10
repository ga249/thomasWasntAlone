#include "simple_logger.h"
#include "gfc_types.h"
#include "characters.h"

#include "player.h"

#define CHAR_1  1
#define CHAR_2  2
#define CHAR_3  3
#define CHAR_4  4
#define CHAR_5  5

void character_load_common(Entity *self, Vector3D position)
{
    self->think = player_think;
    self->update = player_update;
    vector3d_copy(self->position,position);
    self->rotation.x = -M_PI;
    self->entType = ENT_PLAYER;
    self->hasGravity = 1;
    return;
}

Entity *character_ball_spawn(Vector3D position)
{
    Entity *self = NULL;
    
    self = entity_new();
    if (!self)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    
    self->model = gf3d_model_load("sphere");
    self->charName = "ball";
    self->char_ID = CHAR_1;
    character_load_common(self, position);
    self->hbType = HB_SPHERE;
    self->hbRadius = 2;
    return self;
}

Entity *character_box_spawn(Vector3D position)
{
    Entity *self = NULL;
    
    self = entity_new();
    if (!self)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }

    Vector3D min,max;
    
    self->model = gf3d_model_load("box");
    self->charName = "box";
    self->char_ID = CHAR_2;
    character_load_common(self, position);
    self->hbType = HB_RECT;
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
    return self;
}

Entity *character_tallBoi_spawn(Vector3D position)
{
    Entity *self = NULL;
    
    self = entity_new();
    if (!self)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }

    Vector3D min,max;
    
    self->model = gf3d_model_load("tallBoi");
    self->charName = "tallBoi";
    self->char_ID = CHAR_3;
    character_load_common(self, position);
    self->hbType = HB_RECT;
    max = self->position;
    max.x += 1;
    max.y += 1;             //TODO: fix offset for tallBoi hitbox
    max.z += 1;
    self->hbMax = max;
    min = self->position;
    min.x -= 1;
    min.y -= 1;             //TODO: fix offset for tallBoi hitbox
    min.z -= 1;
    self->hbMin = min;
    return self;
}

Entity *character_smallBoi_spawn(Vector3D position)
{
    Entity *self = NULL;
    
    self = entity_new();
    if (!self)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }

    Vector3D min,max;
    
    self->model = gf3d_model_load("tallBoi");
    self->charName = "smallBoi";
    self->char_ID = CHAR_4;
    character_load_common(self, position);
    self->hbType = HB_RECT;
    max = self->position;
    max.x += 1;
    max.y += 1;             //TODO: fix offset for smallBoi hitbox
    max.z += 1;
    self->hbMax = max;
    min = self->position;
    min.x -= 1;
    min.y -= 1;             //TODO: fix offset for smallBoi hitbox
    min.z -= 1;
    self->hbMin = min;
    return self;
}

Entity *character_fatBoi_spawn(Vector3D position)
{
    Entity *self = NULL;
    
    self = entity_new();
    if (!self)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }

    Vector3D min,max;
    
    self->model = gf3d_model_load("tallBoi");
    self->charName = "fatBoi";
    self->char_ID = CHAR_5;
    character_load_common(self, position);
    self->hbType = HB_RECT;
    max = self->position;
    max.x += 1;
    max.y += 1;             //TODO: fix offset for fatBoi hitbox
    max.z += 1;
    self->hbMax = max;
    min = self->position;
    min.x -= 1;
    min.y -= 1;             //TODO: fix offset for fatBoi hitbox
    min.z -= 1;
    self->hbMin = min;
    return self;
}

Entity *character_spawn_by_name(char *name, Vector3D position)
{
    if(!name)
    {
        slog("no character name provided");
        return NULL;
    }

    if (strcmp(name, "ball"))
    {
        return character_ball_spawn(position);
    }
    if (strcmp(name, "box"))
    {
        return character_box_spawn(position);
    }
    if (strcmp(name, "tallBoi"))
    {
        return character_tallBoi_spawn(position);
    }
    if (strcmp(name, "smallBoi"))
    {
        return character_smallBoi_spawn(position);
    }
    if (strcmp(name, "fatBoi"))
    {
        return character_fatBoi_spawn(position);
    }

    slog("character name doesn't match any characters");
    return NULL;
}
