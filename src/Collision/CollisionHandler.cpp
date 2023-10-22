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
    int8_t collisionZone = CollisionZone::none;

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
    Vector2D newtrajectory;
    if( (newtrajectory = newPosition - position) != 0 ){
        Vector2D newLastSafePosition = position;
        
        collider->setCoordenates( position.x + newtrajectory.x , position.y );
        if( mapCollision(collider->getCollisionBox()) )
            newX = CollisionHandler::getInstance()->getFirstCollision( 
                    newLastSafePosition, 
                    Vector2D(position.x + newtrajectory.x, position.y), 
                    collider, 
                    collisionZone 
                    ).x;
        else
            newX = position.x + newtrajectory.x;

        collider->setCoordenates( position.x , position.y + newtrajectory.y );
        if( mapCollision(collider->getCollisionBox()) )
            newY = CollisionHandler::getInstance()->getFirstCollision( 
                    newLastSafePosition, 
                    Vector2D(position.x, position.y + newtrajectory.y), 
                    collider, 
                    collisionZone 
                    ).y;
        else
            newY = position.y + newtrajectory.y;

        float trajectoryX = newX - position.x;
        float trajectoryY = newY - position.y;

        
        if( abs(trajectoryX) > abs(trajectoryY) ){
            position.x = newX;

            *collisionZone = CollisionZone::none;
            if( trajectory.y > 0 )
                *collisionZone |= CollisionZone::bottom;
            else if( trajectory.y < 0 )
                *collisionZone |= CollisionZone::top;

        }else if( abs(trajectoryX) < abs(trajectoryY) ){
            position.y = newY;
        
            *collisionZone = CollisionZone::none;
            if( trajectory.x > 0 )
                *collisionZone |= CollisionZone::right;
            else if( trajectory.x < 0 )
                *collisionZone |= CollisionZone::left;
        }

    }
    //SDL_Log("%c-%c-%c-%c",
        //(*collisionZone & CollisionZone::top   )?'T':' ', 
        //(*collisionZone & CollisionZone::bottom)?'B':' ',
        //(*collisionZone & CollisionZone::left  )?'L':' ',
        //(*collisionZone & CollisionZone::right )?'R':' ');
    return position;
}

Vector2D CollisionHandler::getFirstCollision(Vector2D lastSafePosition, Vector2D newPosition, Collider *collider, int8_t *collisionZone) {
    Vector2D difference = newPosition - lastSafePosition;
    Vector2D direction = difference.normalize();
    if( direction == 0 )
        return newPosition;

    float distance = difference.length();
    Vector2D rayPosition = lastSafePosition;
    int t = 0, step = ( abs(difference.x) > tilesize && abs(difference.y) > tilesize )? tilesize : 1;

    while( t <= distance ){
        collider->setCoordenates( rayPosition.x, rayPosition.y );
        if( (*collisionZone = mapCollision( collider->getCollisionBox() )) ){
            if( step == 1)
                return rayPosition - direction;
            else{
                rayPosition -= direction;
                t -= step;
                step = 1;
            }
        }
        t += step;
        rayPosition += direction;
    }

    return newPosition;
}

