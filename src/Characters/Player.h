#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
class Player : public Character
{

public:
    Player(Properties *props);

    ~Player();

    virtual void draw();
    virtual void update(float dt);

    void animationState();

    inline Transform *getTransform()const{return transform;}

private:
    int row, frame, frameCount;
    int animSpeed;

};

#endif // PLAYER_H
