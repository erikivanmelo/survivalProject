#include "Engine.h"
#include "../Graphics/TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <iostream>
using namespace std;

Engine* Engine::instance = nullptr;

bool Engine::init(){
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 && IMG_Init( IMG_INIT_JPG ) < 0 ){
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

    //load the uwutest texture
    TextureManager::getInstance()->load("uwutest", "../assets/uwutest.jpg");

    return running = true;
}

Engine::~Engine(){
    TextureManager::getInstance()->clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

bool Engine::clean(){
    delete instance;
    return true;
}

void Engine::quit(){
    SDL_Quit();
    running = false;
}

void Engine::update( float dt ){
    
}

void Engine::render(){
    //Clear the buffer
    SDL_RenderClear(renderer);
    //set the drawing color to blue in the buffer
    SDL_SetRenderDrawColor(renderer, 124, 218, 254, 255);

    //Draw the uwutest texture
    TextureManager::getInstance()->draw( "uwutest", (SCREEN_WIDTH/2)-(336/2), (SCREEN_HEIGHT/2)-(280/2), 336, 280 );
    //Update the screen with the buffer
    SDL_RenderPresent(renderer);
}


void Engine::events(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch( event.type ){
        case SDL_QUIT:
            quit();
            break;
    }
}


