#include "TextureManager.h"
#include "../Core/Engine.h"
#include "../Camera/Camera.h"
#include "../Helper.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>



void TextureManager::draw( const string &id, float x, float y, float width, float height, SDL_RendererFlip flip ){

  static const Vector2D *cam = Camera::getInstance()->getPosition();
	SDL_FRect srcRect = { 0, 0, width, height };
	SDL_FRect destRect = { x - cam->x, y - (cam->y/2), width, height };
	SDL_RenderTextureRotated( Engine::getInstance()->getRenderer(), AssetsManager::getInstance()->getTexture(id), &srcRect, &destRect, 0, nullptr, flip );

}

void TextureManager::drawFrame( const string &id, float x, float y, float width, float height, float row, float frame, SDL_RendererFlip flip)
{
	drawFrame(
			AssetsManager::getInstance()->getTexture(id),
			x,
			y,
			width,
			height,
			row,
			frame,
			flip
		);
}

void TextureManager::drawFrame( SDL_Texture *texture, float x, float y, float width, float height, float row, float frame, SDL_RendererFlip flip)
{
  static const Vector2D *cam = Camera::getInstance()->getPosition();
	if( !texture )
		return;
	//A row se le resta uno, porque en el sprite sheet la primera fila es la 0
	SDL_FRect srcRect = { width*frame, height*(row-1), width, height};
	SDL_FRect datRect = { (float)Helper::wrapToRange(x - cam->x, Engine::getInstance()->getMap()->getPixelWidth()-1), y - cam->y, width, height };
	SDL_RenderTextureRotated(Engine::getInstance()->getRenderer(), texture, &srcRect,&datRect,0,nullptr,flip);
}


void TextureManager::drawChunk( SDL_Texture *texture, SDL_FRect *rect )
{
	drawFrame(
		texture,
		rect->x,
		rect->y,
		rect->w,
		rect->h
	);
}

void TextureManager::drawTile( const Tile tile, float x, float y, SDL_RendererFlip flip)
{
	if(!tile)
		return;
	static Tileset *tileset = AssetsManager::getInstance()->getTileset();

	drawFrame( 
		tileset->textures[tile], 
		x, 
		y, 
		tileset->tileSize, 
		tileset->tileSize,
		1,
		0,
		flip
	);
}
