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
    inline static void clean(){ delete instance; }

    static constexpr unsigned int TileH = 0x80000000;
    static constexpr unsigned int TileV = 0x40000000;
    static constexpr unsigned int TileD = 0x20000000;

		bool load( const string &id, const string &fileName, bool withTransparentMagenta = false );
		void drop( const string &id );

		void draw( const string &id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void drawFrame( const string &id,int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawTile( const string &tilesetId, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

		~TextureManager();
	private:
		TextureManager(){}
		static TextureManager* instance;
		unordered_map< string, SDL_Texture* > textureMap;
};

#endif
