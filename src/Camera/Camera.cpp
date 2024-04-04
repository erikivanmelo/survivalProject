#include "Camera.h"
#include <algorithm>
#include "../Helper.h"

Camera *Camera::instance = nullptr;


void Camera::setViewBoxSize(float screenWidth, float screenHeight, float screenScale){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    if (screenScale != -1)
        this->screenScale = screenScale;
    viewBox.w = roundf(screenWidth/this->screenScale);
    viewBox.h = roundf(screenHeight/this->screenScale);
    viewBoxChanged = true;
}

Camera::Camera(
    Point *target, 
    const float maxY) : 
    target(target), 
    maxY(maxY), 
    screenWidth(DEFAULT_SCREEN_WIDTH), 
    screenHeight(DEFAULT_SCREEN_HEIGHT), 
    screenScale(DEFAULT_SCREEN_SCALE), 
    position(Vector2D(0,0)),
    viewBox({
        0, 0,
        (float) DEFAULT_SCREEN_WIDTH  / DEFAULT_SCREEN_SCALE,
        (float) DEFAULT_SCREEN_HEIGHT / DEFAULT_SCREEN_SCALE
    }),
    viewBoxChanged(false)
{}

void Camera::update()
{
    viewBoxChanged = false;
    if( !target )
        return;
    position.x = viewBox.x = target->x - viewBox.w / 2;
    position.y = viewBox.y = std::clamp((int)(target->y - viewBox.h / 2), 0, (int)(maxY - viewBox.h - CHUNK_PIXEL_SQUARE_SIZE));
}
