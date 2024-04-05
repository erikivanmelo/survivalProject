#include "Character.h"
#include "../Core/Engine.h"

void Character::placeBlock(Vector2D position, Tile *tile){
    static GameMap *mapa = Engine::get()->getMap();

    if (!tile)
        tile = tileSelected;

    if (!tile || 
        (!mapa->areBlockAround(position.x, position.y, FOREGROUND) && !mapa->getTile(position.x, position.y, BACKGROUND)) || 
        mapa->getTile(position.x, position.y, FOREGROUND) ||
        CollisionHandler::get()->isCharacterIn(position.x, position.y, collider->getCollisionBox()) ||
        !isInteractionInRange(position)
        ) return;
    mapa->setTile(
        position.x,
        position.y,
        FOREGROUND,
        *tile
    );
}

void Character::breakBlock(Vector2D position){
    static GameMap *mapa = Engine::get()->getMap();
    if (!mapa->getTile(position.x, position.y, FOREGROUND) || !isInteractionInRange(position)) 
        return;
    mapa->dropTile(
        position.x,
        position.y,
        FOREGROUND 
    );
}

void Character::selectBlock(Vector2D position){
    static GameMap *mapa = Engine::get()->getMap();
    tileSelected = mapa->getTile(position.x, position.y, FOREGROUND);
    if(!tileSelected)
        tileSelected = mapa->getTile(position.x, position.y, BACKGROUND);
}

bool Character::isInteractionInRange(Vector2D position){
    const GameMap *gameMap = Engine::get()->getMap();
    int colCount = gameMap->getTileWidth();
    SDL_FRect *box = collider->getCollisionBox();
    
    const int leftTile    =  box->x / TILE_SIZE - interactionRange;
    const int rightTile   = (box->x + (box->w-1)) / TILE_SIZE + interactionRange;
    const int topTile     =  box->y / TILE_SIZE - interactionRange;
    const int bottomTile  = (box->y + (box->h-1)) / TILE_SIZE + interactionRange;

    if(rightTile > colCount && position.x < leftTile ) 
        position.x += colCount;
    
    return (leftTile <= position.x && rightTile  >= position.x && 
            topTile  <= position.y && bottomTile >= position.y);
}

void Character::jump(bool impulsing){
    if (impulsing && !flyMode){
        if( grounded && !jumping ){
            jumping = true;
            grounded = false;
            rigidBody->setVelocityY(DIRECTION_UP * jumpVelocity); 
        }
    } else if (this->jumping && this->rigidBody->getVelocity().y < 0) {
        this->rigidBody->unsetVelocityY();
        this->jumping = false;
    }
}

void Character::move(int8_t direction){
    if (flyMode)
        fly(direction);
    else if (direction == OPTION_RIGHT || direction == OPTION_LEFT)
        walk(direction == OPTION_RIGHT);

}

void Character::fly(int8_t direction) {

    switch (direction) {
        case OPTION_UP:
            rigidBody->applyMovementY( DIRECTION_UP * flySpeed );
        return;

        case OPTION_DOWN:
            rigidBody->applyMovementY( DIRECTION_DOWN * flySpeed );
        return;

        case OPTION_LEFT:
            rigidBody->applyMovementX(DIRECTION_LEFT * flySpeed);
            lookingRight = false;
            animation->setCurrentSeq("default", SDL_FLIP_HORIZONTAL);
        return;

        case OPTION_RIGHT:
            rigidBody->applyMovementX(DIRECTION_RIGHT * flySpeed);
            lookingRight = true;
            animation->setCurrentSeq("default");
        return;
    }
}

void Character::walk(bool toRight){
    rigidBody->applyMovementX( toRight ? walkSpeed : walkSpeed*-1 );
    animation->setCurrentSeq( "walk", toRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );
    lookingRight = toRight;
}

void Character::setFlyMode( bool flyMode ){
    this->flyMode = flyMode;
    rigidBody->setGravity( flyMode? 0 : GRAVITY );
}
