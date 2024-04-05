#include "CurrentPlayer.h"

#include "../Inputs/Input.h"
#include "../Core/Engine.h"
#include <SDL3/SDL_mouse.h>

CurrentPlayer *CurrentPlayer::instance = nullptr;

void CurrentPlayer::debug() {
    position.log("Player Position");
}

void CurrentPlayer::draw() {
    Player::draw();
}

void CurrentPlayer::input() {
    static GameMap *mapa = Engine::get()->getMap();
    static const MouseState *mouseState = Input::get()->getMouseState();

    if (Input::get()->getKeyDown(SDL_SCANCODE_D))
        move(OPTION_RIGHT);

    if (Input::get()->getKeyDown(SDL_SCANCODE_A))
        move(OPTION_LEFT);

    if (Input::get()->getKeyDown(SDL_SCANCODE_W))
        move(OPTION_UP);

    if(Input::get()->getKeyDown(SDL_SCANCODE_S))
        move(OPTION_DOWN);

    if(Input::get()->getKeyPressed(SDL_SCANCODE_G))
        toggleFlyMode();

    if (Input::get()->getKeyPressed(SDL_SCANCODE_F1))
        toggleCollisionBoxView();

    jump(Input::get()->getKeyDown(SDL_SCANCODE_SPACE));


    this->mousePosition = Input::get()->getMousePosition();
    mapa->displayPositionToMapPosition(&mousePosition);
    switch (*mouseState) {
        case SDL_BUTTON_LEFT:
            placeBlock(mousePosition);
            break;
        case SDL_BUTTON_MIDDLE:
            selectBlock(mousePosition);
            break;
        case SDL_BUTTON_RMASK:
            breakBlock(mousePosition);
            break;
    }
}

void CurrentPlayer::update(float dt) {
    static GameMap *mapa = Engine::get()->getMap();
    input();
    Player::update(dt);

    if (moved){
        Camera::get()->update();
        toRender = true;
    }
    mapa->setFocusBlock(mousePosition, isInteractionInRange(mousePosition)? SDL_Color{0, 255, 0,255} : SDL_Color{255, 0, 0,255});
}
