#include "Core/Engine.h"


int main()
{

    Engine::getInstance()->init();

    while(Engine::getInstance()->isRunning()){
        Engine::getInstance()->events();
        Engine::getInstance()->update(0.0f );
        Engine::getInstance()->render();
    }

    Engine::getInstance()->clean();
    return 0;
}
