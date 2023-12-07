#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include "../Map/GameMap.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 300
#define SCREEN_SCALE 2

class Engine
{
    public:
        static Engine* getInstance(){
            return instance ? instance : ( instance = new Engine() );
        }
        inline static void clean(){ delete instance; }
       
        void init();
        static void quit();

        void update();
        void render();
        void events();
        void printDebug();

        inline bool isRunning()const{ return running; }
        inline SDL_Renderer* getRenderer()const{ return renderer; }

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

        inline float partPerSecond(const int pps)const{
            return pps? 1.0/pps : 0;
        }

        ~Engine();
    private:
        inline void setRunning( bool running ){ this->running = running; }
        Engine(){}
        bool running = false;
        SDL_Window* window;
        SDL_Renderer* renderer;
        static Engine* instance;
        GameMap *map;
        int currentFps;
        float fps, dps, ups;

};

#endif
