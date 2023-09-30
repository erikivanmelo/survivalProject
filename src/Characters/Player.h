#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <SDL2/SDL_rect.h>

#define INPUT_D Input::getInstance()->getKeyDown(SDL_SCANCODE_D)
#define INPUT_A Input::getInstance()->getKeyDown(SDL_SCANCODE_A)
#define INPUT_W Input::getInstance()->getKeyDown(SDL_SCANCODE_W)
#define INPUT_S Input::getInstance()->getKeyDown(SDL_SCANCODE_S)
#define INPUT_G Input::getInstance()->getKeyPressed(SDL_SCANCODE_G)

class Player : public Character
{

public:
    Player( int x = 0, int y = 0 );

    void animationState();

    void updateViewPoint();
    void checkInput();
    void update(float dt) override;

    inline Transform *getTransform()const{return transform;}

};

#endif // PLAYER_H
