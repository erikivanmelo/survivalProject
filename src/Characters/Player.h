#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <SDL3/SDL_rect.h>

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
    Player( Vector2D posiiton = Vector2D(0,0) );

    void update(float dt) override;

    void draw()override;
private:
    void checkInput( float dt );


    Vector2D mousePosition;
    
};

#endif // PLAYER_H
