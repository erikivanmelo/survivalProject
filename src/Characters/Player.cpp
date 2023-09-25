#include "Player.h"
#include "../Inputs/Input.h"

Player::Player(Properties *props) : Character(props,"player")
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

    if( Input::getInstance()->getKeyDown( SDL_SCANCODE_S ) )
        walk(true);
    else if( Input::getInstance()->getKeyDown( SDL_SCANCODE_A ) )
        walk(false);
    else{
        rigidBody->ApplyForceX(0);
    }

    Character::update( dt );
    rigidBody->getPosition().log();
}
