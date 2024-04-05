#include "Core/Engine.h"
#include "Timer/Timer.h"
#include "Graphics/Debug.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>

int main()
{

    try{
        Engine *engine = Engine::get();
        engine->init();
        while(engine->isRunning()){
            engine->update();
            engine->render();
            Timer::tickUpdate();
        }
    }catch(const string &e){
        cerr << e << endl;
    }
    Engine::clean();
    return 0;
}
