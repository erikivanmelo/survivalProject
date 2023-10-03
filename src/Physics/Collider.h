#ifndef COLLIDER_H
#define COLLIDER_H

#include <SDL2/SDL_rect.h>

#include "../Camera/Camera.h"

class Collider
{
public:

    inline SDL_Rect getCollisionBox(){return box;}
    inline SDL_Rect getBuffer(){return buffer;}

    inline void setBuffer(int x, int y, int w, int h){ buffer = {x,y,w,h}; }
    //inline void setCollisionBox(int w, int h){box.w = w-buffer.w; box.h = h-buffer.h;}
    inline void setCollisionBox(int w, int h){
        box.w = w - buffer.w; 
        box.h = h - buffer.h;
    }

    inline void setCoordenates(int x, int y){
        box.x = x - buffer.x;
        box.y = y - buffer.y;
    }

    void draw(){
        Vector2D cam = Camera::getInstance()->getPosition();
        box.x -= cam.x;
        box.y -= cam.y;
        SDL_SetRenderDrawColor(Engine::getInstance()->getRenderer(),
                           255, 0, 0,255);
        SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &box);
    }

private:
    SDL_Rect box;
    SDL_Rect buffer;
};

#endif // COLLIDER_H
//#ifndef COLLIDER_H
//#define COLLIDER_H

//#include <SDL2/SDL_rect.h>

//#include "../Camera/Camera.h"

//class Collider
//{
//public:
    //Collider(): 
        //box({0,0,0,0}),
        //buffer({0,0,0,0})
        //{}

    //inline SDL_Rect getCollisionBox(){return box;}
    //inline SDL_Rect getBuffer(){return box;}
    //inline void setBuffer(int x, int y, int w, int h){ buffer = {x,y,w,h}; }
    //inline void setCollisionBox(int w, int h){box.w = w-buffer.w; box.h = h-buffer.h;}

    //inline void setCoordenates(int x, int y){
        //box.x = x - buffer.x;
        //box.y = y - buffer.y;
    //}

    //void draw(){
        //Vector2D cam = Camera::getInstance()->getPosition();
        //box.x -= cam.x;
        //box.y -= cam.y;
        //SDL_SetRenderDrawColor(Engine::getInstance()->getRenderer(),
                           //255, 0, 0,255);
        //SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &box);
    //}

//private:
    //SDL_Rect box;
    //SDL_Rect buffer;
//};

//#endif // COLLIDER_H
