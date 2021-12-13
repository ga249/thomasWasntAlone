#include <SDL.h>            

#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "gf3d_sprite.h"

#include "entity.h"
#include "agumon.h"
#include "player.h"
#include "world.h"
#include "collisions.h"
#include "keys.h"
#include "sounds.h"
#include "level.h"
#include "menus.h"

int main(int argc,char *argv[])
{
    int a;
    Uint8 validate = 0;
    const Uint8 * keys;
    Sprite *mouse = NULL;
    int mousex,mousey;
    float mouseFrame = 0;
    World *w;
    Level *lvl;
    Vector3D keypos = {20,-20,0};
    Vector3D keypos2 = {-20,-30,0};
    
    for (a = 1; a < argc;a++)
    {
        if (strcmp(argv[a],"-disable_validate") == 0)
        {
            validate = 0;
        }
    }
    
    init_logger("gf3d.log");    
    slog("gf3d begin");
    gf3d_vgraphics_init(
        "gf3d",                 //program name
        1200,                   //screen width
        700,                    //screen height
        vector4d(0.51,0.75,1,1),//background color
        0,                      //fullscreen
        validate                //validation
    );
	slog_sync();
    
    entity_system_init(1024);
    menu_manager_init(10);
    sounds_init();              //sounds

    mouse = gf3d_sprite_load("images/pointer.png",32,32, 16);

    w = world_load("config/testworld.json");
    lvl = level_new();

    new_key(keypos,"key");
    new_key(keypos2,"key");
    createMenus();

    slog_sync();
    gf3d_camera_set_scale(vector3d(1,1,1));

    // main game loop
    gf3d_camera_set_scale(vector3d(1,1,1));
    
    slog("gf3d main loop begin");
    while(!lvl->done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        SDL_GetMouseState(&mousex,&mousey);

        mouseFrame += 0.01;
        if (mouseFrame >= 16)mouseFrame = 0;
        
        switch (lvl->screen)
        {
        case IN_GAME:
            if (lvl->paused == 0)
            {
                world_run_updates(w);
                entity_think_all();
                active_character_think();
                entity_update_all();
                active_character_update();
            }else{
                menu_update_group(IN_GAME);
            }
            break;
        
        case MAIN_MENU:
            menu_update_group(MAIN_MENU);
            break;
        }
        level_update(lvl);


        
        gf3d_camera_update_view();
        gf3d_camera_get_view_mat4(gf3d_vgraphics_get_view_matrix());

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        gf3d_vgraphics_render_start();

                //3D draws
                switch (lvl->screen)
                {
                case IN_GAME:
                    if (lvl->paused == 0)
                    {
                        world_draw(w);
                        entity_draw_all();
                    }
                    break;
                
                default:
                    break;
                }
                    

                //2D draws
                switch (lvl->screen)
                {
                case MAIN_MENU:
                    menu_draw_group(MAIN_MENU);
                    gf3d_sprite_draw(mouse,vector2d(mousex,mousey),vector2d(4,4),(Uint32)mouseFrame);
                    break;
                
                case IN_GAME:
                    if (lvl->paused == 0)
                    {
                        keys_draw(get_active_character());
                    }else{
                        menu_draw_group(IN_GAME);
                        gf3d_sprite_draw(mouse,vector2d(mousex,mousey),vector2d(4,4),(Uint32)mouseFrame);
                    }
                    break;
                }
                    
            
        gf3d_vgraphics_render_end();

        if (keys[SDL_SCANCODE_ESCAPE])lvl->done = 1; // exit condition
    }    
    
    world_delete(w);
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}

/*eol@eof*/
