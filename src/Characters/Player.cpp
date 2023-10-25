#include "Player.h"
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"
#include "../Physics/Collider.h"
#include "../Assets/AssetsManager.h"

#include <SDL2/SDL_log.h>
#include <algorithm>

Player::Player( int x, int y ) : Character(new Properties( "player", x, y, 32, 32 ),"player")
{

    //Posicion de la colission box
    collider->setBuffer(-10,-2,0,0);
    //Tamaño de la colission box
    collider->setCollisionBox(12,28);

    animation = new Animation( AssetsManager::getInstance()->getAnimationSeqMap( "player" ), "stand" );



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

    if( INPUT_JUMP && grounded ){
        jumping = true;
        grounded = false;
        rigidBody->ApplyForceY( MoveDirection::UP * jumpForce ); 
    }
        if( INPUT_JUMP && jumping && jumpTimer > 0 ){
            jumpTimer -= dt;
            rigidBody->ApplyForceY( MoveDirection::UP * jumpForce ); 
        }else{
            jumping = false;
            jumpTimer = jumpTime;
        }
    //}
}

void Player::update( float dt ){
    animation->setCurrentSeq( "stand", lookingRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );
    rigidBody->unsetForce();

    checkInput( dt );
    Character::update( dt );

    Camera::getInstance()->update();
}

