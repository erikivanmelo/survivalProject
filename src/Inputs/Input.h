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

private:
    Input();
    static Input *instance;

    void keyUp();
    void keyDown();

    const Uint8* keyStates;

};

#endif // INPUT_H
