#include "CollisionHandler.h"
#include "../Core/Engine.h"
#include <iostream>
#include <algorithm>

CollisionHandler *CollisionHandler::instance = nullptr;

CollisionHandler::CollisionHandler()
{
    const TileLayer *collisionLayer = Engine::getInstance()->getMap()->getMapLayers()[GameMap::foreground];
    collisionTileMap = collisionLayer->getTileMap();
    tilesize = collisionLayer->getTileSize();
    rowCount = collisionLayer->getRowCount();
    colCount = collisionLayer->getColCount();
}

bool CollisionHandler::checkColission(SDL_Rect a, SDL_Rect b)
{
    return SDL_IntersectRect(&a, &b, nullptr);
}


int8_t CollisionHandler::mapCollision(SDL_Rect a)
{
    int x,y;
    int leftTile    = a.x / tilesize;
    int rightTile   = (a.x + a.w) / tilesize;

    if( leftTile >= colCount )
        leftTile -= colCount;
    if( rightTile >= colCount )
        rightTile -= colCount;

    int topTile     = std::clamp(   a.y        / tilesize, 0, rowCount - 1);
    int bottomTile  = std::clamp(  (a.y + a.h) / tilesize, 0, rowCount - 1);

    for( x = leftTile; x != rightTile+1; x++ ){
        if( x >= colCount)
            x -= colCount; 
        for( y = topTile; y <= bottomTile; y++){
            if(collisionTileMap[y][x] > 0){
                return true;
            }
        }
    }

    return false;
}

