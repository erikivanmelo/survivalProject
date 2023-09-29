#include "Core/Engine.h"
#include "Timer/Timer.h"
#include <SDL2/SDL_log.h>

int main()
{

    try{
        Engine::getInstance()->init();

        while(Engine::getInstance()->isRunning()){
            Engine::getInstance()->events();
            Engine::getInstance()->update();
            Engine::getInstance()->render();
            Timer::getInstance()->tickUpdate();
        }
    }catch(const string &e){
        cerr << e;
    }
    Engine::getInstance()->clean();
    return 0;
}
