#include "Animation.h"
#include "../Graphics/TextureManager.h"

Animation::Animation( AnimationSeqList *list, string defaultSeq ):
    seqList(list)
{
    currentSeq = list->at(defaultSeq);
    forceAnimSpeed = -1;
    flip = SDL_FLIP_NONE;
}

Animation::~Animation()
{
    delete seqList;
}

void Animation::update()
{
    //Si en un momento determinado se decide forzar la velocidad de la animacion, se usa "forceAnimSpeed"
    //Si no, se usa la velocidad de la animacion estandar
    int animSpeed = forceAnimSpeed > -1 ? forceAnimSpeed : currentSeq->animSpeed;
    //Cada vez que pasen animSpeed frames se cambia el sprite de la animacion
    spriteFrame = animSpeed > 0 ? ( SDL_GetTicks() / animSpeed ) % currentSeq->frameCount : 0;
}

void Animation::draw( float x, float y )
{
    TextureManager::getInstance()->drawFrame(
        currentSeq->textureId,
        x, 
        y, 
        currentSeq->spriteWidth, 
        currentSeq->spriteHeight, 
        currentSeq->spriteRow, 
        spriteFrame, 
        flip
    );
}

void Animation::setCurrentSeq( string seqId, SDL_RendererFlip flip, int animSpeed )
{
    spriteFrame = 0;
    this->flip = flip;
    this->forceAnimSpeed = animSpeed;
    currentSeq = seqList->at(seqId);
}

