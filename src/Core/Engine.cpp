#include "Engine.h"
#include "../Assets/AssetsManager.h"
#include "../Inputs/Input.h"
#include "../Timer/Timer.h"
#include "../Map/MapParser.h"
#include "../Camera/Camera.h"
#include "../Characters/Player.h"
#include "../Graphics/TextureManager.h"
#include "../Camera/Camera.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <iostream>
using namespace std;

Engine* Engine::instance = nullptr;
Player* player = nullptr;
void Engine::init(){
    //Initialize SDL

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        throw "SDL could not initialize! SDL_Error: " + string(SDL_GetError());

    //Create window
    if( !(window = SDL_CreateWindow("survivalProject2", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE) ) )
        throw std::string("Window could not be created! SDL_Error: " + string(SDL_GetError()));

    //Create renderer
    if( !(TextureManager::renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED )) )
        throw "Renderer could not be created! SDL_Error: " + string(SDL_GetError());

    SDL_SetRenderScale(TextureManager::renderer,SCREEN_SCALE,SCREEN_SCALE);
    SDL_SetRenderDrawColor(TextureManager::renderer, 124, 218, 254, 255);

    AssetsManager::get()->load();

    MapParser::get()->load();
    map = MapParser::get()->getMap("overworld");
    
    player = new Player();
    Camera::constructor(
        player->getOrigin(), 
        map->getPixelHeight(), 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SCREEN_SCALE,
        CHUNK_PIXEL_SQUARE_SIZE
    );

    // Set the frame rate, updates per second and debugPrint per second
    setFps(0);
    setUps(50);
    setDps(10);
    running = true;
}

Engine::~Engine(){
    AssetsManager::clean();
    Input::clean();
    MapParser::clean();
    SDL_DestroyRenderer(TextureManager::renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Engine::quit(){
    get()->setRunning(false);
}

void Engine::printDebug(){
    startInLapse(dt, dps, Timer::getDeltaTime())
        std::cout << "FPS:" << currentFps << endl;
        player->getPosition().log("position");
        Camera::get()->getPosition()->log("Camera");
        Input::get()->getMousePosition().log("Mouse");
        cout << endl;
    endInLapse(dt, dps)
}

void Engine::update(){
    startInLapse(dt, ups, Timer::getDeltaTime())
        player->update(dt);
        map->update();
    endInLapse(dt, ups)
}

void Engine::render(){
    static int frameCount = 0;
    startInLapse(dt,fps, Timer::getDeltaTime())
        frameCount++;
        SDL_SetRenderDrawColor(TextureManager::renderer, 124, 218, 254, 255);

        startInLapse(fpsTimer, 1.0, dt)
            currentFps = static_cast<double>(frameCount) / fpsTimer;
            frameCount = 0;
        endInLapse(fpsTimer, 1.0)

        SDL_RenderClear(TextureManager::renderer);

        map->render();
        player->draw();

        SDL_RenderPresent(TextureManager::renderer);
    endInLapse(dt,fps)
}


void Engine::events(){
    Input::get()->listen();
}

