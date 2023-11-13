#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "../Assets/AssetsManager.h"
#include "../Map/Chunk.h"

using namespace std;

class TextureManager{
	public :
    static constexpr unsigned int TileH = 0x80000000;
    static constexpr unsigned int TileV = 0x40000000;
    static constexpr unsigned int TileD = 0x20000000;



		static void draw( const string &id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE );

    static void drawFrame( const string &id,int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

     static void drawFrame( SDL_Texture *texture,int x, int y, int width, int height, int row = 1, int frame = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    static void drawTile( const Tile tile, int x, int y, SDL_RendererFlip flip = SDL_FLIP_NONE);

};

#endif
