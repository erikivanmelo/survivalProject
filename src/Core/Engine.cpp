#include "Engine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <iostream>
using namespace std;

Engine* Engine::instance = nullptr;

bool Engine::init(){
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0 ){
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return false;
    }

    //Create window
    window = SDL_CreateWindow("survivalProject2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if( window == nullptr ){
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if( renderer == nullptr ){
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    return running = true;
}


bool Engine::clean(){}
bool Engine::quit(){}

void Engine::update( float dt ){
    
}

void Engine::render(){
    SDL_SetRenderDrawColor(renderer, 124, 218, 254, 255);
    SDL_RenderPresent(renderer);
}


void Engine::events(){}


