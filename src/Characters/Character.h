#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Object/GameObject.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"

class Character: public GameObject
{
public:
    Character(Properties *props, const string &name) : GameObject(props), name(name){
        animation = nullptr;
        rigidBody = new RigidBody();
        walkSpeed = 1;
        flySpeed = 2;
    }
    ~Character(){
        delete animation;
        delete rigidBody;
        GameObject::~GameObject();
    }
    enum MoveDirection{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };


    void draw(){
        animation->draw( transform->x, transform->y );
    }

    void update( float dt ){
        rigidBody->update(dt);
        transform->translateX( rigidBody->getPosition().x );
        transform->translateY( rigidBody->getPosition().y );

        animation->update();
    }


protected:

    void walk(bool toRight){
        rigidBody->ApplyForceX( toRight ? walkSpeed : walkSpeed*-1 );
        animation->setCurrentSeq( name + "_walk", toRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );
        lookingRight = toRight;
    }

    void fly( MoveDirection direction ){
        switch (direction) {
            case UP:
                rigidBody->ApplyForceY( flySpeed*-1 );
                break;
            case DOWN:
                rigidBody->ApplyForceY( flySpeed );
                break;
            case LEFT:
                rigidBody->ApplyForceX( flySpeed*-1 );
                break;
            case RIGHT:
                rigidBody->ApplyForceX( flySpeed );
                break;
        }
    }


    std::string name;
    Animation *animation;
    RigidBody *rigidBody;
    float walkSpeed;
    float flySpeed;
    bool lookingRight = true;
};

#endif // CHARACTER_H
