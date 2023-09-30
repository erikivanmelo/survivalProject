#include "Player.h"
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"

Player::Player( int x, int y ) : Character(new Properties( "player_walk", x, y, 32, 32 ),"player")
{
    AnimationSeqList *animationSeqs = new AnimationSeqList();
    animationSeqs->insert( "player_stand", new AnimationSeq("player_walk" ,1,1,0,width,height) );
    animationSeqs->insert( "player_walk",  new AnimationSeq("player_walk" ,1,4,150,width,height) );
    animation = new Animation(animationSeqs,"player_stand");
    rigidBody->setMass( 44 );
}

void Player::updateViewPoint(){
    origin->x = transform->x + (int)(width/2);
    origin->y = transform->y + (int)(height/2);
}

void Player::checkInput(){
    if( INPUT_D )
        this->flyMode? fly( RIGHT ) : walk(true);

    if( INPUT_A )
        this->flyMode? fly( LEFT ) : walk(false);

    if( INPUT_W && this->flyMode )
        fly( UP );

    if( INPUT_S && this->flyMode )
        fly( DOWN ); 

    if( INPUT_G )
        rigidBody->setGravity( (this->flyMode = !this->flyMode)? 0 : GRAVITY );
}

void Player::update( float dt ){
    animation->setCurrentSeq( "player_stand", lookingRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );
    rigidBody->unsetForce();

    checkInput();
    Character::update( dt );

    updateViewPoint();
    Camera::getInstance()->update();
}


