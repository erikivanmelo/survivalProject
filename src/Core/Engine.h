#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Engine
{
    public:
        static Engine* getInstance(){
            return instance ? instance : ( instance = new Engine() );
        }
       
        bool init();
        void quit();

        bool clean();
        void update( float dt );
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
};

#endif
