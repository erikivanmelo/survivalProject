#ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <iostream>
#include <vector>
using namespace std;

class Text{

public:
	
	Text(const string &text, float x, float y, float fontSize, SDL_Color color, const string &font);
	~Text();

	void show();

	void setText(const string &text);
	inline void setX(int x){ this->rect.x = x; }
	inline void setY(int y){ this->rect.y = y; }
	inline void setColor(SDL_Color color){ this->color = color; }

	void setFontSize(const int fontSize);
	void setFont(const string &font);

private:
	string text;
	SDL_FRect rect;
	int fontSize;
	SDL_Color color;
	string font;

	void updateTexture();

	SDL_Texture *texture;
	TTF_Font* fontType;

};

#endif // TEXTMANAGER_H
