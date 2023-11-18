#include "Input.h"
#include "../Core/Engine.h"
#include "../Camera/Camera.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

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
            case SDL_QUIT:
                Engine::quit();
            break;

            case SDL_KEYDOWN:
                keyDown();break;

            case SDL_KEYUP:
                keyUp(event.key.keysym.scancode); break;

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    Camera::getInstance()->setViewBoxSize(
                            event.window.data1, 
                            event.window.data2
                    );

        }
        mouseState = SDL_GetMouseState(&mouseX, &mouseY);
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
