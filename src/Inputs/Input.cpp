#include "Input.h"
#include "../Core/Engine.h"

Input *Input::instance = nullptr;

Input::Input()
{
    keyStates = SDL_GetKeyboardState(nullptr);
}

Input::~Input()
{
    delete keyStates;
}

void Input::listen()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT: 
                Engine::getInstance()->quit(); break;

            case SDL_KEYDOWN: 
                keyDown(); break;

            case SDL_KEYUP: 
                keyUp(); break;
        }
    }
}

bool Input::getKeyDown(SDL_Scancode key)
{
    return (keyStates[key] == 1);
}

void Input::keyUp()
{
    keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::keyDown()
{
    keyStates = SDL_GetKeyboardState(nullptr);
}

