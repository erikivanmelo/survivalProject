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
    inline static void constructor(Point *target, const float maxY) {
        Camera::instance = new Camera(target, maxY);
    }

    inline void debug(){
        position.log("Camera Position"); 
    }
    inline const SDL_FRect *getViewBox()const{return &viewBox;}
    inline const Vector2D *getPosition()const{return &position;}
    inline float getScreenScale()const{return screenScale;}
    inline void setTarget(Point *target){this->target = target;}
    inline bool isViewBoxChanged()const{return viewBoxChanged;}
    inline void unsetViewBoxChanged(){viewBoxChanged = false;}

    void setViewBoxSize(float screenWidth, float screenHeight, float screenScale = -1);

    void update();

private:
    Camera(Point *target, const float maxY);


    Point *target;
    int maxY;
    float screenWidth, screenHeight, screenScale; 
    Vector2D position;
    SDL_FRect viewBox;
    bool viewBoxChanged;

    static Camera* instance;
};

#endif // CAMERA_H
