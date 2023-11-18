#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_stdinc.h>

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

    inline Uint32 getMouseState()const{
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

    Uint32 mouseState;
    int mouseX, mouseY;


    const Uint8* keyStates;

    double startTime = 0;
    double intervalTime = 0;
    const double intervalPressed = 200;
    SDL_Scancode lastKeyPressed;
};

#endif // INPUT_H
