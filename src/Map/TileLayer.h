#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <string>
#include <vector>
#include <SDL2/SDL.h>

typedef struct{
    int firstId, lastId;
    int rowCount,colCount;
    int tileCount, tileSize;
    std::string name, source;
}Tileset;

using TileMap = std::vector<std::vector<unsigned int>>;

class TileLayer : public Layer
{
public:
    TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, Tileset tileset);
    virtual void render();
    virtual void update();
    inline TileMap getTileMap(){return tileMap;}
private:
    int tileSize;
    int rowCount, colCount;

    TileMap tileMap;
    Tileset tileset;

    void determineRotation(unsigned int& tileId, SDL_RendererFlip& flip);
};

#endif // TILELAYER_H
