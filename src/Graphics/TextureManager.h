#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL.h>

class TextureManager{
  public:
    static SDL_Renderer *renderer;
    static constexpr unsigned int TileH = 0x80000000;
    static constexpr unsigned int TileV = 0x40000000;
    static constexpr unsigned int TileD = 0x20000000;

    static void inline setTextureDarkness( SDL_Texture *texture, const Uint8 level) {
      SDL_SetTextureColorMod(texture, 255 - level, 255 - level, 255 - level);
    }

    static void inline renderTexture(SDL_Texture *texture, const SDL_FRect *srcRect, const SDL_FRect *dstRect, const SDL_RendererFlip flip = SDL_FLIP_NONE, const double angle = 0, const SDL_FPoint *center = nullptr, SDL_Renderer *renderer = nullptr) {
      if (!renderer)
        renderer = TextureManager::renderer;
      SDL_RenderTextureRotated(renderer, texture, srcRect, dstRect, angle, center, flip);
    }

    static void inline renderTexture(SDL_Texture *texture, const SDL_FRect *srcRect, const SDL_FRect *dstRect, SDL_Renderer *renderer = nullptr) {
      if (!renderer)
        renderer = TextureManager::renderer;
      SDL_RenderTexture(renderer, texture, srcRect, dstRect);
    }

    static SDL_FRect adaptRectCoordinate(SDL_FRect datRect);

    static void draw(SDL_Texture *texture, const float x, const float y, const float width, const float height, SDL_FRect *srcRect = nullptr, const SDL_RendererFlip flip = SDL_FLIP_NONE, const Uint8 darknessLevel = 0);

    static void drawFrame( SDL_Texture *texture, const float x, const float y, const float width, const float height, const float row = 1, const float frame = 0, const SDL_RendererFlip flip = SDL_FLIP_NONE, const Uint8 darknessLevel = 0);

     static void drawRect( const float x, const float y, const float width, const float height, const SDL_Color &color);


};

#endif
