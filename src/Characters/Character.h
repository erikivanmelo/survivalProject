#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Object/GameObject.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"

class Character: public GameObject
{
public:
    Character(Properties *props, string name) : GameObject(props), name(name){
        rigidBody = new RigidBody();
        walkSpeed = 1;
    }
    ~Character(){
        delete animation;
        delete rigidBody;
        GameObject::~GameObject();
    }


    // IObject interface
public:

    void draw(){
        animation->draw( transform->x, transform->y );
    }

    void update( float dt ){
        rigidBody->update(dt);
        transform->translateX( rigidBody->getPosition().x );
        transform->translateY( rigidBody->getPosition().y );

        animation->update();
    }

    void walk(bool toRight){
        rigidBody->ApplyForceX( toRight ? walkSpeed : walkSpeed*-1 );
        animation->setCurrentSeq( name + "_walk", toRight? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL );
        lookingRight = toRight;
    }

protected:
    std::string name;
    Animation *animation;
    RigidBody *rigidBody;
    float walkSpeed;
    bool lookingRight;
};

#endif // CHARACTER_H
