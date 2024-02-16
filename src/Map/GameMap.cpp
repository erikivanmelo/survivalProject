#include "GameMap.h"
#include "../Camera/Camera.h"
#include "Chunk.h"
#include <iostream>
#include <algorithm>
#include <cstdint>
#include "../Helper.h"
#include "../Core/Engine.h"
#include "../Graphics/TextureManager.h"

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
    const int startY = std::clamp((int)((box->y/tileset->tileSize)/CHUNK_HEIGHT)-1, 0, chunkHeight-1);
    const int endX = (((box->x+box->w)/tileset->tileSize)/CHUNK_WIDTH)+1;
    const int endY = std::clamp((int)(((box->y+box->h)/tileset->tileSize)/CHUNK_HEIGHT)+1,0,chunkHeight-1);

    for(x = startX; x < endX; ++x )
        for (y = startY; y < endY; ++y)
            chunks[Helper::wrapToRange(x, chunkWidth)][y]->render();
}

void GameMap::displayPositionToMapPosition(Vector2D *position){
    static const Camera *cam  = Camera::getInstance();
    position->x = (float)Helper::wrapToRange((int)cam->getPosition()->x+(position->x/SCREEN_SCALE),pixelWidth)/tileset->tileSize;
    position->y = (float)std::clamp((int)(cam->getPosition()->y+position->y/SCREEN_SCALE),0,pixelHeight-1)/tileset->tileSize;
}

void GameMap::mapPositionToDisplayPosition(Vector2D *position){
    static const Camera *cam  = Camera::getInstance();
    position->x = (float)Helper::wrapToRange((int)cam->getPosition()->x+(position->x*tileset->tileSize),pixelWidth-1);
    position->y = (float)std::clamp((int)(cam->getPosition()->y+position->y*tileset->tileSize),0,pixelHeight-1);
}

bool GameMap::areBlockAround(int x, int y, bool z, bool inCenterToo){
    return  
        getTile(Helper::wrapToRange(x + 1, tileWidth), y, z) != 0 || 
        getTile(Helper::wrapToRange(x - 1, tileWidth), y, z) != 0 || 

        getTile(x, std::clamp(y + 1, 0, tileWidth - 1), z) != 0 || 
        getTile(x, std::clamp(y - 1, 0, tileWidth - 1), z) != 0 ||

        (inCenterToo && getTile(x, y, z) != 0);
}

void GameMap::focusBlock(Vector2D position){
    if (!areBlockAround(position.x, position.y, FOREGROUND, true) && !getTile(position.x, position.y, BACKGROUND)) 
        return;
    position = snapToGrid(position);
    int tileSize = tileset->tileSize;
    TextureManager::drawRect(
        position.x*tileSize, 
        position.y*tileSize, 
        tileSize, 
        tileSize, 
        {255, 0, 0,255} 
    );
}


