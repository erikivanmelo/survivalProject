#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Map/GameMap.h"
#include "../Graphics/Text.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 300
#define SCREEN_SCALE 1

namespace Assets{
	const string base			= "../assets/";
	const string maps			= base+"maps/";
	const string fonts		= base+"fonts/";
	const string sprites	= base+"sprites/";
}

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

        Text *debugInfo;
};

#endif
