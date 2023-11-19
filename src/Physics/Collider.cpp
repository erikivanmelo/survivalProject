#include "Collider.h"
#include "../Core/Engine.h"
void Collider::draw(){
    static const Vector2D *cam = Camera::getInstance()->getPosition();
    SDL_FRect tmp = { box->x - (int)cam->x, box->y - (int)cam->y, box->w, box->h };
    SDL_SetRenderDrawColor(Engine::getInstance()->getRenderer(),
                       255, 0, 0,255);
    SDL_RenderRect(Engine::getInstance()->getRenderer(), &tmp);
}
