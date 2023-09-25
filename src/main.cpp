#include "Core/Engine.h"
#include "Timer/Timer.h"

int main()
{

    Engine::getInstance()->init();

    while(Engine::getInstance()->isRunning()){
        Engine::getInstance()->events();
        Engine::getInstance()->update();
        Engine::getInstance()->render();
        Timer::getInstance()->tickUpdate();
        SDL_Log("FPS: %i \n", Timer::getInstance()->getFPS());
        SDL_Log("DeltaTime: %f \n\n", Timer::getInstance()->getDeltaTime());
    }

    Engine::getInstance()->clean();
    return 0;
}
