#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <SDL3/SDL_rect.h>


class Player : public Character
{

public:
    Player( Vector2D position = Vector2D(0,0) );

    void update(float dt) override;

    void draw()override;
};

#endif // PLAYER_H
