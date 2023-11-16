#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

        ~Engine();
    private:
        inline void setRunning( bool running ){ this->running = running; }
        Engine(){}
        bool running = false;
        SDL_Window* window;
        SDL_Renderer* renderer;
        static Engine* instance;
        GameMap *map;
};

#endif
