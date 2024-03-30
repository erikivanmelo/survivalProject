#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <SDL3/SDL_rect.h>

#define INPUT_RIGHT             Input::get()->getKeyDown(SDL_SCANCODE_D)
#define INPUT_LEFT              Input::get()->getKeyDown(SDL_SCANCODE_A)
#define INPUT_UP                Input::get()->getKeyDown(SDL_SCANCODE_W)
#define INPUT_DOWN              Input::get()->getKeyDown(SDL_SCANCODE_S)
#define INPUT_JUMP              Input::get()->getKeyDown(SDL_SCANCODE_SPACE)
#define INPUT_FLYMODE           Input::get()->getKeyPressed(SDL_SCANCODE_G)
#define INPUT_COLLISIONBOXVIEW  Input::get()->getKeyPressed(SDL_SCANCODE_F1)

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
