#include "Collider.h"
#include "../Graphics/TextureManager.h"
void Collider::draw(){
    static const Vector2D *cam = Camera::get()->getPosition();
    SDL_FRect tmp = { box->x - (int)cam->x, box->y - (int)cam->y, box->w, box->h };
    SDL_SetRenderDrawColor(TextureManager::renderer,
                       255, 0, 0,255);
    SDL_RenderRect(TextureManager::renderer, &tmp);
}
