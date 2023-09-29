#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;

class Text{

public:
	
	Text(const string &text, int x, int y, int fontSize, SDL_Color color, const string &font);
	~Text();

	void show();

	void setText(const string &text);
	inline void setX(int x){ this->x = x; }
	inline void setY(int y){ this->y = y; }
	inline void setColor(SDL_Color color){ this->color = color; }

	void setFontSize(const int fontSize);
	void setFont(const string &font);

private:
	string text;
	int x,y,h,w;
	int fontSize;
	SDL_Color color;
	string font;

	void updateTexture();

	SDL_Texture *texture;
	TTF_Font* fontType;

};

#endif // TEXTMANAGER_H
