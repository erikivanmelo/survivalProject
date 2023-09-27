#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>

using namespace std;

class TextureManager{
	public :
		static TextureManager* getInstance(){
			return instance ? instance : ( instance = new TextureManager() );
		}

    static constexpr unsigned int TileH = 0x80000000;
    static constexpr unsigned int TileV = 0x40000000;
    static constexpr unsigned int TileD = 0x20000000;

		static const std::string assets;

		bool load( string id, string fileName, bool withTransparentMagenta = false );
		void drop( string id );
		void clean();

		void draw( string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void drawFrame(std::string id,int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawTile(std::string tilesetId, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

	private:
		TextureManager(){}
		~TextureManager();
		static TextureManager* instance;
		unordered_map< string, SDL_Texture* > textureMap;
};

#endif
