#include "GameMap.h"
#include "../Camera/Camera.h"
#include "Chunk.h"
#include <iostream>
#include <algorithm>
#include <cstdint>
#include "../Helper.h"
#include "../Graphics/TextureManager.h"

GameMap::GameMap( const MapSize width, const MapSize height ):
    chunkWidth(width), chunkHeight(height),
    pixelWidth((width*CHUNK_SQUARE_SIZE)*TILE_SIZE),
    pixelHeight((height*CHUNK_SQUARE_SIZE)*TILE_SIZE),
    tileWidth(width*CHUNK_SQUARE_SIZE),
    tileHeight(height*CHUNK_SQUARE_SIZE),
    tileset(AssetsManager::get()->getTileset()),
    changed(false),
    focusBlock(nullptr),
    focusBlockColor({0,0,0,0})
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
    static const SDL_FRect *box = Camera::get()->getViewBox();
    int x,y;
    const int startX = ((box->x/TILE_SIZE)/CHUNK_SQUARE_SIZE)-1;
    const int startY = std::clamp((int)((box->y/TILE_SIZE)/CHUNK_SQUARE_SIZE)-1, 0, chunkHeight-1);
    const int endX = (((box->x+box->w)/TILE_SIZE)/CHUNK_SQUARE_SIZE)+1;
    const int endY = std::clamp((int)(((box->y+box->h)/TILE_SIZE)/CHUNK_SQUARE_SIZE)+1,0,chunkHeight-1);

    for(x = startX; x < endX; ++x )
        for (y = startY; y < endY; ++y)
            chunks[Helper::wrapToRange(x, chunkWidth)][y]->render();
    drawFocusBlock();
    changed = false;
}

void GameMap::displayPositionToMapPosition(Vector2D *position){
    static const Camera *cam  = Camera::get();
    position->x = (int)Helper::wrapToRange((int)cam->getPosition()->x+(position->x/cam->getScreenScale()),pixelWidth)/TILE_SIZE;
    position->y = (int)std::clamp((int)(cam->getPosition()->y+position->y/cam->getScreenScale()),0,pixelHeight-1)/TILE_SIZE;
}

bool GameMap::areBlockAround(int x, int y, bool z, bool inCenterToo){
    return  
        getTile(Helper::wrapToRange(x + DIRECTION_RIGHT, tileWidth), y, z) != 0 || 
        getTile(Helper::wrapToRange(x + DIRECTION_LEFT, tileWidth), y, z) != 0 || 

        getTile(x, std::clamp(y + DIRECTION_DOWN, 0, tileWidth - 1), z) != 0 || 
        getTile(x, std::clamp(y + DIRECTION_UP, 0, tileWidth - 1), z) != 0 ||

        (inCenterToo && getTile(x, y, z) != 0);
}

void GameMap::setFocusBlock(Vector2D position, const SDL_Color &color) {
    Vector2D *lastValue = nullptr;
    if (focusBlock)
        lastValue = new Vector2D(*focusBlock);
    focusBlockColor = color;

    focusBlock = areBlockAround(position.x, position.y, FOREGROUND, true) || getTile(position.x, position.y, BACKGROUND)?
        new Vector2D(snapToGrid(position)) :
        nullptr;

    if (focusBlock && lastValue) {
        if (*lastValue != *focusBlock)
            changed = true;
    } else if(focusBlock){
        changed = true;
    }

    if (lastValue)
        delete lastValue;
}

void GameMap::drawFocusBlock() {
    if (!focusBlock)
        return;
    TextureManager::drawRect(
        focusBlock->x*TILE_SIZE, 
        focusBlock->y*TILE_SIZE, 
        TILE_SIZE, 
        TILE_SIZE, 
        focusBlockColor 
    );
}
