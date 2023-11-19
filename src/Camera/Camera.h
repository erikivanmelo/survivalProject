#ifndef CAMERA_H
#define CAMERA_H



#include <SDL3/SDL.h>
#include "../Physics/Point.h"
#include "../Physics/Vector2D.h"

class Camera
{
public:
    inline static Camera *getInstance(){ return instance = (instance == nullptr)? new Camera() : instance; }
    inline static void clean(){ delete instance; }

    inline const SDL_FRect *getViewBox()const{return &viewBox;}
    inline const Vector2D *getPosition()const{return &position;}
    inline void setTarget(Point *target){this->target = target;}

    void setViewBoxSize(int width, int height);
    void update();

private:
    Camera();


    SDL_FRect viewBox;
    Point *target;
    Vector2D position;
    int maxY;


    static Camera* instance;
};

#endif // CAMERA_H
