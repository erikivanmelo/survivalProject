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
    }

    Engine::getInstance()->clean();
    return 0;
}
