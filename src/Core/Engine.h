#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include "../Map/GameMap.h"

#define partPerSecond(__PPS) __PPS? 1.0/__PPS : 0

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
        void printDebug();

        inline bool isRunning()const{ return running; }

        inline GameMap* getMap()const{ return map; }

        inline void setFps(const int fps){
            this->fps = partPerSecond(fps);
        }

        inline void setUps(const int ups){
            this->ups = partPerSecond(ups);
        }

        inline void setDps(const int dps){
            this->dps = partPerSecond(dps);
        }

        ~Engine();
    private:
        inline void setRunning( bool running ){ this->running = running; }
        Engine(){}
        bool running = false;
        SDL_Window* window;
        static Engine* instance;
        GameMap *map;
        int currentFps;
        float fps, dps, ups;

};

#endif
