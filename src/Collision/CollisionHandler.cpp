#include "CollisionHandler.h"
#include "../Core/Engine.h"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <cstdint>
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
    int rightTile   = (a.x + (a.w-1)) / tilesize;
    int8_t collisionZone = 0;

    if( leftTile >= colCount )
        leftTile -= colCount;
    if( rightTile >= colCount )
        rightTile -= colCount;

    int topTile     = std::clamp(   a.y            / tilesize, 0, rowCount - 1);
    int bottomTile  = std::clamp(  (a.y + (a.h-1)) / tilesize, 0, rowCount - 1);

    for( x = leftTile; x != rightTile+1; x++ ){
        x = (x + colCount) % colCount; // Ajusta x dentro de los límites de colCount

        for( y = topTile; y <= bottomTile; y++){
            if(collisionTileMap[y][x] > 0){
                if (y == topTile) 
                    collisionZone |= CollisionZone::top;
                if (y == bottomTile) 
                    collisionZone |= CollisionZone::bottom;
                if (x == leftTile) 
                    collisionZone |= CollisionZone::left;
                if (x == rightTile) 
                    collisionZone |= CollisionZone::right;
            }
        }
    }

    return collisionZone;
}

Vector2D CollisionHandler::mostPlausibleMove(Vector2D lastSafePosition, Vector2D newPosition, Collider *collider, int8_t *collisionZone){
    Vector2D position = newPosition;
    Vector2D trajectory = newPosition - lastSafePosition;
    if( (newPosition - lastSafePosition) == 0.0 )
        return newPosition;
    float newX, newY;

    position = getFirstCollision( lastSafePosition, newPosition, collider, collisionZone );

    if( (trajectory = newPosition - position) != 0 ){
        lastSafePosition = position;
        
        collider->setCoordenates( position.x + trajectory.x , position.y );
        if( mapCollision(collider->getCollisionBox()) )
            newX = CollisionHandler::getInstance()->getFirstCollision( 
                    lastSafePosition, 
                    Vector2D(position.x + trajectory.x, position.y), 
                    collider, 
                    collisionZone 
                    ).x;
        else
            newX = position.x + trajectory.x;

        collider->setCoordenates( position.x , position.y + trajectory.y );
        if( mapCollision(collider->getCollisionBox()) )
            newY = CollisionHandler::getInstance()->getFirstCollision( 
                    lastSafePosition, 
                    Vector2D(position.x, position.y + trajectory.y), 
                    collider, 
                    collisionZone 
                    ).y;
        else
            newY = position.y + trajectory.y;

        if( abs(newX - position.x) > abs(newY - position.y) )
            position.x = newX;
        else if( abs(newX - position.x) < abs(newY - position.y) )
            position.y = newY;
        
    }
    return position;
}

Vector2D CollisionHandler::getFirstCollision(Vector2D lastSafePosition, Vector2D newPosition, Collider *collider, int8_t *collisionZone) {

    float t = 0;
    Vector2D difference = newPosition - lastSafePosition;
    Vector2D direction = difference.normalize();
    if( direction.x == 0 && direction.y == 0 )
        return newPosition;

    Vector2D rayPosition = lastSafePosition;
    float distance = difference.length();

    if( abs(difference.x) > tilesize && abs(difference.y) > tilesize ){
        for (t = 0; t <= distance; t += tilesize) {
            rayPosition = lastSafePosition + (direction * t);
            collider->setCoordenates( rayPosition.x, rayPosition.y );
            if( (*collisionZone = mapCollision( collider->getCollisionBox() )) ){
                t -= tilesize;
                break;
            }
        }
    }

    for (t = t != 0? t: 0; t <= distance; ++t) {
        rayPosition = lastSafePosition + (direction * t);

        collider->setCoordenates( rayPosition.x, rayPosition.y );
        if( (*collisionZone = mapCollision( collider->getCollisionBox() )) ){
            return rayPosition - direction;
        }
    }

    return newPosition;
}

