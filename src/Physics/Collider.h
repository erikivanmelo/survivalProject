#ifndef COLLIDER_H
#define COLLIDER_H

#include <SDL3/SDL_rect.h>

#include "../Camera/Camera.h"
#include "Vector2D.h"

class Collider
{
public:

    Collider(){
        box = new SDL_FRect();
        buffer = new SDL_FRect();
    }

    ~Collider(){
        delete box;
        delete buffer;
    }
    inline SDL_FRect *getCollisionBox(){return box;}
    inline SDL_FRect *getBuffer(){return buffer;}

    inline void setBuffer(int x, int y, int w, int h){ 
        buffer->x = x;
        buffer->y = y;
        buffer->w = w;
        buffer->h = h;
    }
    inline void setCollisionBox(int w, int h){
        box->w = w - buffer->w; 
        box->h = h - buffer->h;
    }

    inline void setCoordinates(int x, int y){
        box->x = x - buffer->x;
        box->y = y - buffer->y;
    }

    inline void setCoordinates(Vector2D v){ setCoordinates(v.x,v.y); }

    void draw();

private:
    SDL_FRect *box;
    SDL_FRect *buffer;
};

#endif // COLLIDER_H
