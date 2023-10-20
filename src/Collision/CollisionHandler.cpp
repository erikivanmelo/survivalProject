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
    int rightTile   = (a.x + a.w) / tilesize;
    int8_t retorno = 0;

    if( leftTile >= colCount )
        leftTile -= colCount;
    if( rightTile >= colCount )
        rightTile -= colCount;

    int topTile     = std::clamp(   a.y        / tilesize, 0, rowCount - 1);
    int bottomTile  = std::clamp(  (a.y + a.h) / tilesize, 0, rowCount - 1);

    for( x = leftTile; x != rightTile+1; x++ ){
        x = (x + colCount) % colCount; // Ajusta x dentro de los límites de colCount

        for( y = topTile; y <= bottomTile; y++){
            if(collisionTileMap[y][x] > 0){
                if (y == topTile || y == bottomTile || x == leftTile || x == rightTile) {
                    retorno |= (y == topTile ? CollisionZone::top : 0) |
                               (y == bottomTile ? CollisionZone::bottom : 0) |
                               (x == leftTile ? CollisionZone::left : 0) |
                               (x == rightTile ? CollisionZone::right : 0);
                }
            }
        }
    }

    return retorno;
}

Vector2D CollisionHandler::mostPlausibleMove(Vector2D lastSafePosition, Vector2D newPosition, Collider *collider, int8_t *collisionZone){
    Vector2D position = newPosition;
    Vector2D trajectory = newPosition - lastSafePosition;

    position = getFirstCollision( lastSafePosition, newPosition, collider, collisionZone );

    bool isDiagonalCollision = (*collisionZone & CollisionZone::left && *collisionZone & CollisionZone::top) ||
                           (*collisionZone & CollisionZone::left && *collisionZone & CollisionZone::bottom) ||
                           (*collisionZone & CollisionZone::right && *collisionZone & CollisionZone::top) ||
                           (*collisionZone & CollisionZone::right && *collisionZone & CollisionZone::bottom);

    if( trajectory != 0.0 && isDiagonalCollision ){
        lastSafePosition = position;
        trajectory = newPosition - lastSafePosition;

        collider->setCoordenates( position.x + trajectory.x , position.y );
        if(trajectory.x != 0){
            if( mapCollision(collider->getCollisionBox()) ){
                position.x = CollisionHandler::getInstance()->getFirstCollision( lastSafePosition, Vector2D(position.x + trajectory.x, position.y), collider, collisionZone ).x;
            }else{
                position.x += trajectory.x;
            }
        }

        collider->setCoordenates( position.x , position.y + trajectory.y );
        if(trajectory.y != 0){
            if( mapCollision(collider->getCollisionBox()) ){
                position.y = CollisionHandler::getInstance()->getFirstCollision( lastSafePosition, Vector2D(position.x, position.y + trajectory.y), collider, collisionZone ).y;
            }else{
                position.y += trajectory.y;
            }
        }
    }
    return position;
}

Vector2D CollisionHandler::getFirstCollision(Vector2D lastSafePosition, Vector2D newPosition, Collider *collider, int8_t *collisionZone) {

    Vector2D difference = newPosition - lastSafePosition;
    Vector2D direction = difference.normalize();
    if( direction.x == 0 && direction.y == 0 )
        return newPosition;

    Vector2D rayPosition = lastSafePosition;
    float distance = difference.length();

    if( abs(difference.x) < tilesize && abs(difference.y) < tilesize && (
        direction.x != 0 && direction.y == 0 || direction.x == 0 && direction.y != 0
        )
    ){
        Vector2D ret = normalizePosition( newPosition, collisionZone, direction );
        collider->setCoordenates( ret );
        if( mapCollision( collider->getCollisionBox() ) == 0 ){
            SDL_Log("primer tipo colision");
            return ret;
        }
    }

    if( abs(difference.x) > tilesize && abs(difference.y) > tilesize ){
        for (float t = 0; t <= distance; t += tilesize) {
            rayPosition = lastSafePosition + (direction * t);
            collider->setCoordenates( rayPosition.x, rayPosition.y );
            if( (*collisionZone = mapCollision( collider->getCollisionBox() )) ){
                SDL_Log("segundo tipo colision");
                return normalizePosition( rayPosition, collisionZone, direction );
            }
        }
    }

    const float stepSize = 1 / max( abs(difference.x), abs(difference.y) );
    for (float t = 0; t <= distance; t += stepSize) {
        rayPosition = lastSafePosition + (direction * t);

        collider->setCoordenates( rayPosition.x, rayPosition.y );
        if( (*collisionZone = mapCollision( collider->getCollisionBox() )) ){
            SDL_Log("tercer tipo colision");
            return (rayPosition+1) - direction;
        }
    }

    return newPosition;
}

Vector2D CollisionHandler::normalizePosition( Vector2D position, int8_t *collisionZone , Vector2D direction){
    if( *collisionZone == 0)
        return position;

    position.log("sin normalizar");

    Vector2D newPosition = position;

    
    if( *collisionZone & CollisionZone::right && direction.x > 0 )
        newPosition.x =  int(floor(position.x/8))*8;
    else if( *collisionZone & CollisionZone::left && direction.x < 0 )
        newPosition.x = int(ceil(position.x/8))*8;

    if( *collisionZone & CollisionZone::top && direction.y < 0)
        newPosition.y =  int(ceil(position.y/8))*8;
    else if( *collisionZone & CollisionZone::bottom && direction.y > 0)
        newPosition.y = int(floor(position.y/8))*8;

    newPosition.log("normalizado");

    return newPosition;
}
