#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Map/GameMap.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

class Engine
{
    public:
        static Engine* getInstance(){
            return instance ? instance : ( instance = new Engine() );
        }
       
        bool init();
        void quit();

        bool clean();
        void update();
        void render();
        void events();

        inline bool isRunning(){ return running; }
        inline SDL_Renderer* getRenderer(){ return renderer; }

    private:
        Engine(){}
        ~Engine();
        bool running = false;
        SDL_Window* window;
        SDL_Renderer* renderer;
        static Engine* instance;
        GameMap *map;
};

#endif
