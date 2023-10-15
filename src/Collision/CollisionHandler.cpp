#include "CollisionHandler.h"
#include "../Core/Engine.h"
#include <iostream>

CollisionHandler *CollisionHandler::instance = nullptr;

CollisionHandler::CollisionHandler()
{
    TileLayer *collisionLayer = Engine::getInstance()->getMap()->getMapLayers()[GameMap::foreground];
    collisionTileMap = collisionLayer->getTileMap();
    tilesize = collisionLayer->getTileSize();
    rowCount = collisionLayer->getRowCount();
    colCount = collisionLayer->getColCount();
}

bool CollisionHandler::checkColission(SDL_Rect a, SDL_Rect b)
{
    bool x_overleaps = (a.x < b.x + b.w) && (a.x < a.w + b.x);
    bool y_overleaps = (a.y < b.y + b.h) && (a.y < a.h + b.y);
    return x_overleaps && y_overleaps;
}


int8_t CollisionHandler::mapCollision(SDL_Rect a)
{

    int leftTile = a.x / tilesize;
    int rightTile = ( a.x + a.w ) / tilesize;

    int topTile = a.y / tilesize;
    int bottomTile = ( a.y + a.h ) / tilesize;

    if(leftTile < 0) leftTile = 0;
    if(rightTile > colCount) rightTile = colCount;

    if(topTile < 0) topTile = 0;
    if(bottomTile > rowCount) bottomTile = rowCount;

    for(int x = leftTile; x <= rightTile; x++ ){
        for(int y = topTile; y <= bottomTile; y++){
            if(collisionTileMap[y][x] > 0){
                return true;
            }
        }
    }

    return false;
}

