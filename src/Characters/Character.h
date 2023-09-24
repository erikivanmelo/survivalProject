#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Object/GameObject.h"
#include "../Animation/Animation.h"

class Character: public GameObject
{
public:
    Character(Properties *props) : GameObject(props){}
    ~Character(){
        delete animation;
        GameObject::~GameObject();
    }


    // IObject interface
public:
    virtual void draw()=0;
    virtual void update( float dt )=0;

protected:
    std::string name;
    Animation *animation;
};

#endif // CHARACTER_H
