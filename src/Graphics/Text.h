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
	
	Text(string text, int x, int y, int fontSize, SDL_Color color, string font);
	~Text();

	void show();
	void clear();

	void setText(string text);
	inline void setX(int x){ this->x = x; }
	inline void setY(int y){ this->y = y; }
	inline void setColor(SDL_Color color){ this->color = color; }

	inline void setFontSize(int fontSize){ 
		this->fontSize = fontSize;
		this->fontType = TTF_OpenFont(font.c_str(), fontSize);
	}

	inline void setFont(string font){ 
		this->font = font;
		this->fontType = TTF_OpenFont(font.c_str(), fontSize); 
	}


private:
	int fontSize;
	SDL_Color color;
	int x,y;
	string font;
	string text;

	SDL_Texture *texture;
	TTF_Font* fontType;
	SDL_Surface *surface;

};

#endif // TEXTMANAGER_H
