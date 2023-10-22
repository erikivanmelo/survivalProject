#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Object/GameObject.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"
#include "../Collision/CollisionHandler.h"
#include <cstdint>

class Character: public GameObject
{
public:
    Character(Properties *props, const string &name) : 
        GameObject(props), 
        name(name), 
        collisionZone(CollisionZone::none)
    {
        animation = nullptr;
        collider = new Collider();
        rigidBody = new RigidBody();

        jumpForce = 30.0;
        jumpTime = 0.20;
        jumpTimer = jumpTime;
        walkSpeed = 8;
        flySpeed = 16;
    }

    ~Character(){
        delete animation;
        delete rigidBody;
    }


    void draw()override{
        animation->draw( position.x, position.y );
        collider->draw();
    }


    void update( float dt )override{
        

        checkCollision( dt );

        animation->update();
        collider->draw();
        GameObject::update( dt );
    }


protected:

    void walk(bool toRight){
        rigidBody->ApplyForceX( toRight ? walkSpeed : walkSpeed*-1 );
        animation->setCurrentSeq( name + "_walk", toRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );
        lookingRight = toRight;
    }

    void fly( MoveOption direction ){
        if( !flyMode )
            return;

        switch (direction) {
            case UP:
                rigidBody->ApplyForceY( MoveDirection::UP * flySpeed );
                break;
            case DOWN:
                rigidBody->ApplyForceY( MoveDirection::DOWN * flySpeed );
                break;
            case LEFT:
                rigidBody->ApplyForceX( MoveDirection::LEFT * flySpeed );
                animation->setCurrentSeq( name + "_stand", SDL_FLIP_HORIZONTAL );
                lookingRight = false;
                break;
            case RIGHT:
                rigidBody->ApplyForceX( MoveDirection::RIGHT * flySpeed );
                animation->setCurrentSeq( name + "_stand", SDL_FLIP_NONE );
                lookingRight = true;
                break;
        }
    }

    void setFlyMode( bool flyMode ){
        this->flyMode = flyMode;
        rigidBody->setGravity( flyMode? 0 : GRAVITY );
    }

    void jump(){
        if( grounded ){
            jumping = true;
            rigidBody->ApplyForceY( MoveDirection::UP * jumpForce ); 
        }

    }

    void checkCollision(float dt){
        rigidBody->update( dt );
        Vector2D lastSafePosition = position;
        Vector2D trajectory = rigidBody->getPosition();

        position += trajectory;

        collider->setCoordenates(position);

        if( (collisionZone = CollisionHandler::getInstance()->mapCollision(collider->getCollisionBox())) )
            position = CollisionHandler::getInstance()->mostPlausibleMove( lastSafePosition, position, collider, &collisionZone );
        collider->setCoordenates(position);

        grounded = collisionZone & CollisionZone::bottom;
        if( collisionZone & CollisionZone::top ){
           jumping = false; 
        }
    }

    std::string name;
    Animation *animation;
    RigidBody *rigidBody;
    
    float walkSpeed, flySpeed;
    bool jumping = false, grounded = false;
    bool flyMode = false;

    float jumpTime;
    float jumpTimer;
    float jumpForce;

    bool lookingRight = true;

    Collider *collider;


    int8_t collisionZone;
};

#endif // CHARACTER_H
