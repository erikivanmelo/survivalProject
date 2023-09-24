#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Object/GameObject.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"

class Character: public GameObject
{
public:
    Character(Properties *props) : GameObject(props){
        rigidBody = new RigidBody();
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
        rigidBody->update(0.4);
        transform->translateX( rigidBody->getPosition().x );
        transform->translateY( rigidBody->getPosition().y );

        animation->update();
    }

protected:
    std::string name;
    Animation *animation;
    RigidBody *rigidBody;
};

#endif // CHARACTER_H
