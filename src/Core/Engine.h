#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include "../Map/GameMap.h"
#include "../Characters/CurrentPlayer.h"

// Set the frame rate, updates per second and debugPrint per second
#define FPS 0
#define UPS 0.02 //1/50 ps

class Engine
{
    public:
        static Engine* get(){
            return instance ? instance : ( instance = new Engine() );
        }
        inline static void clean(){ delete instance; }
       
        void init();
        static void quit();

        void update();
        void render();
        void debug();

        inline bool isRunning()const{ return running; }

        inline GameMap* getMap()const{ return map; }

        ~Engine();
    private:
        inline void setRunning( bool running ){ this->running = running; }
        Engine(){}
        bool running = false;
        SDL_Window* window;
        static Engine* instance;
        GameMap *map;
        uint16_t currentFps, currentUps;
        bool toRender = false;
        CurrentPlayer *player = nullptr;
};

#endif
