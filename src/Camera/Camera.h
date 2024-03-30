#ifndef CAMERA_H
#define CAMERA_H

#include <SDL3/SDL.h>
#include "../Physics/Point.h"
#include "../Physics/Vector2D.h"

class Camera
{
public:
    inline static Camera *get(){ return instance; }
    inline static void destructor(){ delete instance; }
    inline static void constructor(Point *target, const float maxY, const float screenWidth, const float screenHeight, const float screenScale, const int chunkPixelSquareSize) {
        Camera::instance = new Camera(
            target, 
            maxY, 
            screenWidth, 
            screenHeight, 
            screenScale,
            chunkPixelSquareSize
        );
    }

    inline const SDL_FRect *getViewBox()const{return &viewBox;}
    inline const Vector2D *getPosition()const{return &position;}
    inline void setTarget(Point *target){this->target = target;}

    void setViewBoxSize(float screenWidth, float screenHeight, float screenScale = -1);
    void update();

private:
    Camera(Point *target, const float maxY, const float screenWidth, const float screenHeight, const float screenScale, const int chunkPixelSquareSize);


    Point *target;
    int maxY;
    float screenWidth, screenHeight, screenScale; 
    const int chunkPixelSquareSize;
    Vector2D position;
    SDL_FRect viewBox;


    static Camera* instance;
};

#endif // CAMERA_H
