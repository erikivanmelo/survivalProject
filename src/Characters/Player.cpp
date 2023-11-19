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
}


void Player::checkInput( float dt ){
    static GameMap *mapa = Engine::getInstance()->getMap();
    const MouseState mouseState = Input::getInstance()->getMouseState();



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


    if( mouseState ){
        Vector2D position = Input::getInstance()->getMousePosition();
        mapa->displayToMapPosition(&position);
        if( mouseState == SDL_BUTTON_RMASK ){
            Engine::getInstance()->getMap()->dropTile(
                position.x,
                position.y,
                FOREGROUND
            );
        }

        static Tile *tile = nullptr;
        if( mouseState == SDL_BUTTON_MIDDLE){
            tile = mapa->getTile(position.x,position.y,FOREGROUND);
            if(!tile)
                tile = mapa->getTile(position.x,position.y,BACKGROUND);
        }

        if(!tile)
            return;

        if( mouseState == SDL_BUTTON_LEFT ){
            Engine::getInstance()->getMap()->setTile(
                position.x,
                position.y,
                FOREGROUND,
                *tile
            );
        }
    }
}

void Player::update( float dt ){
    animation->setCurrentSeq( "default", lookingRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );

    checkInput( dt );
    Character::update( dt );

    Camera::getInstance()->update();
}

