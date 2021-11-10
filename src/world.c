#include "simple_logger.h"
#include "simple_json.h"
#include "gfc_types.h"

#include "world.h"
#include "player.h"
#include "characters.h"
#include "door.h"
#include "button.h"
#include "pressure_plate.h"
#include "jump_pad.h"

static World *current_level = NULL;

World *get_current_level()
{
    return current_level;
}

Entity *get_active_character()
{
    return current_level->activeCharacter;
}

void active_character_think()
{
    get_active_character()->think(get_active_character());
    return;
}

void active_character_update()
{
    get_active_character()->update(get_active_character());
    return;
}

World *world_load(char *filename)
{
    SJson *json,*wjson,*eListjson,*entjson;
    World *w = NULL;
    const char *modelName = NULL;
    int isActive, doesSpawn;
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
    sj_get_integer_value(sj_object_get_value(entjson, "doesSpawn"), &doesSpawn);
    if (doesSpawn)
    {
        sj_get_float_value(sj_object_get_value(entjson, "xpos"), &xpos);
        sj_get_float_value(sj_object_get_value(entjson, "ypos"), &ypos);
        sj_get_float_value(sj_object_get_value(entjson, "zpos"), &zpos);
        sj_get_integer_value(sj_object_get_value(entjson, "isActive"), &isActive);
        pos.x = xpos;
        pos.y = ypos;
        pos.z = zpos;
        //if (isActive == 1)
        //{
            w->activeCharacter = character_ball_spawn(pos);
        //}else{
        //    character_ball_spawn(pos);
        //}
    }
    

    entjson = sj_object_get_value(eListjson, "charBox");
    sj_get_integer_value(sj_object_get_value(entjson, "doesSpawn"), &doesSpawn);
    if (doesSpawn)
    {
        sj_get_float_value(sj_object_get_value(entjson, "xpos"), &xpos);
        sj_get_float_value(sj_object_get_value(entjson, "ypos"), &ypos);
        sj_get_float_value(sj_object_get_value(entjson, "zpos"), &zpos);
        sj_get_integer_value(sj_object_get_value(entjson, "isActive"), &isActive);
        pos.x = xpos;
        pos.y = ypos;
        pos.z = zpos;
        //if (isActive == 1)
        //{
        //    w->activeCharacter = character_box_spawn(pos);
        //}else{
            character_box_spawn(pos);
        //}
    }

    entjson = sj_object_get_value(eListjson, "charTallBoi");
    sj_get_integer_value(sj_object_get_value(entjson, "doesSpawn"), &doesSpawn);
    if (doesSpawn)
    {
        sj_get_float_value(sj_object_get_value(entjson, "xpos"), &xpos);
        sj_get_float_value(sj_object_get_value(entjson, "ypos"), &ypos);
        sj_get_float_value(sj_object_get_value(entjson, "zpos"), &zpos);
        sj_get_integer_value(sj_object_get_value(entjson, "isActive"), &isActive);
        pos.x = xpos;
        pos.y = ypos;
        pos.z = zpos;
        //if (isActive == 1)
        //{
        //    w->activeCharacter = character_tallBoi_spawn(pos);
        //}else{
            character_tallBoi_spawn(pos);
        //}
    }

    entjson = sj_object_get_value(eListjson, "charSmallBoi");
    sj_get_integer_value(sj_object_get_value(entjson, "doesSpawn"), &doesSpawn);
    if (doesSpawn)
    {
        sj_get_float_value(sj_object_get_value(entjson, "xpos"), &xpos);
        sj_get_float_value(sj_object_get_value(entjson, "ypos"), &ypos);
        sj_get_float_value(sj_object_get_value(entjson, "zpos"), &zpos);
        sj_get_integer_value(sj_object_get_value(entjson, "isActive"), &isActive);
        pos.x = xpos;
        pos.y = ypos;
        pos.z = zpos;
        //if (isActive == 1)
        //{
        //    w->activeCharacter = character_smallBoi_spawn(pos);
        //}else{
            character_smallBoi_spawn(pos);
        //}
    }

    entjson = sj_object_get_value(eListjson, "charFatBoi");
    sj_get_integer_value(sj_object_get_value(entjson, "doesSpawn"), &doesSpawn);
    if (doesSpawn)
    {
        sj_get_float_value(sj_object_get_value(entjson, "xpos"), &xpos);
        sj_get_float_value(sj_object_get_value(entjson, "ypos"), &ypos);
        sj_get_float_value(sj_object_get_value(entjson, "zpos"), &zpos);
        sj_get_integer_value(sj_object_get_value(entjson, "isActive"), &isActive);
        pos.x = xpos;
        pos.y = ypos;
        pos.z = zpos;
        //if (isActive == 1)
        //{
        //    w->activeCharacter = character_fatBoi_spawn(pos);
        //}else{
            character_fatBoi_spawn(pos);
        //}
    }
    pos.x = 25;
    pos.y = -15;
    pos.z = 0;
    door_new(pos);

    pos.x = 25;
    pos.y = -30;
    pos.z = 2;
    button_new(pos);

    pos.x = 0;
    pos.y = 30;
    pos.z = -1;
    pplate_new(pos);

    pos.x = 10;
    pos.y = 30;
    pos.z = -1;
    jpad_new(pos);

    sj_free(eListjson);
    sj_free(entjson);
    sj_free(json);
    current_level = w;
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
        current_level->activeCharacter = entity_get_character_by_id(1);
    }
    if (keys[SDL_SCANCODE_2])
    {
        current_level->activeCharacter = entity_get_character_by_id(2);
    }
    if (keys[SDL_SCANCODE_3])
    {
        current_level->activeCharacter = entity_get_character_by_id(3);
    }
    if (keys[SDL_SCANCODE_4])
    {
        current_level->activeCharacter = entity_get_character_by_id(4);
    }
    if (keys[SDL_SCANCODE_5])
    {
        current_level->activeCharacter = entity_get_character_by_id(5);
    }

}

void world_add_entity(World *world,Entity *entity);


/*eol@eof*/
