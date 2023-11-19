#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>
#include "../Assets/AssetsManager.h"
#include "../Map/Chunk.h"

using namespace std;

class TextureManager{
	public :
    static constexpr unsigned int TileH = 0x80000000;
    static constexpr unsigned int TileV = 0x40000000;
    static constexpr unsigned int TileD = 0x20000000;



		static void draw( const string &id, float x, float y, float width, float height, SDL_RendererFlip flip = SDL_FLIP_NONE );

    static void drawFrame( const string &id,float x, float y, float width, float height, float row, float frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

     static void drawFrame( SDL_Texture *texture,float x, float y, float width, float height, float row = 1, float frame = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    static void drawChunk( SDL_Texture *texture, SDL_FRect *rect);
    static void drawTile( const Tile tile, float x, float y, SDL_RendererFlip flip = SDL_FLIP_NONE);

};

#endif
