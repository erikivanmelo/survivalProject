#include "TextureManager.h"
#include "../Core/Engine.h"
#include "../Camera/Camera.h"
#include "../Helper.h"

SDL_Renderer* TextureManager::renderer = nullptr; 

SDL_FRect TextureManager::adaptRectCoordinate(SDL_FRect datRect){
	static const Vector2D *cam = Camera::get()->getPosition();
	datRect.x = (float)Helper::wrapToRange(datRect.x - cam->x, Engine::getInstance()->getMap()->getPixelWidth()-1, datRect.w);
	datRect.y -= cam->y;
	return datRect;
}

void TextureManager::draw(SDL_Texture *texture,const float x, const float y, const float width, const float height, SDL_FRect *srcRect, const SDL_RendererFlip flip, const Uint8 darknessLevel)
{
	if( !texture )
		return;
	SDL_FRect datRect = TextureManager::adaptRectCoordinate({ x, y, width, height });
	TextureManager::setTextureDarkness(texture, darknessLevel);
	TextureManager::renderTexture(texture, srcRect, &datRect, flip);
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void TextureManager::drawFrame( SDL_Texture *texture, const float x, const float y, const float width, const float height, const float row, const float frame, const SDL_RendererFlip flip, const Uint8 darknessLevel)
{
	//A row se le resta uno, porque en el sprite sheet la primera fila es la 0
	SDL_FRect srcRect = { width*frame, height*(row-1), width, height};
	TextureManager::draw(texture, x, y, width, height, &srcRect, flip, darknessLevel);
}

void TextureManager::drawRect( const float x, const float y, const float width, const float height, const SDL_Color &color)
{
	SDL_FRect datRect = TextureManager::adaptRectCoordinate({ x, y, width, height });
	SDL_SetRenderDrawColor(TextureManager::renderer, color.r, color.g, color.b, color.a);
	SDL_RenderRect(TextureManager::renderer, &datRect);
}
