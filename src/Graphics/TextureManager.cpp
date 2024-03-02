#include "TextureManager.h"
#include "../Core/Engine.h"
#include "../Camera/Camera.h"
#include "../Helper.h"

void TextureManager::draw( SDL_Texture *texture,const float x, const float y, const float width, const float height, const SDL_RendererFlip flip, const Uint8 darknessLevel)
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
  SDL_SetTextureColorMod(texture, 255 - darknessLevel, 255 - darknessLevel, 255 - darknessLevel);

	SDL_RenderTextureRotated(Engine::getInstance()->getRenderer(), texture, nullptr,&datRect,0,nullptr,flip);

	SDL_SetTextureColorMod(texture, 255, 255, 255);

}

void TextureManager::drawFrame( SDL_Texture *texture, const float x, const float y, const float width, const float height, const float row, const float frame, const SDL_RendererFlip flip, const Uint8 darknessLevel)
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

	SDL_SetTextureColorMod(texture, 255 - darknessLevel, 255 - darknessLevel, 255 - darknessLevel);
	SDL_RenderTextureRotated(Engine::getInstance()->getRenderer(), texture, &srcRect,&datRect,0,nullptr,flip);
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}



void TextureManager::drawRect( const float x, const float y, const float width, const float height, const SDL_Color &color)
{
	static const Vector2D *cam = Camera::getInstance()->getPosition();
	SDL_FRect datRect = { 
		(float)Helper::wrapToRange(x - cam->x, Engine::getInstance()->getMap()->getPixelWidth()-1), 
		y - cam->y, 
		width, 
		height 
	};
	SDL_SetRenderDrawColor(Engine::getInstance()->getRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderRect(Engine::getInstance()->getRenderer(), &datRect);
}
