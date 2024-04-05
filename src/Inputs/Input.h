#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_stdinc.h>
#include "../Physics/Vector2D.h"
#define INTERVAL_PERESSED 200  

typedef Uint32 MouseState;

class Input
{
public:

    static Input *get(){
        return instance = (instance != nullptr)? instance : new Input();
    }
    inline static void clean(){ delete instance; }

    void listen();
    bool getKeyDown(SDL_Scancode key);
    bool getKeyPressed(SDL_Scancode key);

    inline MouseState getMouseState()const{
        return mouseState;
    }

    inline Vector2D getMousePosition()const{
        return mousePosition;
    }

    inline void debug() {
        mousePosition.log("Mouse Position");
    }

private:
    Input();
    static Input *instance;

    void keyUp(SDL_Scancode key);
    void keyDown();

    MouseState mouseState;
    Vector2D mousePosition;


    const Uint8* keyStates;

    double startTime = 0;
    double intervalTime = 0;
    SDL_Scancode lastKeyPressed;
};

#endif // INPUT_H
