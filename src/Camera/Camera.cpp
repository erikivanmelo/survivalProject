#include "Camera.h"
#include <algorithm>

Camera *Camera::instance = nullptr;


void Camera::setViewBoxSize(float screenWidth, float screenHeight, float screenScale){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    if (screenScale != -1)
        this->screenScale = screenScale;
    viewBox.w = roundf(screenWidth/this->screenScale);
    viewBox.h = roundf(screenHeight/this->screenScale);
}

Camera::Camera(
    Point *target, 
    const float maxY, 
    const float screenWidth, 
    const float screenHeight, 
    const float screenScale, 
    const int chunkPixelSquareSize) : 
    target(target), 
    maxY(maxY), 
    screenWidth(screenWidth), 
    screenHeight(screenHeight), 
    screenScale(screenScale), 
    chunkPixelSquareSize(chunkPixelSquareSize), 
    position(Vector2D(0,0)),
    viewBox({
        0, 0,
        roundf(screenWidth/screenScale),
        roundf(screenHeight/screenScale)
    })
{}

void Camera::update()
{
    if( !target )
        return;
    position.x = viewBox.x = target->x - viewBox.w / 2;
    position.y = viewBox.y = std::clamp((int)(target->y - viewBox.h / 2), 0, (int)(maxY - viewBox.h - chunkPixelSquareSize));
}
