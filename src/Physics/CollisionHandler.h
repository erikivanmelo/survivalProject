#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "../Physics/Vector2D.h"
#include "../Physics/Collider.h"
#include "../Map/GameMap.h"
#include <SDL3/SDL_rect.h>
#include <cstdint>

#define COLLISION_ZONE_NONE    0
#define COLLISION_ZONE_TOP     8
#define COLLISION_ZONE_BOTTOM   16
#define COLLISION_ZONE_LEFT     32
#define COLLISION_ZONE_RIGHT    64

class CollisionHandler
{
public:


    bool checkColission(SDL_FRect a, SDL_FRect b);
    int8_t mapCollision(SDL_FRect *a);
    Vector2D getFirstCollision(Vector2D lastSafePosition, Vector2D newPosition, Collider *collider, int8_t *collisionZone);
    Vector2D mostPlausiblePosition(Vector2D lastSafePosition, Vector2D newPosition, Collider *collider, int8_t *collisionZone);
    Vector2D resolveCollision(Vector2D position, Vector2D trajectory, Collider *collider, int8_t *collisionZone, bool horizontal);

    inline static CollisionHandler* get(){return instance = (instance == nullptr)? new CollisionHandler():instance;}
    ~CollisionHandler(){
    }

    inline bool isCharacterIn(int x, int y, SDL_FRect *playerBox) {
    x *= tilesize;
    y *= tilesize;
    return  (
                playerBox->x < x + tilesize         &&
                playerBox->x     + playerBox->w > x &&
                playerBox->y < y + tilesize         &&
                playerBox->y     + playerBox->h > y
            );
    }

private:

    CollisionHandler();

    GameMap *gameMap;
    static CollisionHandler *instance;

    int colCount;
    int rowCount;
    int tilesize;


};

#endif // COLLISIONHANDLER_H
