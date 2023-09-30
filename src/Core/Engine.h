#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Map/GameMap.h"
#include "../Graphics/Text.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 300

class Engine
{
    public:
        static Engine* getInstance(){
            return instance ? instance : ( instance = new Engine() );
        }
       
        void init();
        static void quit();

        void clean();
        void update();
        void render();
        void events();

        inline bool isRunning()const{ return running; }
        inline SDL_Renderer* getRenderer()const{ return renderer; }

        inline GameMap* getMap()const{ return map; }

    private:
        Engine(){}
        ~Engine();
        bool running = false;
        SDL_Window* window;
        SDL_Renderer* renderer;
        static Engine* instance;
        GameMap *map;

        Text *debugInfo;
};

#endif
