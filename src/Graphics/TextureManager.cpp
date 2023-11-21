#include "TextureManager.h"
#include "../Core/Engine.h"
#include "../Camera/Camera.h"
#include "../Helper.h"

void TextureManager::draw( SDL_Texture *texture,const float x, const float y, const float width, const float height, const SDL_RendererFlip flip )
{
  static const Vector2D *cam = Camera::getInstance()->getPosition();
	if( !texture )
		return;
	SDL_FRect datRect = { 
		(float)Helper::wrapToRange(x - cam->x, Engine::getInstance()->getMap()->getPixelWidth()-1, width), 
		y - cam->y, 
		width, 
		height 
	};
	SDL_RenderTextureRotated(Engine::getInstance()->getRenderer(), texture, nullptr,&datRect,0,nullptr,flip);
}

void TextureManager::drawFrame( SDL_Texture *texture, const float x, const float y, const float width, const float height, const float row, const float frame, const SDL_RendererFlip flip )
{
  static const Vector2D *cam = Camera::getInstance()->getPosition();
	if( !texture )
		return;
	//A row se le resta uno, porque en el sprite sheet la primera fila es la 0
	SDL_FRect srcRect = { width*frame, height*(row-1), width, height};
	SDL_FRect datRect = { 
		(float)Helper::wrapToRange(x - cam->x, Engine::getInstance()->getMap()->getPixelWidth()-1), 
		y - cam->y, 
		width, 
		height 
	};
	SDL_RenderTextureRotated(Engine::getInstance()->getRenderer(), texture, &srcRect,&datRect,0,nullptr,flip);
}

