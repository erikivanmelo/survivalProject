#include "Engine.h"
#include "../Graphics/TextureManager.h"
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

bool Engine::init(){
    //Initialize SDL
    TTF_Init();

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        throw "SDL could not initialize! SDL_Error: " + string(SDL_GetError());

    if( IMG_Init( IMG_INIT_JPG ) < 0 )
        throw "IMG could not initialize! SDL_Error: " + string(IMG_GetError());

    if( TTF_Init() < 0 )
        throw "TTF could not initialize! SDL_Error: " + string(TTF_GetError());

    //Create window
    if( !(window = SDL_CreateWindow("survivalProject2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0)) )
        throw "Window could not be created! SDL_Error: " + string(SDL_GetError());

    //Create renderer
    if( !(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) )
        throw "Renderer could not be created! SDL_Error: " + string(SDL_GetError());

    if( !MapParser::getInstance()->load() )
        throw "Failed to load map";

    map = MapParser::getInstance()->getMap("overworld");

    TextureManager::getInstance()->load( "player_walk", TextureManager::assets+"player_walk.png", true );
    player = new Player(new Properties( "player_walk", 100, 100, 32, 32 ));

    Camera::getInstance()->setTarget( player->getOrigin() );

    debugInfo = new Text(" ", 0, 0, 20, {255,255,255,255}, TextureManager::assets+"arial.ttf");

    return running = true;
}

Engine::~Engine(){
    delete map;
    delete debugInfo;
}

bool Engine::clean(){
    running = false;
    TextureManager::getInstance()->clean();
    Timer::getInstance()->clean();
    delete instance;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return true;
}

void Engine::quit(){
    Engine::getInstance()->clean();
}

void Engine::update(){
    float dt = Timer::getInstance()->getDeltaTime();
    map->update();
    player->update(dt);
    debugInfo->setText("FPS:"+to_string(Timer::getInstance()->getFPS()));
}

void Engine::render(){
    //set the drawing color to blue in the buffer
    SDL_SetRenderDrawColor(renderer, 124, 218, 254, 255);
    //Clear the buffer
    SDL_RenderClear(renderer);

    map->render();
    player->draw();
    debugInfo->show();
    //Update the screen with the buffer
    SDL_RenderPresent(renderer);
}


void Engine::events(){
    Input::getInstance()->listen();
}


