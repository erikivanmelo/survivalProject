#ifndef CAMERA_H
#define CAMERA_H



#include <SDL2/SDL.h>
#include "../Core/Engine.h"
#include "../Physics/Point.h"
#include "../Physics/Vector2D.h"

struct Scala{
    float w = 1.5;
    float h = 1.5;
};

class Camera
{
public:
    inline static Camera *getInstance(){ return instance = (instance == nullptr)? new Camera() : instance; }
    ~Camera(){
        delete target;
    }

    inline SDL_Rect getViewBox(){return viewBox;}
    inline Vector2D getPosition(){return position;}
    inline void setTarget(Point *target){this->target = target;}
    inline Scala getScala(){return scala;}

    void update(float dt);

    inline void clear(){
        delete instance;
    }

private:
    Camera(){
        viewBox = {
            0,
            0,
            static_cast<int>(SCREEN_WIDTH/scala.w),
            static_cast<int>(SCREEN_HEIGHT/scala.h)
        };
    }

    SDL_Rect viewBox;
    Point *target;
    Vector2D position;

    Scala scala;

    static Camera* instance;
};

#endif // CAMERA_H
