#include "TextureManager.h"
#include "../Core/Engine.h"

#include <SDL2/SDL_log.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>

TextureManager* TextureManager::instance = nullptr;

bool TextureManager::load( string id, string fileName ){
	SDL_Surface* surface = IMG_Load( fileName.c_str() );
	if( surface == nullptr ){
		SDL_Log("Failed to load image %s! SDL_image Error: %s\n", fileName.c_str(), IMG_GetError());
		return false;
	}
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(),surface);
	if ( texture == nullptr ){
		SDL_Log("Failed to create texture from %s! SDL Error: %s\n", fileName.c_str(), SDL_GetError());
		return false;
	}
	
	textureMap[id] = texture;

	return true;
}

void TextureManager::draw( string id, int x, int y, int width, int height, SDL_RendererFlip flip ){

	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect destRect = { x, y, width, height };
	SDL_RenderCopyEx( Engine::getInstance()->getRenderer(), textureMap[id], &srcRect, &destRect, 0, nullptr, flip );

}

void TextureManager::drop( string id ){
	SDL_DestroyTexture( textureMap[id] );
	textureMap.erase( id );
}

TextureManager::~TextureManager(){
	for( auto& texture : textureMap )
		SDL_DestroyTexture( texture.second );

	textureMap.clear();
	SDL_Log("TextureMap cleaned!");
}

void TextureManager::clean(){
	delete instance;
}



