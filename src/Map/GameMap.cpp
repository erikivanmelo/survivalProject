#include "GameMap.h"
#include "../Camera/Camera.h"
#include "Chunk.h"
#include <iostream>
#include <algorithm>
#include <cstdint>
#include "../Helper.h"

GameMap::GameMap( const MapSize width, const MapSize height ):
    chunkWidth(width), chunkHeight(height),
    pixelWidth((width*CHUNK_WIDTH)*AssetsManager::getInstance()->getTileset()->tileSize),
    pixelHeight((height*CHUNK_HEIGHT)*AssetsManager::getInstance()->getTileset()->tileSize),
    tileWidth(width*CHUNK_WIDTH),
    tileHeight(height*CHUNK_HEIGHT),
    tileset(AssetsManager::getInstance()->getTileset())
{

    chunks.resize(width);
    for (MapSize i = 0; i < width; ++i) {
        chunks[i].resize(height);
    }

    for (int x = 0; x < chunkWidth; ++x) {
        for (int y = 0; y < chunkHeight; ++y) {
            chunks[x][y] = new Chunk(x,y);
        } 
    }

}

GameMap::~GameMap(){
    const ChunkSize xCount = chunks.size(), yCount = chunks[0].size();
    for (int x = 0; x < xCount; ++x) {
        for (int y = 0; y < yCount; ++y) {
            delete chunks[x][y];
            chunks[x][y] = nullptr;
        }
        chunks[x].clear();
    }
    chunks.clear();
}

void GameMap::render(){
    static SDL_Rect *box = Camera::getInstance()->getViewBox();
    int startX,endX,startY,endY,x,y;
    startX = Helper::wrapToRange((box->x/tileset->tileSize)/CHUNK_WIDTH,chunkWidth);
    //startY = std::clamp((box.y/tileset->tileSize)/CHUNK_HEIGHT, 0, chunkHeight-1);
    startY = 0;
    endX = Helper::wrapToRange(((box->x+box->w)/tileset->tileSize)/CHUNK_WIDTH-1,chunkWidth);
    //endY = std::clamp(((box.y+box.h)/tileset->tileSize)/CHUNK_HEIGHT,0,chunkHeight-1);
    endY = chunkHeight;

    x = startX;
    do {
        x = Helper::wrapToRange(x, chunkWidth);
        for (y = startY; y < endY; ++y) {
            chunks[x][y]->render();
        } 
        x++;
    }while(x != endX+1);
}
