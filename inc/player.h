#ifndef H_PLAYER
#define H_PLAYER
#include <genesis.h>

#define UP 0
#define DOWN 2
#define LEFT 1
#define RIGHT 1
#define IDLE 3

#define JUMP 14

#define GRAVITY 1

typedef struct{
    s16 x;
    s16 y;
}Point;

typedef struct{
    s16 dx;
    s16 dy;
}Vector;

struct{
    Sprite * sprite;
    Point position;
    u8 direction;
    bool isJumping;
    bool flip;
    Vector spd;
}Player;

#endif