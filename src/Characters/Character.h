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
        animation(new Animation(
            AssetsManager::get()->getAnimationSeqMap(textureId), 
            &this->position
        )),
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
        collisionZone( COLLISION_ZONE_NONE )
    {}

    ~Character(){
        delete animation;
        delete rigidBody;
    }


    void draw()override{
        animation->draw();
        if( collisionBoxView )
            collider->draw();
        GameObject::draw();
    }


    void update( float dt )override{
        rigidBody->update(dt);

        this->position = CollisionHandler::get()->mostPlausiblePosition( 
            this->position, 
            this->position + rigidBody->getPosition(), 
            collider, 
            &collisionZone 
        );
        collider->setCoordinates(this->position);

        if( collisionZone & COLLISION_ZONE_LEFT || collisionZone & COLLISION_ZONE_RIGHT )
            rigidBody->unsetVelocityX();

        if( collisionZone & COLLISION_ZONE_BOTTOM || collisionZone & COLLISION_ZONE_TOP ){
            rigidBody->unsetVelocityY();
            jumping = false;
        }
        
        grounded = collisionZone & COLLISION_ZONE_BOTTOM;

        animation->update(dt);
        GameObject::update(dt);
        if (!moved)
            animation->setCurrentSeq( "default", lookingRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );
        if (animation->isToRender())
            toRender = true;
    }

    void walk(bool toRight);

    void fly(int8_t direction);

    void move(int8_t direction);

    void inline toggleFlyMode() {
        flyMode = !flyMode;
    }

    void inline setCollisionBoxView(bool val){
        collisionBoxView = val;
        toRender = true;
    }

    void inline toggleCollisionBoxView() {
        setCollisionBoxView(!collisionBoxView);
    }

    void jump(bool impulsing);
    void setFlyMode(bool flyMode);
    void placeBlock(Vector2D position, Tile *tile = nullptr);
    void breakBlock(Vector2D position);
    void selectBlock(Vector2D position);

    bool isInteractionInRange(Vector2D position);

protected:
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
