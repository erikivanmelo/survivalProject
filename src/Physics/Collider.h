#ifndef COLLIDER_H
#define COLLIDER_H

#include <SDL2/SDL_rect.h>

#include "../Camera/Camera.h"
#include "Vector2D.h"

class Collider
{
public:

    Collider(){
        box = new SDL_Rect();
        buffer = new SDL_Rect();
    }

    ~Collider(){
        delete box;
        delete buffer;
    }
    inline SDL_Rect *getCollisionBox(){return box;}
    inline SDL_Rect *getBuffer(){return buffer;}

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

    inline void setCoordenates(int x, int y){
        box->x = x - buffer->x;
        box->y = y - buffer->y;
    }

    inline void setCoordenates(Vector2D v){ setCoordenates(v.x,v.y); }

    void draw(){
        static Vector2D *cam = Camera::getInstance()->getPosition();
        SDL_Rect tmp = { box->x - (int)cam->x, box->y - (int)cam->y, box->w, box->h };
        SDL_SetRenderDrawColor(Engine::getInstance()->getRenderer(),
                           255, 0, 0,255);
        SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &tmp);
    }

private:
    SDL_Rect *box;
    SDL_Rect *buffer;
};

#endif // COLLIDER_H
