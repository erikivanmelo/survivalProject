#include "Player.h"

Player::Player( Vector2D position ) : Character( "player", position, 32, 32 )
{
    //Posicion de la colission box
    collider->setBuffer(-10,-2,0,0);
    //Tamaño de la colission box
    collider->setCollisionBox(12,28);
    //Rango de interaccion con los bloques
    interactionRange = 4;
}

void Player::update( float dt ){
    Character::update( dt );
}

void Player::draw(){
    Character::draw();
}
