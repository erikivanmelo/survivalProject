#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Object/GameObject.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"
#include "../Collision/CollisionHandler.h"
#include <cstdint>

#define JUMP_TIME 20.0f
#define JUMP_FORCE 5.0f

class Character: public GameObject
{
public:
    Character(Properties *props, const string &name) : GameObject(props), name(name){
        animation = nullptr;
        rigidBody = new RigidBody();
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

    void checkCollision(float dt){
        rigidBody->update( dt );
        Vector2D lastSafePosition = position;
        Vector2D trajectory = rigidBody->getPosition();

        position += trajectory;

        collider->setCoordenates(position);
        int8_t collisionZone = 0;

        if( (collisionZone = CollisionHandler::getInstance()->mapCollision(collider->getCollisionBox())) )
            position = CollisionHandler::getInstance()->mostPlausibleMove( lastSafePosition, position, collider, &collisionZone );
        collider->setCoordenates(position);
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
        walking = true;
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
        flying = true;
    }


    std::string name;
    Animation *animation;
    RigidBody *rigidBody;
    
    float walkSpeed, flySpeed;
    bool walking = false, flying = false, jumping = false, grounded = false;
    bool flyMode = false;

    float jumpTime;
    float jumpForce;

    bool lookingRight = true;

    Collider *collider;


    int collisionZone;
};

#endif // CHARACTER_H
