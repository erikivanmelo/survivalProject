#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_stdinc.h>

typedef Uint32 MouseState;

class Input
{
public:

    static Input *getInstance(){
        return instance = (instance != nullptr)? instance : new Input();
    }
    inline static void clean(){ delete instance; }

    ~Input();

    void listen();
    bool getKeyDown(SDL_Scancode key);
    bool getKeyPressed(SDL_Scancode key);

    inline MouseState getMouseState()const{
        return mouseState;
    }

    inline int getMouseX()const{
        return mouseX;
    }

    inline int getMouseY()const{
        return mouseY;
    }

private:
    Input();
    static Input *instance;

    void keyUp(SDL_Scancode key);
    void keyDown(SDL_Scancode key);

    MouseState mouseState;
    int mouseX, mouseY;


    const Uint8* keyStates;

    double startTime = 0;
    double intervalTime = 0;
    const double intervalPressed = 200;
    SDL_Scancode lastKeyPressed;
};

#endif // INPUT_H
