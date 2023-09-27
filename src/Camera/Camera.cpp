#include "Camera.h"

#include "../Map/MapParser.h"

Camera *Camera::instance = nullptr;

void Camera::update(float dt)
{
    if(target != nullptr){

        viewBox.x = target->x - (int)(viewBox.w / 2);
        viewBox.y = target->y - (int)(viewBox.h / 2);

        if(viewBox.y < 0){
            viewBox.y = 0;
        }

        if(viewBox.y > viewBox.h/2){
            viewBox.y = viewBox.h/2;
        }

        position  = Vector2D(viewBox.x, viewBox.y);
    }
}
