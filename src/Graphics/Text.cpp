#include "Text.h"
#include "../Core/Engine.h"

void Text::setText(string text){ 
	this->text = text;
	SDL_FreeSurface(surface);
	this->surface = TTF_RenderText_Solid(this->fontType, text.c_str(), this->color);
	this->texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), surface);
}


Text::Text(string text, int x, int y, int fontSize, SDL_Color color, string font):
text(text),x(x),y(y),fontSize(fontSize),color(color),font(font){

	this->fontType = TTF_OpenFont(font.c_str(), fontSize);
	surface = TTF_RenderText_Solid(fontType, text.c_str(), color);
	if (!surface) {
		SDL_Log("Failed to create surface from your font! SDL Error: %s\n", SDL_GetError());
		return;
	}

	this->texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), surface);
	if (!texture) {
		SDL_Log("Failed to create texture from your text! SDL Error: %s\n", SDL_GetError());
		return;
	}
}

Text::~Text(){
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(fontType);
}

void Text::show(){
	SDL_Rect rect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(Engine::getInstance()->getRenderer(), texture, NULL, &rect);
}
