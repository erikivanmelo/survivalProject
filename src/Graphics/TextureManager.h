#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL.h>

class TextureManager{
	public :
    static constexpr unsigned int TileH = 0x80000000;
    static constexpr unsigned int TileV = 0x40000000;
    static constexpr unsigned int TileD = 0x20000000;

    static void draw( SDL_Texture *texture,const float x, const float y, const float width, const float height, const SDL_RendererFlip flip = SDL_FLIP_NONE, const Uint8 darknessLevel = 0);

    static void drawFrame( SDL_Texture *texture, const float x, const float y, const float width, const float height, const float row = 1, const float frame = 0, const SDL_RendererFlip flip = SDL_FLIP_NONE, const Uint8 darknessLevel = 0);

     static void drawRect( const float x, const float y, const float width, const float height, const SDL_Color &color);


};

#endif
