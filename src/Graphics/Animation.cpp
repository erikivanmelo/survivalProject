#include "Animation.h"
#include "TextureManager.h"

Animation::Animation( AnimationSeqList *list ):
    seqList(list)
{
    currentSeq = list->at("default");
    forceAnimSpeed = 0;
    flip = SDL_FLIP_NONE;
    spriteFrame = 0;
}

Animation::~Animation()
{
    delete seqList;
}

void Animation::update()
{
    //Si en un momento determinado se decide forzar la velocidad de la animacion, se usa "forceAnimSpeed"
    //Si no, se usa la velocidad de la animacion estandar
    const uint8_t animSpeed = forceAnimSpeed > 0 ? forceAnimSpeed : currentSeq->animSpeed;
    //Cada vez que pasen animSpeed frames se cambia el sprite de la animacion
    spriteFrame = animSpeed > 0 ? ( SDL_GetTicks() / animSpeed ) % currentSeq->frameCount : 0;
}

void Animation::draw(const float x, const float y)
{
    TextureManager::drawFrame(
        currentSeq->texture,
        x, 
        y, 
        currentSeq->spriteWidth, 
        currentSeq->spriteHeight, 
        currentSeq->spriteRow, 
        spriteFrame, 
        flip
    );
}

void Animation::setCurrentSeq( const string &seqId, SDL_RendererFlip flip, const uint8_t animSpeed )
{
    spriteFrame = 0;
    this->flip = flip;
    this->forceAnimSpeed = animSpeed;
    currentSeq = seqList->at(seqId);
}

