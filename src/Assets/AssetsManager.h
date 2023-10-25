#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include "../Core/Engine.h"
#include <SDL2/SDL_render.h>
#include <iostream>
#include "../Graphics/Animation.h"
#include <unordered_map>
#include <string_view>

#include <fstream>
#include <nlohmann/json.hpp>

namespace Assets{
  const std::string base		= "../assets/";
  const std::string maps		= base+"maps/";
  const std::string fonts		= base+"fonts/";
  const std::string sprites	= base+"sprites/";
}

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
        SDL_Log("TextureMap cleaned!");
    }


    SDL_Texture *loadTexture( const string &id, const string &fileName, bool withTransparentMagenta );

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

private:
    static AssetsManager *instance;
		unordered_map< string, SDL_Texture*      > textureMap;
		unordered_map< string, AnimationSeqList* > animationSeqMap;

};
#endif
