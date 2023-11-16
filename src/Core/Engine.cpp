#include "Engine.h"
#include "../Assets/AssetsManager.h"
#include "../Characters/Player.h"
#include "../Inputs/Input.h"
#include "../Timer/Timer.h"
#include "../Map/MapParser.h"
#include "../Camera/Camera.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;

Engine* Engine::instance = nullptr;
Player* player = nullptr;

void Engine::init(){
    //Initialize SDL

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        throw "SDL could not initialize! SDL_Error: " + string(SDL_GetError());

    if( IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG ) < 0 )
        throw "IMG could not initialize! SDL_Error: " + string(IMG_GetError());

    if( TTF_Init() < 0 )
        throw "TTF could not initialize! SDL_Error: " + string(TTF_GetError());

    //Create window
    if( !(window = SDL_CreateWindow("survivalProject2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)) )
        throw "Window could not be created! SDL_Error: " + string(SDL_GetError());

    //Create renderer
    if( !(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED )) )
        throw "Renderer could not be created! SDL_Error: " + string(SDL_GetError());

    if( !MapParser::getInstance()->load() )
        throw "Failed to load map";

    map = MapParser::getInstance()->getMap("overworld");

    
    AssetsManager::getInstance()->load();
    player = new Player( Vector2D( 0, 0 ) );

    SDL_RenderSetScale(renderer,SCREEN_SCALE,SCREEN_SCALE);

    Camera::getInstance()->setTarget( player->getOrigin() );

    running = true;
}

Engine::~Engine(){
    AssetsManager::clean();
    Timer::clean();
    Camera::clean();
    Input::clean();
    MapParser::clean();
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Engine::quit(){
    getInstance()->setRunning(false);
}

void Engine::printDebug(){
    static const float updateTime = 1.0/10;
    static float dt;
    if( (dt += Timer::getInstance()->getDeltaTime()) < updateTime )
        return;
    std::cout << "FPS:" << Timer::getInstance()->getFPS() << endl;
    player->getPosition().log("position");

    cout << endl;
    dt -= updateTime ;
}

void Engine::update(){
    static const float updateTime = 1.0/50;
    static float dt;
    if( (dt += Timer::getInstance()->getDeltaTime()) < updateTime )
        return;
    map->update();
    player->update(dt);

    dt -= updateTime ;
}

void Engine::render(){
    //set the drawing color to blue in the buffer
    SDL_SetRenderDrawColor(renderer, 124, 218, 254, 255);
    //Clear the buffer
    SDL_RenderClear(renderer);

    map->render();
    player->draw();
    //Update the screen with the buffer
    SDL_RenderPresent(renderer);
}


void Engine::events(){
    Input::getInstance()->listen();
}


