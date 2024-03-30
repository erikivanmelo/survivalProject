#include "Player.h"
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"
#include "../Physics/Collider.h"
#include "../Core/Engine.h"
#include "../Helper.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include <algorithm>

Player::Player( Vector2D position ) : Character( "player", position, 32, 32 )
{
    //Posicion de la colission box
    collider->setBuffer(-10,-2,0,0);
    //Tamaño de la colission box
    collider->setCollisionBox(12,28);
    //Rango de interaccion con los bloques
    interactionRange = 4;
}



void Player::checkInput( float dt ){
    static GameMap *mapa = Engine::get()->getMap();
    const MouseState mouseState = Input::get()->getMouseState();



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
    } else if ( this->rigidBody->getVelocity().y < 0 && this->jumping) {
        this->rigidBody->unsetVelocityY();
        this->jumping = false;
    }


    this->mousePosition = Input::get()->getMousePosition();
    mapa->displayPositionToMapPosition(&mousePosition);
    switch (mouseState) {
        case SDL_BUTTON_LEFT:
            placeBlock(mousePosition);
            break;
        case SDL_BUTTON_MIDDLE:
            selectBlock(mousePosition);
            break;
        case SDL_BUTTON_RMASK:
            breakBlock(mousePosition);
            break;
    }
}


void Player::update( float dt ){
    animation->setCurrentSeq( "default", lookingRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );

    checkInput( dt );
    Character::update( dt );

    Camera::get()->update();
}

void Player::draw(){
    static GameMap *mapa = Engine::get()->getMap();
    Character::draw();
    mapa->focusBlock(mousePosition, isInteractionInRange(mousePosition)? SDL_Color{0, 255, 0,255} : SDL_Color{255, 0, 0,255});
}
