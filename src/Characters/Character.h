#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Object/GameObject.h"
#include "../Graphics/Animation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"
#include "../Physics/CollisionHandler.h"
#include <cmath>
#include <cstdint>

class Character: public GameObject
{
public:
    Character( const string &textureId, Vector2D position, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE ) : 
        GameObject( textureId, position, width, height, flip ),
        animation( new Animation( AssetsManager::getInstance()->getAnimationSeqMap( textureId ) ) ),
        rigidBody( new RigidBody() ),
        walkSpeed( 8 ),
        flySpeed( 16 ),
        jumping( false ),
        grounded( false ),
        flyMode( false ),
        collisionBoxView( false ),
        jumpVelocity( 30.0 ),
        lookingRight( true ),
        collider( new Collider() ),
        collisionZone( CollisionZone::none )
    {}

    ~Character(){
        delete animation;
        delete rigidBody;
    }


    void draw()override{
        animation->draw( position.x, position.y );
        if( collisionBoxView )
            collider->draw();
    }


    void update( float dt )override{
        rigidBody->update(dt);

        this->position = CollisionHandler::getInstance()->mostPlausiblePosition( 
            this->position, 
            this->position + rigidBody->getPosition(), 
            collider, 
            &collisionZone 
        );
        collider->setCoordinates(this->position);

        if( collisionZone & CollisionZone::left || collisionZone & CollisionZone::right )
            rigidBody->unsetVelocityX();

        if( collisionZone & CollisionZone::bottom || collisionZone & CollisionZone::top ){
            rigidBody->unsetVelocityY();
            jumping = false;
        }
        
        grounded = collisionZone & CollisionZone::bottom;

        animation->update();
        GameObject::update( dt );
    }


protected:

    void walk(bool toRight){
        rigidBody->applyMovementX( toRight ? walkSpeed : walkSpeed*-1 );
        animation->setCurrentSeq( "walk", toRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );
        lookingRight = toRight;
    }

    void fly( MoveOption direction ){
        if( !flyMode )
            return;

        switch (direction) {
            case UP:
                rigidBody->applyMovementY( MoveDirection::UP * flySpeed );
                break;
            case DOWN:
                rigidBody->applyMovementY( MoveDirection::DOWN * flySpeed );
                break;
            case LEFT:
                rigidBody->applyMovementX( MoveDirection::LEFT * flySpeed );
                animation->setCurrentSeq( "default", SDL_FLIP_HORIZONTAL );
                lookingRight = false;
                break;
            case RIGHT:
                rigidBody->applyMovementX( MoveDirection::RIGHT * flySpeed );
                animation->setCurrentSeq( "default" );
                lookingRight = true;
                break;
        }
    }

    void setFlyMode( bool flyMode ){
        this->flyMode = flyMode;
        rigidBody->setGravity( flyMode? 0 : GRAVITY );
    }

    void jump(){
        if( grounded && !jumping ){
            jumping = true;
            grounded = false;
            rigidBody->setVelocityY( MoveDirection::UP * jumpVelocity ); 
        }
    }

    Animation *animation;
    RigidBody *rigidBody;
    
    float walkSpeed, flySpeed;
    bool jumping = false, grounded = false;
    bool flyMode = false;
    bool collisionBoxView = false;

    float jumpVelocity;

    bool lookingRight = true;

    Collider *collider;


    int8_t collisionZone;
};

#endif // CHARACTER_H
