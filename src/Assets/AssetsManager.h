#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <SDL3/SDL_render.h>
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
    int rowCount,colCount;
    int tileCount, tileSize;
    std::string name, source;
    std::vector<SDL_Texture*> textures;
    SDL_FRect srcRect;
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
        delete tileset;

        for(int i = 1; i < tileset->tileCount; ++i){
            SDL_DestroyTexture(tileset->textures[i]);
        }

        SDL_Log("TextureMap cleaned!");
    }


    SDL_Texture *loadTexture( const string &id, const string &fileName, const bool withTransparentMagenta, const bool saveIt = true, const SDL_Rect srcRect = {0,0,0,0} );

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
