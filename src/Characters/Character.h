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
        interactionRange( 1 ),
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

    void walk(bool toRight);

    void fly( MoveOption direction );

    void setFlyMode(bool flyMode);
    void jump();
    void placeBlock(Vector2D position, Tile *tile = nullptr);
    void breakBlock(Vector2D position);
    void selectBlock(Vector2D position);

    bool isInteractionInRange(Vector2D position);

    Tile *tileSelected = nullptr;


    Animation *animation;
    RigidBody *rigidBody;
    
    float walkSpeed, flySpeed;
    bool jumping = false, grounded = false;
    bool flyMode = false;
    bool collisionBoxView = false;

    int interactionRange;

    float jumpVelocity;

    bool lookingRight = true;

    Collider *collider;


    int8_t collisionZone;
};

#endif // CHARACTER_H
