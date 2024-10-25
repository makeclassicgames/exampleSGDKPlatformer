/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>

#include "player.h"
#include "collision.h"

#include "maps.h"
#include "sprt.h"

Map * map;

void inputHandler(u16,u16,u16);
void readInput();
void updatePhysics();

int main()
{
    u16 index = TILE_USER_INDEX;
    Player.direction=IDLE;
    Player.position.x=20;
    Player.position.y=137;
    Player.flip=FALSE;
    Player.isJumping=FALSE;
    Player.spd.dx=0;
    Player.spd.dy=0;
    VDP_drawImageEx(BG_B, &fondo1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, index), 0, 0, TRUE, DMA);
    index+= fondo1.tileset->numTile;
    VDP_loadTileSet(&tilesetmapa1, index, CPU);
    PAL_setPalette(PAL1, palmapa1.data,CPU);
    map= MAP_create(&mapa1,BG_A,TILE_ATTR_FULL(PAL1, FALSE,FALSE,FALSE,index));
    MAP_scrollTo(map,0,0);
    Sprite * sprite = SPR_addSprite(&zera, Player.position.x, Player.position.y, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    Player.sprite = sprite;
    PAL_setPalette(PAL2, zera.palette->data,CPU);
    JOY_setEventHandler(inputHandler);
    while(1)
    {
        readInput();
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        updatePhysics();
        SPR_setPosition(Player.sprite, Player.position.x, Player.position.y);
        SPR_setAnim(Player.sprite, Player.direction);
        SPR_setHFlip(Player.sprite, Player.flip);
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}

void updatePhysics(){
    Player.position.y+=Player.spd.dy;
    Player.spd.dy+=GRAVITY;
    u16 tile_x = Player.position.x>>3;
    u16 tile_y = (Player.position.y>>3)+4;
    if(collision_map1[tile_y*40+tile_x]!=1){
        Player.spd.dy=0;
        Player.isJumping=FALSE;
    }
    tile_x = Player.position.x>>3;
    tile_y = (Player.position.y>>3);

    if(Player.direction==RIGHT){
        tile_x+=3;
    }

    if(Player.direction==LEFT){
        tile_x-=1;
    }

    if(collision_map1[tile_y*40+tile_x]!=1){
        Player.spd.dx=0;
    }

    Player.position.x+=Player.spd.dx;
}

void readInput(){
    u16 value = JOY_readJoypad(JOY_1);
    if(value & BUTTON_LEFT){
        Player.spd.dx=-1;
        Player.direction=LEFT;
        Player.flip=TRUE;
    }else if(value & BUTTON_RIGHT){
        Player.spd.dx=1;
        Player.direction=RIGHT;
        Player.flip=FALSE;
    }else{
        Player.spd.dx=0;
        Player.direction=IDLE;
    }
}

void inputHandler(u16 joy,u16 state,u16 changed){
    if(joy == JOY_1){
        if((state & BUTTON_C & changed) && !Player.isJumping){
            Player.isJumping=TRUE;
            Player.spd.dy=-JUMP;
            Player.direction=IDLE;
        }
    }
}
