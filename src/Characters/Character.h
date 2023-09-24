#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Object/GameObject.h"

class Character: public GameObject
{
public:
    Character(Properties *props) : GameObject(props){}


    // IObject interface
public:
    virtual void draw()=0;
    virtual void update( float dt )=0;

protected:
    std::string name;
};

#endif // CHARACTER_H
