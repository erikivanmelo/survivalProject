#include "Camera.h"
#include "../Core/Engine.h"
#include <algorithm>

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
    if( !target )
        return;
    position.x = viewBox.x = target->x - viewBox.w / 2;
    position.y = viewBox.y = std::clamp((int)(target->y - viewBox.h / 2), 0, (int)(maxY - viewBox.h ));
}
