#include "CollisionHandler.h"
#include "../Core/Engine.h"
#include "../Helper.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_surface.h>
#include <cstdint>
#include <iostream>
#include <algorithm>

CollisionHandler *CollisionHandler::instance = nullptr;

CollisionHandler::CollisionHandler():
    gameMap(Engine::getInstance()->getMap())
{
    tilesize = AssetsManager::getInstance()->getTileset()->tileSize;
    rowCount = gameMap->getTileHeight();
    colCount = gameMap->getTileWidth();
}

bool CollisionHandler::checkColission(SDL_FRect a, SDL_FRect b)
{
    return SDL_GetRectIntersectionFloat(&a, &b, nullptr);
}


int8_t CollisionHandler::mapCollision(SDL_FRect *a)
{
    int x,y;
    int8_t collisionZone = CollisionZone::none;
    const int leftTile    = Helper::wrapToRange(a->x / tilesize, colCount);
    const int rightTile   = Helper::wrapToRange((a->x + (a->w-1)) / tilesize,colCount);
    const int topTile     = std::clamp((int)   a->y            / tilesize, 0, rowCount - 1);
    const int bottomTile  = std::clamp((int)  (a->y + (a->h-1)) / tilesize, 0, rowCount - 1);

    x = leftTile;
    do{
        x = Helper::wrapToRange(x, colCount);
        for( y = topTile; y <= bottomTile; y++){
            if( !gameMap->getTile(x,y) )
                continue;

            if (y == topTile) 
                collisionZone |= CollisionZone::top;
            else if (y == bottomTile) 
                collisionZone |= CollisionZone::bottom;

            if (x == leftTile) 
                collisionZone |= CollisionZone::left;
            else if (x == rightTile) 
                collisionZone |= CollisionZone::right;
        }
        x++;
    }while(x != rightTile+1);

    return collisionZone;
}

Vector2D CollisionHandler::mostPlausiblePosition(Vector2D lastSafePosition, Vector2D newPosition, Collider *collider, int8_t *collisionZone){
    Vector2D position = newPosition;
    Vector2D trajectory = newPosition - lastSafePosition;
    if( (newPosition - lastSafePosition) == 0 )
        return newPosition;

    position = getFirstCollision( lastSafePosition, newPosition, collider, collisionZone );
    Vector2D newtrajectory;
    if( (newtrajectory = newPosition - position) != 0 ){
        float newX, newY;
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

    do{
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
    }while( t <= distance );

    return newPosition;
}

