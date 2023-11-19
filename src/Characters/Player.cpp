#include "Player.h"
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"
#include "../Physics/Collider.h"
#include "../Core/Engine.h"
#include "../Helper.h"

#include <SDL2/SDL_log.h>
#include <SDL2/SDL_mouse.h>
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
        int x = Input::getInstance()->getMouseX(),y = Input::getInstance()->getMouseY();
        mapa->displayToMapPosition(&x,&y);
        if( mouseState == SDL_BUTTON_RMASK ){
            Engine::getInstance()->getMap()->dropTile(
                x,
                y,
                FOREGROUND
            );
        }

        static Tile *tile = nullptr;
        if( mouseState == SDL_BUTTON_MIDDLE){
            tile = mapa->getTile(x,y,FOREGROUND);
            if(!tile)
                tile = mapa->getTile(x,y,BACKGROUND);
        }

        if(!tile)
            return;

        if( mouseState == SDL_BUTTON_LEFT ){
            Engine::getInstance()->getMap()->setTile(x,y,
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

