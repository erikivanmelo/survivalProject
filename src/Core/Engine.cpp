#include "Engine.h"
#include "../Assets/AssetsManager.h"
#include "../Inputs/Input.h"
#include "../Timer/Timer.h"
#include "../Map/MapParser.h"
#include "../Camera/Camera.h"
#include "../Characters/Player.h"

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
    if( !(renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED )) )
        throw "Renderer could not be created! SDL_Error: " + string(SDL_GetError());

    if( !MapParser::getInstance()->load() )
        throw "Failed to load map";

    map = MapParser::getInstance()->getMap("overworld");

    
    AssetsManager::getInstance()->load();
    player = new Player( Vector2D( 0, 0 ) );

    SDL_SetRenderScale(renderer,SCREEN_SCALE,SCREEN_SCALE);

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
    Vector2D mousePosition = Input::getInstance()->getMousePosition();
    std::cout << "FPS:" << Timer::getInstance()->getFPS() << endl;
    player->getPosition().log("position");
    Camera::getInstance()->getPosition()->log("Camera");
    cout << "mouse:" << mousePosition.x << " - " <<  mousePosition.y << endl;
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


