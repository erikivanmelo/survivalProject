#include "Text.h"
#include "../Core/Engine.h"


Text::Text(const string &text, float x, float y, float fontSize, SDL_Color color, const string &font):
text(text),rect(x,y),fontSize(fontSize),color(color),font(font){

	this->texture = nullptr;
	this->fontType = TTF_OpenFont(font.c_str(), fontSize);
	this->updateTexture();
}

Text::~Text(){
	SDL_DestroyTexture(texture);
	TTF_CloseFont(fontType);
}

void Text::setText(const string &text){ 
	this->text = text;
	this->updateTexture();
}

void Text::setFontSize(const int fontSize){ 
	this->fontSize = fontSize;
	this->fontType = TTF_OpenFont(font.c_str(), fontSize);
}

void Text::setFont(const string &font){ 
	this->font = font;
	this->fontType = TTF_OpenFont(font.c_str(), fontSize); 
}

void Text::show(){
	SDL_FRect rect = { this->x, this->y, this->w, this->h };
	SDL_RenderCopy(TextureManager::renderer, texture, NULL, &rect);
}

void Text::updateTexture(){
	if(this->texture)
		SDL_DestroyTexture(texture);

	SDL_Surface *surface = TTF_RenderText_Solid(fontType, text.c_str(), color);
	if( !surface ) 
		throw "Failed to create surface from your font! SDL Error: " + string(SDL_GetError());

	this->h = surface->h;
	this->w = surface->w;

	if( !(this->texture = SDL_CreateTextureFromSurface(TextureManager::renderer, surface)) )
		throw "Failed to create texture from your text! SDL Error: " + string(SDL_GetError());
	
	SDL_FreeSurface(surface);
}
