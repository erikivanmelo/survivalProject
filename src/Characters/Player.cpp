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


    this->mousePosition = Input::getInstance()->getMousePosition();
    mapa->displayPositionToMapPosition(&mousePosition);
    if( mouseState ){
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
}

void Player::placeBlock(Vector2D position, Tile *tile){
    static GameMap *mapa = Engine::getInstance()->getMap();

    if (!tile)
        tile = tileSelected;

    if (!tile || 
        (!mapa->areBlockAround(position.x, position.y, FOREGROUND) && !mapa->getTile(position.x, position.y, BACKGROUND)) || 
        mapa->getTile(position.x, position.y, FOREGROUND) ||
        CollisionHandler::getInstance()->isCharacterIn(position.x, position.y, collider->getCollisionBox())
        ) return;
    mapa->setTile(
        position.x,
        position.y,
        FOREGROUND,
        *tile
    );
}

void Player::breakBlock(Vector2D position){
    static GameMap *mapa = Engine::getInstance()->getMap();
    mapa->dropTile(
        position.x,
        position.y,
        FOREGROUND 
    );
}

void Player::selectBlock(Vector2D position){
    static GameMap *mapa = Engine::getInstance()->getMap();
    tileSelected = mapa->getTile(mousePosition.x,mousePosition.y,FOREGROUND);
    if(!tileSelected)
        tileSelected = mapa->getTile(mousePosition.x,mousePosition.y,BACKGROUND);
}

void Player::update( float dt ){
    animation->setCurrentSeq( "default", lookingRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );

    checkInput( dt );
    Character::update( dt );

    Camera::getInstance()->update();
}

void Player::draw(){
    static GameMap *mapa = Engine::getInstance()->getMap();
    Character::draw();
    mapa->focusBlock(mousePosition);
}
