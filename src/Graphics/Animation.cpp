#include "Animation.h"
#include "TextureManager.h"
#include <SDL3/SDL_render.h>
#include <cstdint>

Animation::Animation( AnimationSeqList *list, Vector2D *position):
    flip(SDL_FLIP_NONE),
    seqList(list),
    currentSeq(list->at("default")),
    forceAnimSpeed(0),
    spriteFrame(0),
    position(position)
{}

Animation::~Animation()
{
    delete seqList;
}

void Animation::update(float dt)
{
    const uint8_t lastFrame = spriteFrame;
    //Si en un momento determinado se decide forzar la velocidad de la animacion, se usa "forceAnimSpeed"
    //Si no, se usa la velocidad de la animacion estandar
    const uint8_t animSpeed = forceAnimSpeed > 0 ? forceAnimSpeed : currentSeq->animSpeed;
    //Cada vez que pasen animSpeed frames se cambia el sprite de la animacion
    spriteFrame = (animSpeed == 0? 0 : ( SDL_GetTicks() / animSpeed ) % currentSeq->frameCount);
    if (lastFrame != spriteFrame)
        toRender = true;
}

void Animation::draw()
{
    TextureManager::drawFrame(
        currentSeq->texture,
        position->x, 
        position->y, 
        currentSeq->spriteWidth, 
        currentSeq->spriteHeight, 
        currentSeq->spriteRow, 
        spriteFrame, 
        flip
    );
    IObject::draw();
}

void Animation::setCurrentSeq( const string &seqId, SDL_RendererFlip flip, const uint8_t animSpeed )
{
    AnimationSeq *newSeq = seqList->at(seqId);
    this->spriteFrame = 0;
    this->flip = flip;
    this->forceAnimSpeed = animSpeed;
    if (newSeq != currentSeq)
        toRender = true;
    this->currentSeq = newSeq;
}

