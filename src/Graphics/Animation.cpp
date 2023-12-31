#include "Animation.h"
#include "TextureManager.h"

Animation::Animation( AnimationSeqList *list ):
    seqList(list)
{
    currentSeq = list->at("default");
    forceAnimSpeed = -1;
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
    int animSpeed = forceAnimSpeed > -1 ? forceAnimSpeed : currentSeq->animSpeed;
    //Cada vez que pasen animSpeed frames se cambia el sprite de la animacion
    spriteFrame = animSpeed > 0 ? ( SDL_GetTicks() / animSpeed ) % currentSeq->frameCount : 0;
}

void Animation::draw( float x, float y )
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

void Animation::setCurrentSeq( const string &seqId, SDL_RendererFlip flip, int animSpeed )
{
    spriteFrame = 0;
    this->flip = flip;
    this->forceAnimSpeed = animSpeed;
    currentSeq = seqList->at(seqId);
}

