#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <SDL2/SDL_render.h>
#include <iostream>
#include "../Graphics/Animation.h"
#include <unordered_map>

#include <fstream>
#include <nlohmann/json.hpp>

namespace Assets{
  const std::string base		= "../assets/";
  const std::string maps		= base+"maps/";
  const std::string fonts		= base+"fonts/";
  const std::string sprites	= base+"sprites/";
  const int         pixelDepth = SDL_PIXELFORMAT_RGB565;
}

typedef struct{
    int firstId, lastId;
    int rowCount,colCount;
    int tileCount, tileSize;
    std::string name, source;
    std::vector<SDL_Texture*> textures;
    SDL_Rect srcRect;
}Tileset;

class AssetsManager{
    
public:
    
		static AssetsManager* getInstance(){
			return instance ? instance : ( instance = new AssetsManager() );
		}

    ~AssetsManager(){
        auto it = textureMap.begin();
        while (it != textureMap.end()) {
            SDL_DestroyTexture(it->second);
            it = textureMap.erase(it);
        }
        //TODO Crear destructor de texturas de tileset
        delete tileset;
        SDL_Log("TextureMap cleaned!");
    }


    SDL_Texture *loadTexture( const string &id, const string &fileName, bool withTransparentMagenta, const bool saveIt = true, const int x = 0, const int y = 0, const int width = 0, const int height = 0);

    void load();

    inline SDL_Texture *getTexture(const std::string &id) const{
        return textureMap.at(id);
    }

    inline AnimationSeqList *getAnimationSeqMap(const std::string &id){
        return animationSeqMap.at(id);
    }

    static void clean(){
        delete instance;
    }

    inline void setTileset(Tileset *tileset){
        this->tileset = tileset;
    }

    inline Tileset *getTileset()const{
        return this->tileset;
    }

private:
    static AssetsManager *instance;
		unordered_map< string, SDL_Texture*      > textureMap;
		unordered_map< string, AnimationSeqList* > animationSeqMap;
    Tileset *tileset;

};
#endif
