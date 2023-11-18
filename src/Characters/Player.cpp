#include "Player.h"
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"
#include "../Physics/Collider.h"
#include "../Core/Engine.h"
#include "../Helper.h"

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
    static const Camera *cam  = Camera::getInstance();
    static const GameMap *mapa = Engine::getInstance()->getMap();

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

    if( Input::getInstance()->getMouseState() == SDL_BUTTON_LEFT ){
        int mouseX = Input::getInstance()->getMouseX(), mouseY = Input::getInstance()->getMouseY();
        int x = Helper::wrapToRange((int)cam->getPosition()->x+(mouseX/SCREEN_SCALE),mapa->getPixelWidth()) /8;
        int y = std::clamp((int)cam->getPosition()->y+(mouseY/SCREEN_SCALE),0,mapa->getPixelHeight()-1)/8;
       
        cout << "mapa:" << x << " - " << y << endl;


        Engine::getInstance()->getMap()->setTile(
                x,
                y,
                FOREGROUND,
                1
                );
    }


    if( INPUT_COLLISIONBOXVIEW )
        this->collisionBoxView = !this->collisionBoxView;

    if( INPUT_JUMP ){
        jump();
    } else if ( this->rigidBody->getVelocity().y < 0 && this->jumping) {
        this->rigidBody->unsetVelocityY();
        this->jumping = false;
    }
}

void Player::update( float dt ){
    animation->setCurrentSeq( "default", lookingRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );

    checkInput( dt );
    Character::update( dt );

    Camera::getInstance()->update();
}

