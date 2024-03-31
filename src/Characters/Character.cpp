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
    GameMap *gameMap = Engine::get()->getMap();
    int tilesize = TILE_SIZE;
    int colCount = gameMap->getTileWidth();
    SDL_FRect *box = collider->getCollisionBox();
    
    const int leftTile    =  box->x / tilesize - interactionRange;
    const int rightTile   = (box->x + (box->w-1)) / tilesize + interactionRange;
    const int topTile     =  box->y / tilesize - interactionRange;
    const int bottomTile  = (box->y + (box->h-1)) / tilesize + interactionRange;

    if(rightTile > colCount && position.x < leftTile ) 
        position.x += colCount;
    
    return (leftTile <= position.x && rightTile  >= position.x && 
            topTile  <= position.y && bottomTile >= position.y);
}

void Character::jump(){
    if( grounded && !jumping ){
        jumping = true;
        grounded = false;
        rigidBody->setVelocityY(DIRECTION_UP * jumpVelocity); 
    }
}

void Character::fly(int8_t direction) {
    if( !flyMode )
        return;

    if (direction == OPTION_UP || direction == OPTION_DOWN)
        rigidBody->applyMovementY( direction * flySpeed );

    if (direction == OPTION_LEFT || direction == OPTION_RIGHT){
        rigidBody->applyMovementX(direction * flySpeed);
        lookingRight = direction == OPTION_RIGHT;
        animation->setCurrentSeq( "default", lookingRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
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
