#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <SDL2/SDL_rect.h>

#define INPUT_RIGHT     Input::getInstance()->getKeyDown(SDL_SCANCODE_D)
#define INPUT_LEFT      Input::getInstance()->getKeyDown(SDL_SCANCODE_A)
#define INPUT_UP        Input::getInstance()->getKeyDown(SDL_SCANCODE_W)
#define INPUT_DOWN      Input::getInstance()->getKeyDown(SDL_SCANCODE_S)
#define INPUT_JUMP      Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE)
#define INPUT_FLYMODE   Input::getInstance()->getKeyPressed(SDL_SCANCODE_G)

class Player : public Character
{

public:
    Player( int x = 0, int y = 0 );

    void animationState();

    void checkInput( float dt );
    void update(float dt) override;

};

#endif // PLAYER_H
