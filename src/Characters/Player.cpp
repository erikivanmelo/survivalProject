#include "Player.h"
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"
#include "../Physics/Collider.h"

#include <SDL2/SDL_log.h>
#include <algorithm>

Player::Player( Vector2D position ) : Character( "player", position, 32, 32 )
{
    //Posicion de la colission box
    collider->setBuffer(-10,-2,0,0);
    //Tamaño de la colission box
    collider->setCollisionBox(12,28);
}


void Player::checkInput( float dt ){
    if( INPUT_RIGHT )
        this->flyMode? fly( RIGHT ) : walk(true);

    if( INPUT_LEFT )
        this->flyMode? fly( LEFT ) : walk(false);

    if( INPUT_UP && this->flyMode )
        fly( UP );

    if( INPUT_DOWN && this->flyMode )
        fly( DOWN ); 

    if( INPUT_FLYMODE )
        setFlyMode( !this->flyMode );

    if( INPUT_COLLISIONBOXVIEW )
        this->collisionBoxView = !this->collisionBoxView;

    if( INPUT_JUMP ){
        jump();
    }
}

void Player::update( float dt ){
    animation->setCurrentSeq( "default", lookingRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );

    checkInput( dt );
    Character::update( dt );

    Camera::getInstance()->update();
}

