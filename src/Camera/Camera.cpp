#include "Camera.h"

Camera *Camera::instance = nullptr;

void Camera::update(float dt)
{
    if(target != nullptr){

        viewBox.x = target->x - (int)(SCREEN_WIDTH / 2);
        viewBox.y = target->y - (int)(SCREEN_HEIGHT / 2);

        if(viewBox.y < 0){
            viewBox.y = 0;
        }

        if(viewBox.y > (maxY - viewBox.h) ){
            viewBox.y = (maxY - viewBox.h);
        }

        position  = Vector2D(viewBox.x, viewBox.y);
    }
}
