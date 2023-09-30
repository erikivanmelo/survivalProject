#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
class Player : public Character
{

public:
    Player( int x = 0, int y = 0 );

    ~Player();

    void animationState();

    void update(float dt) override;

    inline Transform *getTransform()const{return transform;}

    bool god = false;


};

#endif // PLAYER_H
