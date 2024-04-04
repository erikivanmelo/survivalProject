#include "GameObject.h"
#include "../Core/Engine.h"

void GameObject::update(float dt){
    static const float widthMap = Engine::get()->getMap()->getPixelWidth();
    if (!(moved = position != lastPosition))
        return;

    if (position.x > widthMap) 
        position.x = fmod(position.x, widthMap);
    else if (position.x < 0)
        position.x = widthMap + fmod(position.x, widthMap);

    updateViewPoint();
    lastPosition = position;
}
