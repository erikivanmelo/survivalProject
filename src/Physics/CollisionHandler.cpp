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
    gameMap(Engine::get()->getMap()),
    colCount(gameMap->getTileWidth()),
    rowCount(gameMap->getTileHeight())
{}

bool CollisionHandler::checkColission(SDL_FRect a, SDL_FRect b)
{
    return SDL_GetRectIntersectionFloat(&a, &b, nullptr);
}


int8_t CollisionHandler::mapCollision(SDL_FRect *a)
{
    unsigned int x,y;
    int8_t collisionZone = COLLISION_ZONE_NONE;
    const unsigned int leftTile    = Helper::wrapToRange(a->x / TILE_SIZE, colCount);
    const unsigned int rightTile   = Helper::wrapToRange((a->x + (a->w-1)) / TILE_SIZE,colCount);
    const unsigned int topTile     = std::clamp((int)   a->y            / TILE_SIZE, 0, rowCount - 1);
    const unsigned int bottomTile  = std::clamp((int)  (a->y + (a->h-1)) / TILE_SIZE, 0, rowCount - 1);
    const unsigned int xEnd = rightTile+1;

    x = leftTile;
    do{
        x = Helper::wrapToRange(x, colCount);
        for( y = topTile; y <= bottomTile; ++y){
            if( !gameMap->getTile(x,y) )
                continue;

            if (y == topTile) 
                collisionZone |= COLLISION_ZONE_TOP;
            else if (y == bottomTile) 
                collisionZone |= COLLISION_ZONE_BOTTOM;

            if (x == leftTile) 
                collisionZone |= COLLISION_ZONE_LEFT;
            else if (x == rightTile) 
                collisionZone |= COLLISION_ZONE_RIGHT;
        }
        x++;
    }while(x != xEnd);

    return collisionZone;
}

Vector2D CollisionHandler::mostPlausiblePosition(Vector2D lastSafePosition, Vector2D newPosition, Collider *collider, int8_t *collisionZone){
    Vector2D trajectory = newPosition - lastSafePosition;
    if( trajectory == 0 )
        return newPosition;

    collider->setCoordinates(newPosition);
    Vector2D position = getFirstCollision( lastSafePosition, newPosition, collider, collisionZone );
    Vector2D newtrajectory = newPosition - position;
    if( newtrajectory == 0 )
        return position;

    collider->setCoordinates( position.x + newtrajectory.x , position.y );
    float newX = mapCollision(collider->getCollisionBox())? 
            CollisionHandler::get()->getFirstCollision( 
            position, 
            Vector2D(position.x + newtrajectory.x, position.y), 
            collider, 
            collisionZone 
            ).x : position.x + newtrajectory.x;

    collider->setCoordinates( position.x , position.y + newtrajectory.y );
    float newY = mapCollision(collider->getCollisionBox())?
            CollisionHandler::get()->getFirstCollision( 
            position, 
            Vector2D(position.x, position.y + newtrajectory.y), 
            collider, 
            collisionZone 
            ).y : position.y + newtrajectory.y;

    float trajectoryX = newX - position.x;
    float trajectoryY = newY - position.y;

    
    if( abs(trajectoryX) > abs(trajectoryY) ){
        position.x = newX;

        *collisionZone = COLLISION_ZONE_NONE;
        if( trajectory.y > 0 )
            *collisionZone |= COLLISION_ZONE_BOTTOM;
        else if( trajectory.y < 0 )
            *collisionZone |= COLLISION_ZONE_TOP;

    }else if( abs(trajectoryX) < abs(trajectoryY) ){
        position.y = newY;
    
        *collisionZone = COLLISION_ZONE_NONE;
        if( trajectory.x > 0 )
            *collisionZone |= COLLISION_ZONE_RIGHT;
        else if( trajectory.x < 0 )
            *collisionZone |= COLLISION_ZONE_LEFT;
    }

    return position;
}

Vector2D CollisionHandler::getFirstCollision(Vector2D startPosition, Vector2D endPosition, Collider *collider, int8_t *collisionZone) {
    Vector2D difference = endPosition - startPosition;
    Vector2D direction = difference.normalize();
    // If the direction is 0, the start position is the same as the end position
    if( direction == 0 )
        return endPosition;

    float distance = difference.length();
    Vector2D rayPosition = startPosition;
    int journey = 0;
    int step = ( abs(difference.x) > TILE_SIZE && abs(difference.y) > TILE_SIZE )? TILE_SIZE : 1;

    if (distance < step)
        return startPosition;

    do{
        collider->setCoordinates( rayPosition.x, rayPosition.y );
        if( (*collisionZone = mapCollision( collider->getCollisionBox() )) ){
            if( step == 1)
                return rayPosition - direction;
            else{
                rayPosition -= direction;
                journey -= step;
                step = 1;
            }
        }
        journey += step;
        rayPosition += direction;
    }while( journey <= distance );

    return endPosition;
}

