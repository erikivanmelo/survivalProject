#include "Player.h"

Player::Player(Properties *props) : Character(props)
{
    AnimationSeqList *animationSeqs = new AnimationSeqList();
    animationSeqs->insert( "player_stand", new AnimationSeq("player_stand",1,1,0  ,width,height) );
    animationSeqs->insert( "player_walk",  new AnimationSeq("player_walk" ,1,4,150,width,height) );
    animation = new Animation(animationSeqs,"player_walk");
}

Player::~Player()
{
    Character::~Character();
}

void Player::draw()
{
    animation->draw( 100, 100 );
}

void Player::update( float dt ){
    animation->update();
}


