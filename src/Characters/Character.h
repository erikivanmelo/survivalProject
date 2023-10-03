#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Object/GameObject.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"
#include "../Collision/CollisionHandler.h"

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
        animation->draw( transform->x, transform->y );
    }

    void checkCollision(float dt){
        
        rigidBody->update( dt );
        lastSafePosition.x = transform->x;
        transform->x += rigidBody->getPosition().x;
        collider->setCoordenates(transform->x, transform->y);

        if(CollisionHandler::getInstance()->mapCollision(collider->getCollisionBox()))
            transform->x = lastSafePosition.x;

        rigidBody->update( dt );
        lastSafePosition.y = transform->y;
        transform->y += rigidBody->getPosition().y;
        collider->setCoordenates(transform->x, transform->y);

        if(CollisionHandler::getInstance()->mapCollision(collider->getCollisionBox())){
            grounded = true;
            transform->y = lastSafePosition.y;
        }else{
            grounded = false;
        }
    }


    void update( float dt )override{
        checkCollision( dt );

        animation->update();
        collider->draw();
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

    Vector2D lastSafePosition;

    int collisionZone;
};

#endif // CHARACTER_H
