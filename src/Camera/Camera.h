#ifndef CAMERA_H
#define CAMERA_H



#include <SDL2/SDL.h>
#include "../Core/Engine.h"
#include "../Physics/Point.h"
#include "../Physics/Vector2D.h"
#include "../Map/TileLayer.h"

class Camera
{
public:
    inline static Camera *getInstance(){ return instance = (instance == nullptr)? new Camera() : instance; }
    inline static void clean(){ delete instance; }

    inline SDL_Rect getViewBox()const{return viewBox;}
    inline Vector2D getPosition()const{return position;}
    inline void setTarget(Point *target){this->target = target;}

    inline void setViewBoxSize(int width, int height){
       viewBox.w = static_cast<int>(width/scala.w);
       viewBox.h = static_cast<int>(height/scala.h);
    }

    void update();

    ~Camera(){}
private:
    Camera(){
        viewBox = {
            0,
            0,
            static_cast<int>(SCREEN_WIDTH/SCREEN_SCALE),
            static_cast<int>(SCREEN_HEIGHT/SCREEN_SCALE)
        };
        target = nullptr;

        maxY = Engine::getInstance()->getMap()->getMapLayers()[GameMap::foreground]->getHeight();
    }

    SDL_Rect viewBox;
    Point *target;
    Vector2D position;
    int maxY;


    static Camera* instance;
};

#endif // CAMERA_H
