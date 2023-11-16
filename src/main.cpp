#include "Core/Engine.h"
#include "Timer/Timer.h"
#include <SDL2/SDL_log.h>

int main()
{

    try{
        Engine *engine = Engine::getInstance();
        engine->init();
        while(engine->isRunning()){
            engine->events();
            engine->update();
            engine->render();
            engine->printDebug();
            Timer::getInstance()->tickUpdate();
        }
    }catch(const string &e){
        cerr << e << endl;
    }
    Engine::clean();
    return 0;
}
