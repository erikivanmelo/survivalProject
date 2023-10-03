#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "../Map/TileLayer.h"
#include <SDL2/SDL_rect.h>


class CollisionHandler
{
public:
    bool checkColission(SDL_Rect a, SDL_Rect b);
    int8_t mapCollision(SDL_Rect a);

    inline static CollisionHandler* getInstance(){return instance = (instance == nullptr)? new CollisionHandler():instance;}
    ~CollisionHandler(){
        delete collisionLayer;
    }
private:

    CollisionHandler();

    TileMap collisionTileMap;
    TileLayer *collisionLayer;
    static CollisionHandler *instance;

    int colCount;
    int rowCount;
    int tilesize;


};

#endif // COLLISIONHANDLER_H
//#ifndef COLLISIONHANDLER_H
//#define COLLISIONHANDLER_H

//#include "../Map/TileLayer.h"
//#include <SDL2/SDL_rect.h>

//namespace CollisionZone{
    //enum{
        //top = 8,
        //bottom = 16,
        //left = 32,
        //right = 64
    //};
//}

//class CollisionHandler
//{
//public:
    //bool checkColission(SDL_Rect a, SDL_Rect b);
    //int8_t mapCollision(SDL_Rect a);

    //inline static CollisionHandler* getInstance(){return instance = (instance == nullptr)? new CollisionHandler():instance;}
    //~CollisionHandler(){
        //delete collisionLayer;
    //}
//private:

    //CollisionHandler();

    //TileMap collisionTileMap;
    //TileLayer *collisionLayer;
    //static CollisionHandler *instance;


//};

//#endif // COLLISIONHANDLER_H
