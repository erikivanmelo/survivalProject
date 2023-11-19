#include "Input.h"
#include "../Core/Engine.h"
#include "../Camera/Camera.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>

Input *Input::instance = nullptr;

Input::Input()
{
    keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::listen()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_EVENT_QUIT:
                Engine::quit();
            break;

            case SDL_EVENT_KEY_DOWN:
                keyDown(event.key.keysym.scancode);break;

            case SDL_EVENT_KEY_UP:
                keyUp(event.key.keysym.scancode); break;

            case SDL_EVENT_WINDOW_RESIZED:
                Camera::getInstance()->setViewBoxSize(
                        event.window.data1, 
                        event.window.data2
                );

        }
        mouseState = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    }
}

bool Input::getKeyDown(SDL_Scancode key)
{
    return (keyStates[key] == 1);
}

bool Input::getKeyPressed(SDL_Scancode key)
{
    if (intervalTime > 0 && intervalTime < intervalPressed && lastKeyPressed == key)
    {
        intervalTime = 0;
        return true;
    }
    return false;
}

void Input::keyUp(SDL_Scancode key)
{
    lastKeyPressed = key;
    intervalTime = SDL_GetTicks() - startTime;
}

void Input::keyDown()
{
    startTime = SDL_GetTicks();
    keyStates = SDL_GetKeyboardState(nullptr);
}
