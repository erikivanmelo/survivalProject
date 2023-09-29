#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
class Player : public Character
{

public:
    Player(Properties *props);

    ~Player();

    void animationState();

    void update(float dt) override;

    inline Transform *getTransform()const{return transform;}

    bool flymode = false;

};

#endif // PLAYER_H
