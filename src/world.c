#include "simple_logger.h"
#include "simple_json.h"
#include "gfc_types.h"

#include "world.h"
#include "player.h"


World *world_load(char *filename)
{
    SJson *json,*wjson,*eListjson,*entjson;
    World *w = NULL;
    const char *modelName = NULL;
    int isActive;
    float xpos, ypos, zpos;
    Vector3D pos;

    w = gfc_allocate_array(sizeof(World),1);
    if (w == NULL)
    {
        slog("failed to allocate data for the world");
        return NULL;
    }
    json = sj_load(filename);
    if (!json)
    {
        slog("failed to load json file (%s) for the world data",filename);
        free(w);
        return NULL;
    }
    wjson = sj_object_get_value(json,"world");
    if (!wjson)
    {
        slog("failed to find world object in %s world condig",filename);
        free(w);
        sj_free(json);
        return NULL;
    }
    modelName = sj_get_string_value(sj_object_get_value(wjson,"model"));
    if (modelName)
    {
        w->worldModel = gf3d_model_load((char *)modelName);
        gfc_matrix_identity(w->modelMat);
        gfc_matrix_scale(
            w->modelMat,
            vector3d(10,10,10)
        );
        gfc_matrix_translate(
            w->modelMat,
            vector3d(0,0,-10)
        );
        gfc_matrix_rotate(w->modelMat, w->modelMat, GFC_HALF_PI,vector3d(1,0,0));
    }else{
        slog("world data (%s) has no model",filename);
    }

    eListjson = sj_object_get_value(wjson, "entityList");

    entjson = sj_object_get_value(eListjson, "charBall");
    modelName = sj_get_string_value(sj_object_get_value(entjson,"modelName"));
    if (modelName)
    {
        slog("name: %s", modelName);
    }
    sj_get_float_value(sj_object_get_value(entjson, "xpos"), &xpos);
    sj_get_float_value(sj_object_get_value(entjson, "ypos"), &ypos);
    sj_get_float_value(sj_object_get_value(entjson, "zpos"), &zpos);
    sj_get_integer_value(sj_object_get_value(entjson, "isActive"), &isActive);
    pos.x = xpos;
    pos.y = ypos;
    pos.z = zpos;
    player_new(pos,(char *)modelName,"ball", isActive);

    entjson = sj_object_get_value(eListjson, "charDino");
    modelName = sj_get_string_value(sj_object_get_value(entjson,"modelName"));
    if (modelName)
    {
        slog("name: %s", modelName);
    }
    sj_get_float_value(sj_object_get_value(entjson, "xpos"), &xpos);
    sj_get_float_value(sj_object_get_value(entjson, "ypos"), &ypos);
    sj_get_float_value(sj_object_get_value(entjson, "zpos"), &zpos);
    sj_get_integer_value(sj_object_get_value(entjson, "isActive"), &isActive);
    pos.x = xpos;
    pos.y = ypos;
    pos.z = zpos;
    player_new(pos,(char *)modelName,"dino", isActive);

    sj_free(eListjson);
    sj_free(entjson);
    sj_free(json);
    return w;
}

void world_draw(World *world)
{
    if (!world)return;
    if (!world->worldModel)return;// no model to draw, do nothing
    gf3d_model_draw(world->worldModel,world->modelMat);
}

void world_delete(World *world)
{
    if (!world)return;
    gf3d_model_free(world->worldModel);
    free(world);
}

void world_run_updates(World *world)
{
    if (!world)return;
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    if (keys[SDL_SCANCODE_1])
    {
        if(!strcmp(entity_get_active_player()->charName,"ball"))
        {
            entity_get_active_player()->activePlayer = 0;
            entity_get_player_by_name("ball")->activePlayer = 1;
        }
    }
    if (keys[SDL_SCANCODE_2])
    {
        if(!strcmp(entity_get_active_player()->charName,"dino"))
        {
            entity_get_active_player()->activePlayer = 0;
            entity_get_player_by_name("dino")->activePlayer = 1;
        }
    }
}

void world_add_entity(World *world,Entity *entity);


/*eol@eof*/
