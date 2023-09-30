#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "TileLayer.h"

class GameMap
{
public:
    void render(){
        for(unsigned int i = 0; i < mapLayers.size(); i++)
            mapLayers[i]->render();
    }

    void update(){
        for(unsigned int i = 0; i < mapLayers.size(); i++)
            mapLayers[i]->update();
    }

    std::vector<TileLayer*> getMapLayers()const{return mapLayers;}

private:
    friend class MapParser;
    std::vector<TileLayer*> mapLayers;

};

#endif // GAMEMAP_H
