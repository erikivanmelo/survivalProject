#include "Camera.h"
#include "../Core/Engine.h"

Camera *Camera::instance = nullptr;


void Camera::setViewBoxSize(int width, int height){
   viewBox.w = static_cast<int>(width/SCREEN_SCALE);
   viewBox.h = static_cast<int>(height/SCREEN_SCALE);
}

Camera::Camera(){
    viewBox = {
        0,
        0,
        static_cast<int>(SCREEN_WIDTH/SCREEN_SCALE),
        static_cast<int>(SCREEN_HEIGHT/SCREEN_SCALE)
    };
    target = nullptr;
    position = Vector2D(0,0);

    maxY = Engine::getInstance()->getMap()->getPixelHeight();
}

void Camera::update()
{
    if(target != nullptr){

        viewBox.x = target->x - (int)(viewBox.w / 2);
        viewBox.y = target->y - (int)(viewBox.h / 2);

        if(viewBox.y < 0){
            viewBox.y = 0;
        }

        if(viewBox.y > (maxY - viewBox.h) ){
            viewBox.y = (maxY - viewBox.h);
        }

        position.x = viewBox.x;
        position.y = viewBox.y;

    }
}
