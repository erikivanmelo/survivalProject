#include "GameMap.h"
#include "../Camera/Camera.h"
#include "Chunk.h"
#include <iostream>
#include <algorithm>
#include <cstdint>
#include "../Helper.h"
#include "../Core/Engine.h"

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

    auto it = tileList.begin();
    while (it != tileList.end()) {
        delete it->second;
        it->second = nullptr;
        it = tileList.erase(it);
    }
}

void GameMap::render(){
    static const SDL_FRect *box = Camera::getInstance()->getViewBox();
    int x,y;
    const int startX = ((box->x/tileset->tileSize)/CHUNK_WIDTH)-1;
    const int startY = std::clamp((int)(box->y/tileset->tileSize)/CHUNK_HEIGHT, 0, chunkHeight-1);
    const int endX = (((box->x+box->w)/tileset->tileSize)/CHUNK_WIDTH)+1;
    const int endY = std::clamp((int)((box->y+box->h)/tileset->tileSize)/CHUNK_HEIGHT,0,chunkHeight-1);

    for(x = startX; x < endX; ++x ){
        for (y = startY; y <= endY; ++y) {
            chunks[Helper::wrapToRange(x, chunkWidth)][y]->render();
        } 
    }
}

void GameMap::displayToMapPosition(Vector2D *position){
    static const Camera *cam  = Camera::getInstance();
    position->x = (float)Helper::wrapToRange((int)cam->getPosition()->x+(position->x/SCREEN_SCALE),pixelWidth)/8;
    position->y = (float)std::clamp((int)(cam->getPosition()->y+position->y/SCREEN_SCALE),0,pixelHeight-1)/8;
}

