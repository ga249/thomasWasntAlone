#include <stdlib.h>
#include "simple_logger.h"
#include "menus.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "collisions.h"
#include "level.h"
#include "simple_json.h"
#include "entity.h"
#include "world.h"

#define B_START     0
#define B_QUIT      1
#define B_MAIN_M    2


typedef struct 
{
    Uint32      maxMenus;         /**<Maximum number of entities*/
    Menu        *menuList;     /**<List of entities*/
    TTF_Font    *text;           
}MenuManager;

static MenuManager menu_manager = {0};

Menu *menu_new(){
    int i;
    for (i=0; i < menu_manager.maxMenus; i++){
        if(menu_manager.menuList[i]._inuse)continue;
        menu_manager.menuList[i]._inuse = 1;
        // slog("Items in menu list %d", i);
        return &menu_manager.menuList[i];
    }
    slog("out of open menu slots in memory");
    return NULL;
}

void menu_manager_init(Uint32 maxMenus){
    if (menu_manager.menuList != NULL){
        //TODO: cleanup
    }
    if (!maxMenus){
        slog("cannot init 0 zise menu list");
        return;
    }
    menu_manager.menuList = (Menu * )malloc(sizeof(Menu) * maxMenus);
    if (menu_manager.menuList == NULL){
        slog("failed to allocate %i menus for the menu manager",maxMenus);
    }
    menu_manager.maxMenus = maxMenus;
    memset(menu_manager.menuList,0,sizeof(Menu)*maxMenus);
    slog("Menu manager initalized");
    atexit(menu_manager_close);
}

void menu_manager_close(){
    int i;
    for (i=0; i < menu_manager.maxMenus; i++){
        if(menu_manager.menuList[i]._inuse){
            menu_free(&menu_manager.menuList[i]);
        }
    }
    menu_manager.maxMenus = 0;
    free(menu_manager.menuList);
    menu_manager.menuList =NULL;
    slog("menu manager closed");
}

void menu_free(Menu *self){
    if (!self)return;
    if (!self->sprite)
    gf3d_sprite_free(self->sprite);
    memset(self,0,sizeof(Menu));
}

void menu_update(Menu *self){
    if (!self)return;
    if (self->think){
        self->think(self);
    }
}

void menu_update_group(int group){
    // level_get_active()->frame ++;
    int i;
    for (i = 0;i < menu_manager.maxMenus;i++)
    {
        if (!menu_manager.menuList[i]._inuse)continue;
        if (menu_manager.menuList[i].group == group)menu_update(&menu_manager.menuList[i]);
    }
}

void menu_draw(Menu *self){
    if (self == NULL){
        slog("cannot draw, null menu provided");
        return;
    }
    
    //gf2d_sprite_draw_image(self->sprite, 
    //                       vector2d(self->position.x + self->drawOffset.x,self->position.y + self->drawOffset.y));
    
    gf3d_sprite_draw(
        self->sprite,
        vector2d(self->position.x,self->position.y),
        vector2d(1,1),
        self->frame
    );
    

}

void menu_draw_group(int group)
{
    int i;
    for (i = 0;i < menu_manager.maxMenus;i++)
    {
        if (!menu_manager.menuList[i]._inuse)continue;
        if (menu_manager.menuList[i].group == group)menu_draw(&menu_manager.menuList[i]);
    }
}

Menu *menu_generic(
    int         group,
    SDL_Rect    box,
    Vector2D    drawOffset,
    int         buttonFrame,
    Sprite      *sprite,
    void        (*think)(struct Menu_S *self)
){
    Menu *menu;
    menu = menu_new();
    menu->group = group;
    menu->box = box;
    menu->drawOffset = drawOffset;
    menu->sprite = sprite;
    menu->think = think;
    menu->position = vector2d(menu->box.x,menu->box.y);
    return menu;
}

void menu_genericV(
    int         group,
    SDL_Rect    box,
    Vector2D    drawOffset,
    int         buttonFrame,
    Sprite      *sprite,
    void        (*think)(struct Menu_S *self)
){
    Menu *menu;
    menu = menu_new();
    menu->group = group;
    menu->box = box;
    menu->think = think;

    menu->drawOffset = drawOffset;
    if(sprite == NULL)
    {
        menu->sprite = NULL;
    }else{
        menu->sprite = sprite;
        menu->frame = buttonFrame;
    }

}

void createMenus()
{
    SDL_Rect quitBox, startBox, mainMBox;
    Vector2D blank = vector2d(0,0);
    Sprite *startSprite, *quitSprite, *mainMSprite;
    startSprite = gf3d_sprite_load("images/startButton.png",107,23,1);
    quitSprite = gf3d_sprite_load("images/quitButton.png",107,23,1);
    mainMSprite = gf3d_sprite_load("images/mainMButton.png",107,23,1);
    

    //------------------------------------------MAIN_MENU--------------------------------
    gfc_rect_set(quitBox,400,400,107,23);
    gfc_rect_set(startBox,400,500,107,23);
    gfc_rect_set(mainMBox,400,600,107,23);
    menu_generic(MAIN_MENU,quitBox,blank,B_QUIT,quitSprite,quitThink);
    menu_generic(MAIN_MENU,startBox,blank,B_START,startSprite,startThink);

    menu_generic(IN_GAME,quitBox,blank,B_QUIT,quitSprite,quitThink);
    menu_generic(IN_GAME,mainMBox,blank,B_START,mainMSprite,mainMThink);

}

void quitThink(Menu *self)
{
    //last_level_change = 0;
    int mx,my;
    SDL_GetMouseState(&mx,&my);
    if (collide_menu(self->box, vector2d(mx,my)))
    {
        if ((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && (SDL_GetTicks() - last_level_change >= 200))
        {
            last_level_change = SDL_GetTicks();
            level_get_active()->done = 1;
        }
    }
}

void startThink(Menu *self)
{
    //last_level_change = 0;
    int mx,my;
    SDL_GetMouseState(&mx,&my);
    if (collide_menu(self->box, vector2d(mx,my)))
    {
        if ((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && (SDL_GetTicks() - last_level_change >= 200))
        {
            last_level_change = SDL_GetTicks();
            level_get_active()->paused = 0;
            //world_load("config/testworld.json");
            level_get_active()->screen = IN_GAME;
        }
    }
}

void mainMThink(Menu *self)
{
    //last_level_change = 0;
    int mx,my;
    SDL_GetMouseState(&mx,&my);
    if (collide_menu(self->box, vector2d(mx,my)))
    {
        if ((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && (SDL_GetTicks() - last_level_change >= 200))
        {
            last_level_change = SDL_GetTicks();
            //level_get_active()->paused = 1;
            level_get_active()->screen = MAIN_MENU;
        }
    }
}
