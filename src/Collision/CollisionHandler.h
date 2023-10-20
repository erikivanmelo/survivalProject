#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "../Map/TileLayer.h"
#include "../Physics/Vector2D.h"
#include "../Physics/Collider.h"
#include <SDL2/SDL_rect.h>
#include <cstdint>

namespace CollisionZone{
    enum{
        top = 8,
        bottom = 16,
        left = 32,
        right = 64
    };
}

class CollisionHandler
{
public:
    bool checkColission(SDL_Rect a, SDL_Rect b);
    int8_t mapCollision(SDL_Rect a);
    Vector2D getFirstCollision(Vector2D lastSafePosition, Vector2D newPosition, Collider *collider, int8_t *collisionZone);
    Vector2D mostPlausibleMove(Vector2D lastSafePosition, Vector2D newPosition, Collider *collider, int8_t *collisionZone);
    Vector2D resolveCollision(Vector2D position, Vector2D trajectory, Collider *collider, int8_t *collisionZone, bool horizontal);

    inline static CollisionHandler* getInstance(){return instance = (instance == nullptr)? new CollisionHandler():instance;}
    ~CollisionHandler(){
    }
private:

    CollisionHandler();
    Vector2D normalizePosition( Vector2D position, int8_t *collisionZone, Vector2D direction);

    TileMap collisionTileMap;
    static CollisionHandler *instance;

    int colCount;
    int rowCount;
    int tilesize;


};

#endif // COLLISIONHANDLER_H
