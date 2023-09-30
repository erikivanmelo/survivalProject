#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

class Input
{
public:

    static Input *getInstance(){
        return instance = (instance != nullptr)? instance : new Input();
    }

    ~Input();

    void listen();
    bool getKeyDown(SDL_Scancode key);
    bool getKeyPressed(SDL_Scancode key);

private:
    Input();
    static Input *instance;

    void keyUp(SDL_Scancode key);
    void keyDown(SDL_Scancode key);

    const Uint8* keyStates;

    double startTime = 0;
    double endTime = 0;
    double intervalTime = 0;
    const double intervalPressed = 200;
    SDL_Scancode lastKeyPressed;
};

#endif // INPUT_H
