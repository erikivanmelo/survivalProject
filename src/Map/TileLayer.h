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
    inline TileMap getTileMap()const{return tileMap;}
    void render()override;
    void update()override{};

    inline int getTileSize()const{return tileSize;}
    inline int getRowCount()const{return rowCount;}
    inline int getColCount()const{return colCount;}
    inline int getWidth()const{return width;}
    inline int getHeight()const{return height;}

private:
    const int tileSize;
    const int rowCount, colCount;
    const int width, height;

    TileMap tileMap;
    Tileset tileset;

    void determineRotation(unsigned int& tileId, SDL_RendererFlip& flip);
};

#endif // TILELAYER_H
