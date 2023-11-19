#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <SDL2/SDL_rect.h>

#define INPUT_RIGHT             Input::getInstance()->getKeyDown(SDL_SCANCODE_D)
#define INPUT_LEFT              Input::getInstance()->getKeyDown(SDL_SCANCODE_A)
#define INPUT_UP                Input::getInstance()->getKeyDown(SDL_SCANCODE_W)
#define INPUT_DOWN              Input::getInstance()->getKeyDown(SDL_SCANCODE_S)
#define INPUT_JUMP              Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE)
#define INPUT_FLYMODE           Input::getInstance()->getKeyPressed(SDL_SCANCODE_G)
#define INPUT_COLLISIONBOXVIEW  Input::getInstance()->getKeyPressed(SDL_SCANCODE_F1)

class Player : public Character
{

public:
    Player( Vector2D posiiton );

    void update(float dt) override;

private:
    void checkInput( float dt );

    Tile tileSelected;
};

#endif // PLAYER_H
