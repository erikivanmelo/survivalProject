#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "Layer.h"

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

    std::vector<Layer*> getMapLayers()const{return mapLayers;}

private:
    friend class MapParser;
    std::vector<Layer*> mapLayers;

};

#endif // GAMEMAP_H
