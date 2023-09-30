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

Player::~Player()
{
    Character::~Character();
}

void Player::update( float dt ){
    animation->setCurrentSeq( "player_stand", lookingRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );
    rigidBody->unsetForce();


    if( Input::getInstance()->getKeyDown( SDL_SCANCODE_D ) ){
        if( this->god )
            walk(true);
        else
            fly( RIGHT );
    }else if( Input::getInstance()->getKeyDown( SDL_SCANCODE_A ) ){
        if( this->god )
            walk(false);
        else
            fly( LEFT );
    }else if( Input::getInstance()->getKeyDown( SDL_SCANCODE_W) && this->god ){
        fly( UP ); 
    }else if( Input::getInstance()->getKeyDown( SDL_SCANCODE_S) && this->god ){
        fly( DOWN ); 
    }else if( Input::getInstance()->getKeyDown( SDL_SCANCODE_G ) ){
        this->god = !this->god;
        if( this->god )
            rigidBody->setGravity(0);
        else
            rigidBody->setGravity(GRAVITY);
    }else if( Input::getInstance()->getKeyDown( SDL_SCANCODE_W ) ){
        
    }else{
        rigidBody->ApplyForceX(0);
    }

    //Actualiza el punto de visto del personaje al centro de la pantalla
    origin->x = transform->x + width/2;
    origin->y = transform->y + height/2;
    
    Camera::getInstance()->update( dt );
    Character::update( dt );
}
