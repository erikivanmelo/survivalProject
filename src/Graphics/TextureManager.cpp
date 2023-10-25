#include "TextureManager.h"
#include "../Core/Engine.h"
#include "../Camera/Camera.h"

#include <SDL2/SDL_log.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>



void TextureManager::draw( const string &id, int x, int y, int width, int height, SDL_RendererFlip flip ){

  Vector2D cam =  Camera::getInstance()->getPosition();
	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect destRect = { (int)(x - cam.x), (int)(y - (cam.y/2)), width, height };
	SDL_RenderCopyEx( Engine::getInstance()->getRenderer(), AssetsManager::getInstance()->getTexture(id), &srcRect, &destRect, 0, nullptr, flip );

}

void TextureManager::drawFrame( const string &id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
  Vector2D cam =  Camera::getInstance()->getPosition();
	//A row se le resta uno, porque en el sprite sheet la primera fila es la 0
	SDL_Rect srcRect = { width*frame, height*(row-1), width, height};
	SDL_Rect datRect = { (int)(x - cam.x), (int)(y - cam.y), width, height };
	SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), AssetsManager::getInstance()->getTexture(id), &srcRect,&datRect,0,nullptr,flip);
}
void TextureManager::drawFrame( SDL_Texture *texture, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
  Vector2D cam =  Camera::getInstance()->getPosition();
	//A row se le resta uno, porque en el sprite sheet la primera fila es la 0
	SDL_Rect srcRect = { width*frame, height*(row-1), width, height};
	SDL_Rect datRect = { (int)(x - cam.x), (int)(y - cam.y), width, height };
	SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), texture, &srcRect,&datRect,0,nullptr,flip);
}

void TextureManager::drawTile( const string &tilesetId, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    Vector2D cam =  Camera::getInstance()->getPosition();
		SDL_Rect srcRect = { tileSize*frame, tileSize*row, tileSize, tileSize};
    SDL_Rect datRect = { (int)(x - cam.x), (int)(y - cam.y), tileSize, tileSize };
    SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), 
				AssetsManager::getInstance()->getTexture(tilesetId), 
				&srcRect,
				&datRect,
				0,
				nullptr,
				flip);
}
